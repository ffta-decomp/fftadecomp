import { check, concat, hex, integer, put16, u16, view } from './binary.mjs';

const kana = 'ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむめもゃやゅゆょよらりるれろゎわをんァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロヮワヲンヴ、。ー';
const glyphs = kana +
  '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz' +
  '.「」『』…?!,·:_々/~‘’“”(){}[]+-±×=<>∞♂♀%&*※—|↑↓←→○△□■^;◎';
const controlSizes = new Map([
  ...[0x40, 0x41, 0x42, 0x4a, 0x4d, 0x4f, 0x52, 0x54, 0x56, 0x57, 0x58].map(n => [n, 0]),
  ...[0, 0x1b, 0x1d, 0x46, 0x4b, 0x51, 0x53, 0x32, 4].map(n => [n, 1]),
  [0x45, 2],
]);
const alternateControls = [4, 0x46, 0x4b, 0x45, 0x45, null, 0x53, 0x51,
  0x4d, 0x52, 0x42, 0x57, 0x54, 0x40, 0x4f, 0x41, 0x56, 0x4a, null, 0x1b, 0x1d, 0x58, 0];

export function inflate(bytes, offset, size, limit) {
  integer(size, 1, 65536, 'Decompressed text size');
  const output = new Uint8Array(size);
  let cursor = offset;
  let written = 0;
  const take = () => {
    check(cursor < limit, 'Truncated compressed dialogue');
    return bytes[cursor++];
  };
  while (written < size) {
    const op = take();
    let length;
    let distance = 0;
    let value = 0;
    if (op & 0x80) {
      length = ((op >> 3) & 15) + 3;
      distance = (((op & 7) << 8) | take()) + 1;
    } else if (op & 0x40) {
      length = (op & 63) + 1;
      check(written + length <= size, 'Dialogue literal exceeds decoded size');
      for (let i = 0; i < length; i++) output[written++] = take();
      continue;
    } else if (op & 0x20) {
      length = (op & 31) + 2;
    } else if (op & 0x10) {
      const high = take();
      length = (((high & 0xc0) >> 2) | (op & 15)) + 4;
      distance = (((high & 63) << 8) | take()) + 1;
    } else if (op === 1 || op === 2) {
      length = take() + 3;
      value = op === 1 ? 255 : 0;
    } else {
      check(op === 0, 'Unknown dialogue compression command');
      length = take() + 5;
      distance = ((take() << 8) | take()) + 1;
    }
    check(written + length <= size && distance <= written, 'Invalid compressed dialogue range');
    for (let i = 0; i < length; i++) {
      output[written] = distance ? output[written - distance] : value;
      written++;
    }
  }
  return output;
}

export function decodeText(bytes, alternate) {
  const tokens = [];
  let cursor = 0;
  let halfMode = false;
  let separators = 0;
  const take = () => {
    check(cursor < bytes.length && cursor < 4096, 'Unterminated dialogue record');
    return bytes[cursor++];
  };
  while (true) {
    const byte = take();
    if (alternate && byte === 255) break;
    if (!alternate && byte === 0) {
      if (!separators) break;
      separators--;
      tokens.push({ kind: 'separator' });
      continue;
    }
    if (!alternate && byte === 1) {
      halfMode = true;
      continue;
    }
    if (alternate ? byte < 0x80 : halfMode || byte >= 0x80) {
      const full = !alternate && !halfMode;
      const code = alternate ? take() : full ? ((byte & 127) << 8) | take() : byte - 1;
      tokens.push({ kind: 'glyph', code, width: full ? 'full' : 'half' });
      continue;
    }
    check(alternate || byte === 0x40, `Unknown dialogue marker ${hex(byte)}`);
    const code = alternate ? alternateControls[byte - 0x80] : take() - 0x21;
    check(controlSizes.has(code), 'Unknown dialogue control');
    const length = alternate && code === 0x45 ? 1 : controlSizes.get(code);
    const args = Array.from({ length }, take);
    tokens.push(alternate && code === 0x45
      ? { kind: 'control', code, args, side: byte === 0x83 ? 'left' : 'right' }
      : { kind: 'control', code, args });
    if (!alternate && code === 0x32) separators = 2;
  }
  return tokens;
}

export function readLine(bytes, start, end) {
  check(start + 2 <= end, 'Empty dialogue record');
  const flags = u16(bytes, start);
  const alternate = Boolean(flags & 1);
  const compressed = Boolean(flags & 2);
  check(!compressed || start + 6 <= end, 'Truncated dialogue header');
  const payload = compressed
    ? inflate(bytes, start + 6, view(bytes).getUint32(start + 2), end)
    : bytes.subarray(start + 2, end);
  const tokens = decodeText(payload, alternate);
  return { flags, encoding: alternate ? 'alternate' : 'standard', compressed, tokens, preview: preview(tokens) };
}

