#!/usr/bin/env python3
"""Export the bounded fields read by the graphics action-script interpreter."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_pointer_lz77_records import POINTER_START, POINTER_END, ROM_BASE, ROM_SHA256

SCRIPT_START = 0x948450
SCRIPT_END = 0x94d5c4
SCRIPT_COUNT = 73
# Exact byte widths read from r7 by the interpreter's jump-table handlers.
ARGUMENT_BYTES = {3: 6, 4: 2, 5: 2, 6: 6, 7: 4, 8: 1, 9: 1, 12: 6}


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def merge_ranges(ranges):
    merged = []
    for start, end in sorted(ranges):
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(end, merged[-1][1]))
        else:
            merged.append((start, end))
    return merged


def encode_halfwords(values):
    if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("graphics action halfword differs")
    return b"".join(value.to_bytes(2, "little") for value in values)


def serialize_selected_fields(record, fields):
    size = record["end"] - record["start"]
    prefix = fields["header_prefix"]
    commands = fields["commands"]
    if (len(prefix) != 3 or any(type(value) is not int or not 0 <= value <= 255 for value in prefix)
            or len(commands) != record["command_count"] or len(commands) > 255):
        raise ValueError("graphics action header differs")
    header = bytes(prefix + [len(commands)]) + encode_halfwords([fields["initial_delay"]])
    required = []
    for command in commands:
        opcode = command["opcode"]
        flags = command["flags"]
        if (type(opcode) is not int or not 0 <= opcode <= 13 or
                type(flags) is not int or not 0 <= flags <= 255):
            raise ValueError("graphics action opcode or flags differ")
        header += bytes((opcode, flags)) + encode_halfwords(
            [command["duration"], command["argument_offset"]])
        length = ARGUMENT_BYTES.get(opcode, 0)
        if length:
            offset = command["argument_offset"]
            if offset + length > size:
                raise ValueError("graphics action argument leaves record")
            required.append((offset, offset + length))
    if len(header) > size:
        raise ValueError("graphics action commands leave record")
    expected = merge_ranges(required)
    supplied = fields["arguments"]
    if [(argument["offset"], argument["offset"] + len(argument["bytes"]))
            for argument in supplied] != expected:
        raise ValueError("graphics action argument coverage differs")
    result = bytearray(size)
    covered = bytearray(size)

    def write(offset, data):
        if offset < 0 or offset + len(data) > size:
            raise ValueError("graphics action field leaves record")
        for index, value in enumerate(data):
            position = offset + index
            if covered[position] and result[position] != value:
                raise ValueError("graphics action fields conflict")
            result[position] = value
            covered[position] = 1

    write(0, header)
    for argument in supplied:
        values = argument["bytes"]
        if any(type(value) is not int or not 0 <= value <= 255 for value in values):
            raise ValueError("graphics action argument byte differs")
        write(argument["offset"], bytes(values))
    return bytes(result), bytes(covered)


def serialize_selected(record, source):
    return serialize_selected_fields(record, json.loads(source.read_text()))


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    record_dir = output / "records"
    record_dir.mkdir(exist_ok=True)
    pointers = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if SCRIPT_START <= target < SCRIPT_END:
            pointers.setdefault(target, []).append(site)
    starts = sorted(pointers)
    if len(starts) != SCRIPT_COUNT or starts[0] != SCRIPT_START:
        raise ValueError("graphics action pointer directory differs")
    records = []
    fragments = []
    for index, start in enumerate(starts):
        end = starts[index + 1] if index + 1 < len(starts) else SCRIPT_END
        source = rom[start:end]
        count = source[3]
        header_end = 6 + 6 * count
        if header_end > len(source):
            raise ValueError("graphics action command table leaves record")
        commands = []
        required = []
        for step in range(count):
            at = 6 + step * 6
            opcode, flags = source[at:at + 2]
            if opcode > 13:
                raise ValueError("graphics action opcode leaves interpreter range")
            duration = int.from_bytes(source[at + 2:at + 4], "little")
            offset = int.from_bytes(source[at + 4:at + 6], "little")
            if offset > len(source):
                raise ValueError("graphics action relative offset leaves record")
            commands.append({"opcode": opcode, "flags": flags,
                             "duration": duration, "argument_offset": offset})
            length = ARGUMENT_BYTES.get(opcode, 0)
            if length:
                if offset + length > len(source):
                    raise ValueError("graphics action argument leaves record")
                required.append((offset, offset + length))
        argument_ranges = merge_ranges(required)
        fields = {"header_prefix": list(source[:3]),
                  "initial_delay": int.from_bytes(source[4:6], "little"),
                  "commands": commands,
                  "arguments": [{"offset": first, "bytes": list(source[first:last])}
                                for first, last in argument_ranges]}
        name = f"action-0x{start:06x}.json"
        path = record_dir / name
        path.write_text(json.dumps(fields, indent=2) + "\n")
        record = {"start": start, "end": end, "command_count": count,
                  "pointer_sites": pointers[start], "file": name,
                  "opaque_bytes": len(source) - sum(last - first for first, last in
                                                     merge_ranges([(0, header_end)] + argument_ranges))}
        rebuilt, covered = serialize_selected(record, path)
        if any(covered[pos] and rebuilt[pos] != source[pos] for pos in range(len(source))):
            raise ValueError("graphics action fields do not round-trip")
        for first, last in merge_ranges([(0, header_end)] + argument_ranges):
            fragments.append({"start": start + first, "size": last - first,
                              "record_start": start, "source_sha256": sha256(source[first:last])})
        records.append(record)
    manifest = {"reference_sha256": ROM_SHA256,
                "interpreter_entry": 0x080d4224, "record_loader": 0x080d44cc,
                "pointer_table_window": [POINTER_START, POINTER_END],
                "records": records, "fragments": fragments,
                "record_count": len(records),
                "command_count": sum(record["command_count"] for record in records),
                "structured_bytes": sum(fragment["size"] for fragment in fragments),
                "opaque_bytes": sum(record["opaque_bytes"] for record in records),
                "scope_note": "Only fields read at the named interpreter offsets are rebuilt. Opaque record tails and later pointer targets remain original-byte inclusion."}
    if (manifest["command_count"] != 279 or manifest["structured_bytes"] != 2940 or
            manifest["opaque_bytes"] != 17912):
        raise ValueError("graphics action structure coverage differs")
    for fragment in fragments:
        if reconstruct_fragment(manifest, output, fragment["start"]) != rom[
                fragment["start"]:fragment["start"] + fragment["size"]]:
            raise ValueError("graphics action fragment does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"record_count": len(records), "command_count": manifest["command_count"],
            "fragment_count": len(fragments), "structured_bytes": manifest["structured_bytes"],
            "opaque_bytes": manifest["opaque_bytes"], "manifest_sha256": sha256(path.read_bytes())}


def fragment_entry(manifest, offset):
    matches = [fragment for fragment in manifest["fragments"] if fragment["start"] == offset]
    if len(matches) != 1:
        raise ValueError("graphics action fragment is not unique")
    return matches[0]


def fragment_source_file(manifest, offset, source_dir):
    fragment = fragment_entry(manifest, offset)
    record = next(record for record in manifest["records"]
                  if record["start"] == fragment["record_start"])
    return source_dir / "records" / record["file"]


def reconstruct_fragment(manifest, source_dir, offset):
    fragment = fragment_entry(manifest, offset)
    record = next(record for record in manifest["records"]
                  if record["start"] == fragment["record_start"])
    rebuilt, covered = serialize_selected(record, source_dir / "records" / record["file"])
    first = offset - record["start"]
    last = first + fragment["size"]
    if not all(covered[first:last]):
        raise ValueError("graphics action fragment contains unstructured bytes")
    data = rebuilt[first:last]
    if sha256(data) != fragment["source_sha256"]:
        raise ValueError(f"graphics action fragment differs at 0x{offset:08x}")
    return data


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("graphics action export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
