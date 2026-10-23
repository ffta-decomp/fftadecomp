#!/usr/bin/env python3
"""Export fully covered nested graphics actions inside pointer-bounded roots."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_graphics_action_scripts import ARGUMENT_BYTES, serialize_selected_fields
from extract_pointer_lz77_records import ROM_SHA256

# Each prefix ends at the first unparsed payload in its pointer-bounded root.
PREFIXES = {
    0x9492dc: (1080, 108, 2),
    0x94973c: (268, 64, 3),
    0x94a320: (952, 124, 3),
    0x94a6d8: (132, 132, 2),
    0x94a75c: (852, 228, 5),
    0x94ab50: (240, 240, 3),
    0x94ac40: (160, 160, 2),
    0x94ad30: (4436, 1440, 10),
    0x94c64c: (2080, 148, 3),
}
EXPECTED_BYTES = 2644


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode_script(data, start):
    if start + 12 > len(data):
        raise ValueError("nested graphics action header is truncated")
    count = data[start + 3]
    header_end = 6 + 6 * count
    if not 1 <= count <= 64 or start + header_end > len(data):
        raise ValueError("nested graphics action command count differs")
    commands = []
    argument_ranges = []
    payload_end = header_end
    for step in range(count):
        at = start + 6 + step * 6
        opcode = data[at]
        offset = int.from_bytes(data[at + 4:at + 6], "little")
        length = ARGUMENT_BYTES.get(opcode, 0)
        if opcode > 13 or offset < header_end or start + offset + length > len(data):
            raise ValueError("nested graphics action command boundary differs")
        commands.append({"opcode": opcode, "flags": data[at + 1],
                         "duration": int.from_bytes(data[at + 2:at + 4], "little"),
                         "argument_offset": offset})
        if length:
            argument_ranges.append((offset, offset + length))
            payload_end = max(payload_end, offset + length)
    merged = []
    for first, last in sorted(argument_ranges):
        if merged and first <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(last, merged[-1][1]))
        else:
            merged.append((first, last))
    covered = bytearray(payload_end)
    covered[:header_end] = bytes([1]) * header_end
    for first, last in merged:
        covered[first:last] = bytes([1]) * (last - first)
    if not all(covered):
        raise ValueError("nested graphics action has unclassified interior bytes")
    padded_end = (payload_end + 3) & ~3
    if start + padded_end > len(data) or any(data[start + payload_end:start + padded_end]):
        raise ValueError("nested graphics action alignment differs")
    fields = {"header_prefix": list(data[start:start + 3]),
              "initial_delay": int.from_bytes(data[start + 4:start + 6], "little"),
              "commands": commands,
              "arguments": [{"offset": first, "bytes": list(data[start + first:start + last])}
                            for first, last in merged],
              "padding_bytes": padded_end - payload_end}
    return fields, padded_end


def encode_prefix(entry, source_dir):
    source = json.loads((source_dir / entry["file"]).read_text())
    if len(source["scripts"]) != entry["script_count"]:
        raise ValueError("nested graphics action script count differs")
    output = bytearray()
    for script in source["scripts"]:
        padding = script["padding_bytes"]
        if type(padding) is not int or not 0 <= padding <= 3:
            raise ValueError("nested graphics action padding differs")
        command_count = len(script["commands"])
        payload_end = max([6 + 6 * command_count] +
                          [argument["offset"] + len(argument["bytes"])
                           for argument in script["arguments"]])
        record = {"start": 0, "end": payload_end, "command_count": command_count}
        encoded, covered = serialize_selected_fields(record, script)
        if not all(covered) or (payload_end + padding) % 4:
            raise ValueError("nested graphics action contains unclassified bytes")
        output += encoded + bytes(padding)
    if len(output) != entry["end"] - entry["start"] or sha256(output) != entry["source_sha256"]:
        raise ValueError("nested graphics action prefix differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    entries = []
    for root_start, (root_bytes, prefix_bytes, expected_scripts) in PREFIXES.items():
        data = rom[root_start:root_start + root_bytes]
        cursor = 0
        scripts = []
        while cursor < prefix_bytes:
            fields, script_bytes = decode_script(data, cursor)
            cursor += script_bytes
            scripts.append(fields)
        if cursor != prefix_bytes or len(scripts) != expected_scripts:
            raise ValueError("nested graphics action prefix boundary differs")
        name = f"nested-0x{root_start:06x}.json"
        (output / name).write_text(json.dumps({"scripts": scripts}, indent=2) + "\n")
        entry = {"start": root_start, "end": root_start + prefix_bytes,
                 "root_end": root_start + root_bytes, "script_count": len(scripts),
                 "file": name, "source_sha256": sha256(data[:prefix_bytes])}
        entries.append(entry)
        if encode_prefix(entry, output) != data[:prefix_bytes]:
            raise ValueError("nested graphics action does not round-trip")
    selected_bytes = sum(entry["end"] - entry["start"] for entry in entries)
    if selected_bytes != EXPECTED_BYTES:
        raise ValueError("nested graphics action coverage differs")
    manifest = {"reference_sha256": ROM_SHA256, "entries": entries,
                "selected_bytes": selected_bytes,
                "script_count": sum(entry["script_count"] for entry in entries),
                "caveat": "Only nine fully field-covered script prefixes are selected. The rest of each pointer-bounded root remains original-byte inclusion."}
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"prefixes": len(entries), "scripts": manifest["script_count"],
            "selected_bytes": selected_bytes, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    if args.output_dir.resolve().is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("nested graphics action export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