export function preview(tokens, withControls = false) {
  return tokens.map(token => {
    if (token.kind === 'glyph') return glyphs[token.code] ?? `⟨${hex(token.code, 4)}⟩`;
    if (token.kind === 'separator') return ' / ';
    if (token.code === 0x52) return ' ';
    if (token.code === 0x4d) return '\n';
    if (token.code === 0x4f) return '\n\n';
    if (token.code === 0x51) return `〈${hex(token.code)}:${token.args[0]}〉`;
    return withControls ? `‹${controlLabel(token.code)}${token.args.length ? ' ' + token.args.join(', ') : ''}›` : '';
  }).join('');
}

export function controlLabel(code) {
  return ({ 0x52: '空格', 0x4d: '换行', 0x32: '双字符串' })[code] ?? `控制码 ${hex(code)}`;
}

export function plainTokens(text, encoding = 'standard') {
  check(typeof text === 'string', 'Dialogue text must be a string');
  const substitutions = { "'": '’', '"': '”', '　': ' ' };
  const tokens = Array.from(text.replace(/\r\n?/g, '\n'), original => {
    const char = substitutions[original] ?? original;
    if (char === ' ') return { kind: 'control', code: 0x52, args: [] };
    if (char === '\n') return { kind: 'control', code: 0x4d, args: [] };
    const code = glyphs.indexOf(char);
    check(code >= 0, `Glyph unavailable in the US font map: ${JSON.stringify(original)}. Use a verified glyph token if you know its native code.`);
    return { kind: 'glyph', code, width: encoding === 'standard' ? 'full' : 'half' };
  });
  // Preserve the observed speech continuation sequence used by native scene dialogue.
  return [...tokens, { kind: 'control', code: 0x40, args: [] }, { kind: 'control', code: 0x42, args: [] }];
}

export function encodeLine(tokens, encoding, flags) {
  check(Array.isArray(tokens) && tokens.length <= 2048, 'Invalid dialogue token count');
  check(encoding === 'standard' || encoding === 'alternate', 'Unknown dialogue encoding');
  const alternate = encoding === 'alternate';
  const payload = [];
  let half = false;
  let separators = 0;
  for (const token of tokens) {
    check(token && typeof token === 'object', 'Invalid dialogue token');
    if (token.kind === 'glyph') {
      check(token.width === 'full' || token.width === 'half', 'Invalid glyph width');
      if (token.width === 'full') {
        check(!alternate && !half, 'Full-width token is incompatible with this dialogue encoding or position');
        const code = integer(token.code, 0, 3174, 'US glyph index');
        payload.push(0x80 | (code >> 8), code & 255);
      } else if (alternate) {
        payload.push(0, integer(token.code, 0, 255, 'Half-width glyph index'));
      } else {
        const code = integer(token.code, 1, 254, 'Half-width glyph index');
        if (!half) payload.push(1);
        half = true;
        payload.push(code + 1);
      }
    } else if (token.kind === 'control') {
      const { code, args } = token;
      check(controlSizes.has(code) && (alternate || !half), 'Invalid control code or position');
      check(Array.isArray(args) && args.length === (alternate && code === 0x45 ? 1 : controlSizes.get(code)), 'Wrong dialogue control argument count');
      if (alternate) {
        const opcode = code === 0x45 ? (token.side === 'left' ? 3 : token.side === 'right' ? 4 : -1) : alternateControls.indexOf(code);
        check(opcode >= 0, 'Control unavailable in alternate encoding');
        payload.push(0x80 + opcode);
      } else {
        payload.push(0x40, code + 0x21);
        if (code === 0x32) {
          check(!separators, 'Nested direct-string control');
          separators = 2;
        }
      }
      for (const arg of args) payload.push(integer(arg, 0, 255, 'Control argument'));
    } else {
      check(token.kind === 'separator' && !alternate && separators > 0, 'Unexpected direct-string separator');
      separators--;
      payload.push(0);
    }
  }
  check(!separators && payload.length < 4095, 'Unterminated or oversized dialogue');
  const header = new Uint8Array(2);
  put16(header, 0, (integer(flags, 0, 65535, 'Dialogue flags') & ~3) | Number(alternate));
  return concat([header, Uint8Array.from(payload), Uint8Array.of(alternate ? 255 : 0)]);
}

export function makePage(records) {
  check(records.length >= 1 && records.length < 4096, 'Dialogue page line count is outside native bounds');
  const indices = new Uint8Array((records.length + 1) * 2);
  let offset = indices.length;
  records.forEach((record, i) => {
    check(offset + record.length <= 65535, 'Dialogue page exceeds the 16-bit offset range');
    put16(indices, i * 2, offset);
    offset += record.length;
  });
  put16(indices, records.length * 2, 65535);
  return concat([indices, ...records]);
}
