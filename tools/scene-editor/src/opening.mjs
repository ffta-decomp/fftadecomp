import { check, concat, integer, put16 } from './binary.mjs';
import { PROFILE } from './profile.mjs';

export const OPENING_ID = 'first-act';
export const OPENING_ROSTER = { pointer: 0x54d208, start: 0x52cfc0, size: 432 };
// Only the battle banner consumer uses this copy of the encounter definitions.
export const OPENING_BANNER = { pointer: 0x92eb4, start: 0x54cd54, end: 0x55128c,
  categoryOffset: 30 * 40 + 34, defeatAllEnemies: 1 };
export const OPENING_OUTCOME = { pointer: 0xa148, start: 0xa1a908, end: 0xa1b90c, group: 0xa1b294 };
export const DIRECTIONS = ['southwest', 'northwest', 'northeast', 'southeast'];
export const OPENING_CAST = Object.freeze({
  marche: 15, mewt: 16, ritz: 17, student: 76, instructor: 23,
  redCap: 128, goblin1: 129, goblin2: 130, goblin3: 131,
});

export function blankOpening() {
  return {
    title: 'Goblin Patrol', cast: [], steps: [],
    battleIntro: 'Stand together!', battleEnding: "They're retreating.", victory: 'defeatOpponents',
  };
}

export function openingExample() {
  return {
    ...blankOpening(),
    cast: [
      { actor: 'marche', x: 3, y: 5, facing: 'southwest' },
      { actor: 'mewt', x: 3, y: 6, facing: 'northeast' },
      { actor: 'ritz', x: 6, y: 5, facing: 'southeast' },
      { actor: 'student', x: 7, y: 5, facing: 'northwest' },
      { actor: 'redCap', x: 4, y: 3, facing: 'southeast' },
      { actor: 'goblin1', x: 5, y: 2, facing: 'southwest' },
      { actor: 'goblin2', x: 7, y: 3, facing: 'northwest' },
      { actor: 'goblin3', x: 6, y: 6, facing: 'northeast' },
    ],
    steps: [
      { type: 'say', actor: 'marche', text: 'Something is moving\nby the fence.' },
      { type: 'walk', actor: 'marche', x: 4, y: 4, facing: 'southwest' },
      { type: 'face', actor: 'marche', facing: 'southeast' },
      { type: 'say', actor: 'redCap', text: 'Goblin patrol!\nStay where you are!' },
    ],
  };
}

function fields(value, keys, label) {
  check(value && typeof value === 'object' && !Array.isArray(value), `Invalid ${label}`);
  for (const key of Object.keys(value)) check(keys.includes(key), `Unknown ${label} field: ${key}`);
}

function direction(value) {
  const encoded = DIRECTIONS.indexOf(value);
  check(encoded >= 0, 'Choose a direction');
  return encoded;
}

function tile(value) {
  return { x: integer(value.x, 0, 11, 'Column'), y: integer(value.y, 0, 8, 'Row') };
}

const op = (operation, operands = {}) => ({ operation, operands });
const fadeAudio = (level, frames) => op('fadeSceneAudio', { level, frames, channels: 1 });
const fadeFromBlack = frames => op('fadeSceneBrightness', { mode: 0x13, frames, level: 100 });
const fadeToBlack = frames => op('fadeSceneBrightness', { mode: 0x31, frames, level: 0 });
const place = (actor, x, y, facing, visibility) =>
  op('placeSceneActor', { actor, tile: (y << 4) | x, facing, visibility });

