import { check } from './binary.mjs';
import { PROFILE } from './profile.mjs';
import { pageKey, programKey } from './rom.mjs';

/**
 * Build a static reading of the selected program. Branch destinations are
 * byte offsets; the browser never simulates game flags or task scheduling.
 */
export function storySteps(commands) {
  const steps = [];
  const branchTargets = new Set();
  const resolve = command => command.offset +
    (command.operation === 'adjustScriptOffset' ? 3 : 5) + command.operands.delta;
  for (const command of commands) {
    if (command.operation === 'adjustScriptOffset' || command.operation === 'addOffsetWhenTargetFlagSet') {
      branchTargets.add(resolve(command));
    }
  }
  commands.forEach((command, index) => {
    const { offset, operation, operands } = command;
    if (operation === 'native') {
      const previous = steps.at(-1);
      if (previous?.kind === 'native' && !branchTargets.has(offset)) {
        previous.count++;
        previous.opcodes.push(command.opcode);
        return;
      }
      steps.push({ kind: 'native', index, offset, count: 1, opcodes: [command.opcode] });
    } else if (operation === 'say') {
      steps.push({ kind: 'dialogue', index, offset, ...operands, pageScope: operands.textSelector > 239 ? 'fallback' : 'scene' });
    } else if (operation === 'adjustScriptOffset' || operation === 'addOffsetWhenTargetFlagSet') {
      steps.push({ kind: 'branch', index, offset, operation, operands, target: resolve(command) });
    } else {
      steps.push({ kind: operation === 'finishSceneTask' ? 'end' : 'action', index, offset, operation, operands });
    }
  });
  return steps;
}

export function describeStory(rom, change, id, variant = 0) {
  const scene = change.scenes.get(id) ?? rom.scenes[id];
  check(scene?.id > 0, 'Unknown scene ID');
  const { script, dialoguePage } = scene;
  const key = programKey(script.group, script.program);
  const changed = change.programs.get(key);
  const commands = changed?.commands ?? rom.programs.get(key)?.commands ?? [];
  const page = pageKey(dialoguePage, dialoguePage === PROFILE.dialogue.nested ? variant : null);
  const records = change.pages.get(page)?.records ?? rom.pages.get(page)?.records;
  check(records, 'Unknown dialogue page or variant');
  const lines = new Map(records.map(record => [record.index, record.preview]));
  for (const edit of change.diffs) {
    const [target, line] = edit.target.split(':');
    if (edit.kind === 'dialogue' && target === page) lines.set(Number(line), edit.after.text);
  }
  const linear = storySteps(commands).flatMap(step => {
    const inserted = (changed?.insertions ?? []).flatMap((event, i) => event.anchorOffset === step.offset
      ? [{ ...event, kind: 'dialogue', index: step.index, offset: step.offset, insertionIndex: i, pageScope: 'scene' }]
      : []);
    return [...inserted, step];
  });
  const steps = linear.map(step => step.kind === 'dialogue' && step.pageScope === 'scene'
    ? { ...step, dialogue: { page, line: step.textSelector, text: lines.get(step.textSelector) ?? null } }
    : step);
  return { format: 'ffta.scene-story/v1', scene: id, script, page, steps };
}
