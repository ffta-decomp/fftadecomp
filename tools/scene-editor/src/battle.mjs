import { check, integer } from './binary.mjs';
import { encodeLine, plainTokens } from './text.mjs';

export const DEMO_ID = 'snowball.goblin';
export const BATTLE_SCENE = 6;
export const BATTLE_EVENT_CAPABILITIES = [
  { key: 'onDamageResolved', state: 'rom-probe' },
  { key: 'spawnBattleUnit', state: 'unbound' },
  { key: 'speakAsBattleUnit', state: 'unbound' },
  { key: 'replaceVictoryCondition', state: 'native-retarget-probe' },
];

function fields(value, required, subject) {
  check(value && typeof value === 'object' && !Array.isArray(value), `${subject} must be an object`);
  const keys = Object.keys(value);
  check(keys.length === required.length && required.every(key => Object.hasOwn(value, key)), `Invalid ${subject} fields`);
}

export function snowballDemo() {
  return {
    scene: BATTLE_SCENE,
    trigger: { kind: 'onDamageResolved', target: 'mewt', once: 'perBattle' },
    spawn: { id: 'goblin', template: 'goblin', side: 'opponent', hp: 3, attack: 1 },
    dialogue: { speaker: 'goblin', text: 'Count me in!' },
    victory: { kind: 'defeatUnit', target: 'goblin' },
  };
}

export function validateBattleEvent(key, event) {
  check(key === DEMO_ID, 'The US profile only supports the Snowball Battle authoring fixture');
  fields(event, ['scene', 'trigger', 'spawn', 'dialogue', 'victory'], 'battle event');
  check(event.scene === BATTLE_SCENE, 'The battle event must belong to Snowball Battle');
  const { trigger, spawn, dialogue, victory } = event;
  fields(trigger, ['kind', 'target', 'once'], 'trigger');
  check(trigger.kind === 'onDamageResolved' && trigger.target === 'mewt' && trigger.once === 'perBattle',
    'The fixture requires once-per-battle damage to Mewt');
  fields(spawn, ['id', 'template', 'side', 'hp', 'attack'], 'opponent');
  check(spawn.id === 'goblin' && spawn.template === 'goblin' && spawn.side === 'opponent', 'Invalid fixture opponent');
  integer(spawn.hp, 1, 255, 'Goblin HP');
  integer(spawn.attack, 0, 255, 'Goblin attack');
  fields(dialogue, ['speaker', 'text'], 'battle dialogue');
  check(dialogue.speaker === spawn.id && typeof dialogue.text === 'string' && dialogue.text.trim(), 'Invalid Goblin dialogue');
  encodeLine(plainTokens(dialogue.text), 'standard', 0x10);
  fields(victory, ['kind', 'target'], 'victory condition');
  check(victory.kind === 'defeatUnit' && victory.target === spawn.id, 'Victory must refer to the spawned opponent');
  return event;
}

/** Preview the declarative rule against author-supplied battle events. */
export function battleEventStep(rule, phase, input) {
  if (phase === 'waiting' && input.kind === 'damageResolved' && input.target === rule.trigger.target && input.damage > 0) {
    return { phase: 'speaking', outputs: [
      { kind: 'spawnBattleUnit', ...rule.spawn },
      { kind: 'speakAsBattleUnit', ...rule.dialogue },
    ] };
  }
  if (phase === 'speaking' && input.kind === 'dialogueClosed') {
    return { phase: 'fighting', outputs: [{ kind: 'resumeBattle' }] };
  }
  if (phase === 'fighting' && input.kind === 'unitDefeated' && input.target === rule.victory.target) {
    return { phase: 'won', outputs: [{ kind: 'battleVictory', target: input.target }] };
  }
  return { phase, outputs: [] };
}