export function lowerOpening(rom, project) {
  const openings = project.openings ?? {};
  fields(openings, [OPENING_ID], 'opening collection');
  if (!Object.hasOwn(openings, OPENING_ID)) return { project, roster: null, outcome: null, opening: null };
  const opening = openings[OPENING_ID];
  fields(opening, ['title', 'cast', 'steps', 'battleIntro', 'battleEnding', 'victory'], 'opening');
  check(typeof opening.title === 'string' && opening.title.trim() && opening.title.length <= 80, 'Opening title must contain 1–80 characters');
  check(Array.isArray(opening.cast) && Array.isArray(opening.steps) && opening.steps.length <= 120, 'Invalid opening cast or steps');
  check(typeof opening.battleIntro === 'string' && opening.battleIntro.length <= 160, 'Invalid battle introduction');
  const ending = opening.battleEnding ?? blankOpening().battleEnding;
  check(typeof ending === 'string' && ending.length <= 160, 'Invalid battle ending');
  check(opening.victory === undefined || opening.victory === 'defeatOpponents', 'Invalid opening victory rule');
  for (const id of [1, 2, 6]) check(!Object.hasOwn(project.scenes, id), `Scene ${id} is owned by the authored opening`);
  for (const key of ['0/0', '0/1', '0/5']) check(!Object.hasOwn(project.programs, key), `Program ${key} is owned by the authored opening`);

  const cast = new Map();
  const occupied = new Set();
  for (const member of opening.cast) {
    fields(member, ['actor', 'x', 'y', 'facing'], 'cast member');
    const { actor, facing } = member;
    check(Object.hasOwn(OPENING_CAST, actor) && !cast.has(actor), 'Unknown or duplicate cast member');
    const { x, y } = tile(member);
    const key = `${x},${y}`;
    check(!occupied.has(key), 'Each cast member needs a separate starting tile');
    occupied.add(key);
    cast.set(actor, place(OPENING_CAST[actor], x, y, direction(facing), 1));
  }

  const effective = structuredClone(project);
  const page = PROFILE.dialogue.pages + Object.keys(project.pages).length;
  check(!Object.keys(project.dialogue).some(key => key.split(':')[0] === String(page)),
    'Edit generated opening dialogue in the Cutscene panel');
  effective.pages[page] = {};
  let line = 0;
  function say(actor, text, presentationFlags) {
    check(typeof text === 'string' && text.trim() && text.length <= 160, 'Dialogue must contain 1–160 characters');
    effective.dialogue[`${page}:${line}`] = { text };
    return op('say', { speakerHandle: actor, textSelector: line++, presentationFlags });
  }

  const script = [
    op('setStoryFlag', { flag: 0x580, value: 1 }), op('setStoryFlag', { flag: 2, value: 1 }),
    op('selectSceneEncounter', { encounter: 1 }), op('loadSceneMap', { map: 0 }),
    op('prepareMapView', { mode: 1 }), op('loadEncounterUnits'),
    ...Object.entries(OPENING_CAST).map(([key, handle]) => cast.get(key) ?? place(handle, 11, 8, 1, 3)),
    op('selectScenePresentation', { preset: 24 }), op('moveSceneCamera', { x: 152, y: 204, mode: 1, duration: 0 }),
    fadeAudio(100, 1), fadeFromBlack(20),
  ];
  for (const step of opening.steps) {
    check(step && typeof step === 'object' && !Array.isArray(step), 'Invalid opening step');
    const { type, actor } = step;
    const handle = OPENING_CAST[actor];
    check(cast.has(actor), 'Every step must use an actor from the cast');
    if (type === 'say') {
      fields(step, ['type', 'actor', 'text'], 'dialogue step');
      script.push(say(handle, step.text, handle < 128 ? 130 : 128));
    } else if (type === 'walk') {
      fields(step, ['type', 'actor', 'x', 'y', 'facing'], 'walk step');
      const { x, y } = tile(step);
      script.push(op('setContextValue', { value: 16 }),
        op('moveActorOnGrid', { actor: handle, x, y, facing: direction(step.facing), mode: 0, speed: 1 }),
        op('waitForActors'), op('setActorTile', { actor: handle, x, y }));
    } else if (type === 'face') {
      fields(step, ['type', 'actor', 'facing'], 'facing step');
      script.push(op('setActorFacing', { actor: handle, facing: direction(step.facing) }),
        op('refreshActorFacing', { actor: handle }));
    } else {
      throw new Error('Unknown opening step');
    }
  }
  script.push(op('setContextValue', { value: 30 }), fadeToBlack(20), op('selectScenePresentation', { preset: 33 }), fadeFromBlack(20));
  const deployment = [
    [15, 4, 3, 0], [16, 5, 2, 2], [76, 8, 2, 1], [17, 7, 3, 3],
    [131, 4, 7, 2], [128, 6, 7, 3], [129, 5, 6, 0], [130, 8, 6, 1],
  ];
  for (const [actor, x, y, facing] of deployment) {
    if (![...cast.values()].some(command => command.operands.actor === actor)) script.push(place(actor, x, y, facing, 1));
    script.push(op('setActorTile', { actor, x, y }));
  }
  script.push(op('setSceneRuntimeMode', { mode: 4 }));

  effective.scenes[1] = { dialoguePage: page };
  effective.scenes[2] = { dialoguePage: page };
  effective.scenes[6] = { dialoguePage: page };
  effective.programs['0/0'] = { instructions: script };
  effective.programs['0/5'] = { instructions: [
    op('setStoryFlag', { flag: 2, value: 0 }),
    op('selectScenePresentation', { preset: 24 }),
    op('moveSceneCamera', { x: 152, y: 204, mode: 1, duration: 0 }), fadeFromBlack(15),
    ...(opening.battleIntro.trim() ? [say(15, opening.battleIntro, 128)] : []),
    op('setContextValue', { value: 30 }),
    op('setSceneRuntimeMode', { mode: 8 }),
  ] };

  effective.programs['0/1'] = { instructions: [
    op('selectScenePresentation', { preset: 24 }),
    op('moveSceneCamera', { x: 152, y: 204, mode: 1, duration: 0 }), fadeFromBlack(20),
    ...(ending.trim() ? [say(15, ending, 128)] : []),
    fadeToBlack(24), op('setSceneRuntimeState12'),
    op('queueScene', { scene: 4 }), op('setSceneRuntimeMode', { mode: 2 }),
  ] };

  const roster = rom.bytes.slice(OPENING_ROSTER.start, OPENING_ROSTER.start + OPENING_ROSTER.size);
  for (let slot = 0; slot < 4; slot++) roster.set([1, slot === 0 ? 45 : 44], slot * 48);
  if (line === 0) effective.dialogue[`${page}:0`] = { text: '' };
  return { project: effective, roster, outcome: compileOutcome(rom), opening };
}

function compileOutcome(rom) {
  const { start, end, group } = OPENING_OUTCOME;
  const archive = rom.bytes.slice(start, end);
  const openingProgram = 1;
  // The battle outcome dispatcher selects group five, entry one after damage.
  const entry = group - start + openingProgram * 2;
  put16(archive, entry, end - group);
  return concat([archive, new Uint8Array([
    0x04, 0x21, 0x02, 17, 0, // Completion flag already set: finish.
    0x10, 3, 0,              // No eligible enemies: skip the next jump.
    0x01, 11, 0,             // Enemies remain: finish without setting flags.
    0x02, 0x21, 0x02, 1,     // Mark this outcome handled once.
    0x02, 0x20, 0x02, 1,     // Set the native battle completion flag.
    0x05, 2, 0,              // Enqueue the authored ending.
    0,
  ])]);
}
