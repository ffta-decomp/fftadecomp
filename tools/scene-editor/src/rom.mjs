import { PROFILE, OPERATIONS, US_LAYOUT_SIGNATURES } from './profile.mjs';
import { check, digest, hex, u16, u32 } from './binary.mjs';
import { readLine } from './text.mjs';

export const programKey = (group, program) => `${group}/${program}`;
export const pageKey = (page, variant = null) => variant === null ? String(page) : `${page}/${variant}`;
export const lineKey = (page, line) => `${page}:${line}`;

export function opcodeSpecs(bytes) {
  const specs = new Map();
  for (let opcode = 0; opcode <= 0x71; opcode++) {
    const at = PROFILE.scripts.descriptors + opcode * 6;
    const size = u16(bytes, at);
    const handler = u32(bytes, at + 2);
    if (size < 1 || size > 64 || !(handler & 1) || handler < PROFILE.bus || handler >= PROFILE.bus + bytes.length) continue;
    const [operation, label, operands] = OPERATIONS[opcode] ?? ['native', '待考证的原生指令', null];
    check(operands === null || operands.reduce((sum, arg) => sum + arg.size, 1) === size, `Incorrect opcode schema for ${hex(opcode)}`);
    specs.set(opcode, { opcode, size, handler, operation, label, operands });
  }
  return specs;
}

export function decodeInstructions(bytes, specs) {
  const commands = [];
  let cursor = 0;
  while (cursor < bytes.length) {
    const opcode = bytes[cursor];
    const spec = specs.get(opcode);
    check(spec && cursor + spec.size <= bytes.length, `Invalid instruction ${hex(opcode)} at +${hex(cursor)}`);
    let command;
    if (spec.operands) {
      let at = cursor + 1;
      const operands = {};
      for (const arg of spec.operands) {
        const raw = arg.size === 1 ? bytes[at] : u16(bytes, at);
        operands[arg.key] = arg.signed && raw >= 0x8000 ? raw - 0x10000 : raw;
        at += arg.size;
      }
      command = { operation: spec.operation, operands };
    } else {
      command = { operation: 'native', opcode, operands: Array.from(bytes.subarray(cursor + 1, cursor + spec.size)) };
    }
    commands.push({ offset: cursor, ...command });
    cursor += spec.size;
  }
  return commands;
}

export function readPrograms(bytes, specs) {
  const { start, end, groups } = PROFILE.scripts;
  check(u32(bytes, start) === groups * 4, 'Unexpected script group count');
  const groupStarts = Array.from({ length: groups }, (_, i) => start + u32(bytes, start + i * 4));
  const result = new Map();
  const directories = groupStarts.map((groupStart, group) => {
    const groupEnd = groupStarts[group + 1] ?? end;
    const directoryBytes = u32(bytes, groupStart);
    check(directoryBytes > 0 && directoryBytes % 4 === 0 && groupStart + directoryBytes <= groupEnd, 'Invalid program directory');
    const offsets = Array.from({ length: directoryBytes / 4 }, (_, i) => groupStart + u32(bytes, groupStart + i * 4));
    const programs = [];
    for (let i = 0; i < offsets.length; i++) {
      const first = offsets[i];
      const last = offsets[i + 1] ?? groupEnd;
      check(first >= groupStart + directoryBytes && last >= first && last <= groupEnd, 'Invalid program range');
      if (first === groupEnd) continue;
      let endOfCommands = last;
      if (last === groupEnd) {
        while (endOfCommands > first && last - endOfCommands < 3 && bytes[endOfCommands - 1] === 255) endOfCommands--;
        // A trailing 0xff can belong to a real instruction operand.
        while (endOfCommands < last) {
          try {
            decodeInstructions(bytes.subarray(first, endOfCommands), specs);
            break;
          } catch {
            endOfCommands++;
          }
        }
      }
      const commands = decodeInstructions(bytes.subarray(first, endOfCommands), specs);
      const item = { group, program: i, offset: first, end: endOfCommands, commands };
      programs.push(item);
      result.set(programKey(group, i), item);
    }
    return { group, start: groupStart, end: groupEnd, slotCount: offsets.length, programs };
  });
  return { programs: result, directories };
}

