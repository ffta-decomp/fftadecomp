import { check, eq, put32, u32 } from './binary.mjs';
import { BATTLE_SCENE, DEMO_ID } from './battle.mjs';
import { PROFILE } from './profile.mjs';

// Rebuild from runtime/snowball_hit_probe.s with GNU as for ARM7TDMI.
const listener = Uint8Array.from(
  '1fb40e480088062811d10d4886420ed1307910280bd1308b854208d209480068002804d0dc300088392800d1c0461fbc3583301c044a9646044a104792210002ec340002a8f40002a1220a0881820c08'
    .match(/../g), byte => Number.parseInt(byte, 16));
const original = Uint8Array.of(0x35, 0x83, 0x30, 0x1c, 0x25, 0xf0, 0xf0, 0xff);
const hook = 0x0a2298;
const markerOffset = 0x2c;

function expandProbe(rom) {
  check(rom.sha256 === PROFILE.sha256 && rom.bytes.length === PROFILE.size, 'Expected verified US retail ROM');
  const bytes = new Uint8Array(PROFILE.maximumSize).fill(255);
  bytes.set(rom.bytes);
  return bytes;
}

export function buildBattleVictoryProbe(rom) {
  const directory = 0xa1a908;
  const end = 0xa1b90c;
  const directoryPointer = 0xa148;
  const selectorField = 0xa1b318;
  const stockRule = Uint8Array.of(4, 0x21, 2, 16, 0, 9, 16, 1, 11, 0, 2, 0x21, 2, 1, 2, 0x20, 2, 1, 5, 2, 0, 0);
  check(u32(rom.bytes, directoryPointer) === PROFILE.bus + directory &&
    eq(rom.bytes.subarray(selectorField - 6, selectorField - 6 + stockRule.length), stockRule),
  'Snowball victory script differs from the verified retail revision');
  const bytes = expandProbe(rom);
  bytes.set(rom.bytes.subarray(directory, end), PROFILE.size);
  // The second observed retail target is already present and targetable at battle entry.
  bytes[PROFILE.size + selectorField - directory] = 76;
  put32(bytes, directoryPointer, PROFILE.bus + PROFILE.size);
  return {
    bytes,
    report: { format: 'ffta.battle-victory-probe/v1', baseSha256: rom.sha256, scene: BATTLE_SCENE,
      mode: 'retarget-existing-unit', nativeRule: { group: 5, index: 1 }, targetSelector: 76 },
  };
}

export function buildBattleListenerProbe(rom) {
  check(rom.sha256 === PROFILE.sha256 && eq(rom.bytes.subarray(hook, hook + original.length), original),
    'Snowball listener hook differs from the verified retail revision');
  const address = PROFILE.bus + PROFILE.size;
  const bytes = expandProbe(rom);
  bytes.set(listener, PROFILE.size);
  // Load a Thumb address from the original BL's words and tail-branch from the store site.
  bytes.set(Uint8Array.of(0x00, 0x4b, 0x18, 0x47), hook);
  put32(bytes, hook + 4, address + 1);
  return {
    bytes,
    report: {
      format: 'ffta.battle-listener-probe/v1',
      baseSha256: rom.sha256,
      event: DEMO_ID,
      hookOffset: hook,
      routineOffset: PROFILE.size,
      markerAddress: address + markerOffset,
      size: listener.length,
    },
  };
}
