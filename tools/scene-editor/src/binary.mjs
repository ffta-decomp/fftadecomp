export const fail = message => { throw new Error(message); };
export const check = (condition, message) => { if (!condition) fail(message); };
export const align = (value, boundary = 4) => Math.ceil(value / boundary) * boundary;
export const hex = (value, width = 2) => '0x' + value.toString(16).padStart(width, '0');
export const view = bytes => new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
export const u16 = (bytes, offset) => view(bytes).getUint16(offset, true);
export const u32 = (bytes, offset) => view(bytes).getUint32(offset, true);
export const put16 = (bytes, offset, value) => view(bytes).setUint16(offset, value, true);
export const put32 = (bytes, offset, value) => view(bytes).setUint32(offset, value, true);
export const bytesHex = bytes => Array.from(bytes, n => n.toString(16).padStart(2, '0')).join('');
export const eq = (a, b) => a.length === b.length && a.every((n, i) => n === b[i]);
export async function digest(bytes) {
  return bytesHex(new Uint8Array(await crypto.subtle.digest('SHA-256', bytes)));
}
export function integer(value, min, max, field) {
  check(Number.isInteger(value) && value >= min && value <= max, `${field} must be an integer in ${min}..${max}`);
  return value;
}
export function concat(parts) {
  const result = new Uint8Array(parts.reduce((sum, part) => sum + part.length, 0));
  let offset = 0;
  for (const part of parts) {
    result.set(part, offset);
    offset += part.length;
  }
  return result;
}