function readPages(bytes) {
  const { start, pages, nested, variants, end } = PROFILE.dialogue;
  const outer = Array.from({ length: pages }, (_, i) => start + u32(bytes, start + i * 4));
  const children = Array.from({ length: variants }, (_, i) => start + u32(bytes, outer[nested] + i * 4));
  const limits = [...new Set([...outer, ...children, end])].sort((a, b) => a - b);
  const unique = new Map();
  const result = new Map();
  function add(page, variant, offset) {
    if (!unique.has(offset)) {
      const limit = limits[limits.indexOf(offset) + 1];
      check(offset >= start + pages * 4 && limit <= end, 'Invalid dialogue page pointer');
      const directory = u16(bytes, offset);
      const count = directory / 2 - 1;
      check(Number.isInteger(count) && count > 0 && count < 4096 && offset + directory < limit &&
        u16(bytes, offset + directory - 2) === 65535, 'Invalid dialogue directory');
      const records = Array.from({ length: count }, (_, i) => {
        const first = offset + u16(bytes, offset + i * 2);
        const last = i + 1 === count ? limit : offset + u16(bytes, offset + (i + 1) * 2);
        check(first >= offset + directory && first < last && last <= limit, 'Invalid dialogue record bounds');
        return { index: i, start: first, end: last, ...readLine(bytes, first, last) };
      });
      unique.set(offset, records);
    }
    const key = pageKey(page, variant);
    result.set(key, { key, page, variant, offset, records: unique.get(offset) });
  }
  outer.forEach((offset, page) => {
    if (page === nested) children.forEach((child, variant) => add(page, variant, child));
    else add(page, null, offset);
  });
  return { pages: result, outer, children };
}

export async function openRetail(input) {
  const rom = await openUSRom(input);
  check(rom.sha256 === PROFILE.sha256, 'Unrecognized US retail ROM revision');
  return rom;
}

export async function openUSRom(input) {
  check(input instanceof Uint8Array && input.length === PROFILE.size, 'Expected a 16 MiB FFTA US ROM');
  const bytes = Uint8Array.from(input);
  const sha256 = await digest(bytes);
  const retail = sha256 === PROFILE.sha256;
  if (!retail) {
    const gameCode = String.fromCharCode(...bytes.subarray(0xac, 0xb0));
    check(gameCode === PROFILE.gameCode && bytes[0xbc] === 0, 'This game or ROM revision needs its own profile');
    for (const [start, end, expected] of US_LAYOUT_SIGNATURES) {
      check(await digest(bytes.subarray(start, end)) === expected,
        'This ROM changes the US engine or scene instruction table and needs its own profile');
    }
  }
  for (const table of [PROFILE.index, PROFILE.scripts, PROFILE.dialogue]) {
    check(u32(bytes, table.pointer) === PROFILE.bus + table.start, 'Unexpected native pointer');
  }
  const specs = opcodeSpecs(bytes);
  const { programs, directories } = readPrograms(bytes, specs);
  const { pages, outer, children } = readPages(bytes);
  const scenes = Array.from({ length: PROFILE.index.count }, (_, id) => {
    const at = PROFILE.index.start + id * 4;
    const [oneBasedGroup, program, dialoguePage, reserved] = bytes.subarray(at, at + 4);
    const script = { group: oneBasedGroup - 1, program };
    const linked = programs.get(programKey(script.group, script.program));
    const status = id === 0 ? 'sentinel' : linked?.commands.length ? 'resolved' : linked ? 'empty' : 'unresolved';
    return { id, status, script, dialoguePage, reserved };
  });
  check(programs.size === 228 && pages.size === 88, 'Unexpected retail scene archive topology');
  return { bytes, profile: retail ? PROFILE.id : PROFILE.compatibleId, sha256, scenes, specs, programs, directories, pages, outer, children };
}

export function catalog(rom, { includePrograms = false, includeDialogue = false } = {}) {
  const scenes = rom.scenes.map(scene => {
    const page = rom.pages.get(pageKey(scene.dialoguePage, scene.dialoguePage === PROFILE.dialogue.nested ? 0 : null));
    const program = rom.programs.get(programKey(scene.script.group, scene.script.program));
    return {
      ...scene, instructionCount: program?.commands.length ?? 0,
      dialogueCount: page?.records.length ?? 0, excerpt: scene.id ? (page?.records[0]?.preview ?? '').slice(0, 100) : '',
    };
  });
  return {
    format: 'ffta.scene-catalog/v1', profile: rom.profile, baseSha256: rom.sha256, scenes,
    opcodes: [...rom.specs.values()],
    pages: [...rom.pages.values()].map(({ key, page, variant, records }) => ({
      key, page, variant, lineCount: records.length,
      ...(includeDialogue ? { lines: records.map(({ index, flags, encoding, tokens, preview }) => ({ index, flags, encoding, tokens, preview })) } : {}),
    })),
    ...(includePrograms ? { programs: [...rom.programs.values()].map(({ group, program, commands }) => ({ group, program, commands })) } : {}),
  };
}
