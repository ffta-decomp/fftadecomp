#!/usr/bin/env python3
"""Export bounded graphics frame and counted sample-table tails."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_graphics_frame_resources import encode_u16
from extract_graphics_nested_frames import _encode_fields as encode_frame_sequence
from extract_pointer_lz77_records import ROM_SHA256


FRAME_TAIL = (0x94df44, 0x94dfa4)
SAMPLE_TAIL = (0x94e5b8, 0x94eae0)
SAMPLE_COUNTS = (64, 64, 240, 96, 80, 104)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_tail(entry, source_dir):
    fields = json.loads((source_dir / entry["file"]).read_text())
    if entry["format"] == "frame_and_byte_pairs":
        pairs = fields["pairs"]
        if len(pairs) != 41 or any(len(pair) != 2 or any(type(value) is not int or
                not 0 <= value <= 255 for value in pair) for pair in pairs):
            raise ValueError("graphics byte-pair table differs")
        output = encode_frame_sequence(fields["sequence"])
        output += encode_u16([len(pairs)]) + bytes(value for pair in pairs for value in pair)
    elif entry["format"] == "counted_halfword_tables":
        tables = fields["tables"]
        if len(tables) != len(SAMPLE_COUNTS):
            raise ValueError("graphics sample table count differs")
        output = bytearray()
        for index, (table, count) in enumerate(zip(tables, SAMPLE_COUNTS)):
            values = table["values"]
            if len(values) != count:
                raise ValueError("graphics sample value count differs")
            output += encode_u16([count])
            if index < 2:
                if table["marker"] != 0xf0f0:
                    raise ValueError("graphics sample marker differs")
                output += encode_u16([table["marker"]])
            output += encode_u16(values)
            if index >= 2:
                output += b"\0\0"
        output = bytes(output)
    else:
        raise ValueError("unknown graphics sample tail")
    if len(output) != entry["end"] - entry["start"] or sha256(output) != entry["source_sha256"]:
        raise ValueError("graphics sample tail differs from retail")
    return output


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    frame_start, frame_end = FRAME_TAIL
    frame_count = int.from_bytes(rom[frame_start + 4:frame_start + 6], "little")
    frame_size = 8 + 4 * frame_count
    if frame_count != 1 or frame_size != 12 or rom[frame_start + 10:frame_start + 12] != b"\0\0":
        raise ValueError("graphics nested frame boundary differs")
    at = frame_start + 6
    sequence = {"attribute0": int.from_bytes(rom[frame_start:frame_start + 2], "little"),
                "attribute1": int.from_bytes(rom[frame_start + 2:frame_start + 4], "little"),
                "frames": [{"duration": int.from_bytes(rom[at:at + 2], "little"),
                            "primary_index": rom[at + 2], "secondary_index": rom[at + 3]}]}
    pair_start = frame_start + frame_size
    pair_count = int.from_bytes(rom[pair_start:pair_start + 2], "little")
    if pair_count != 41 or pair_start + 2 + pair_count * 2 != frame_end:
        raise ValueError("graphics byte-pair boundary differs")
    pairs = [list(rom[pos:pos + 2]) for pos in range(pair_start + 2, frame_end, 2)]
    first_fields = {"sequence": sequence, "pairs": pairs}

    sample_start, sample_end = SAMPLE_TAIL
    cursor = sample_start
    tables = []
    for index, expected_count in enumerate(SAMPLE_COUNTS):
        count = int.from_bytes(rom[cursor:cursor + 2], "little")
        if count != expected_count:
            raise ValueError("graphics sample count differs")
        cursor += 2
        table = {}
        if index < 2:
            table["marker"] = int.from_bytes(rom[cursor:cursor + 2], "little")
            if table["marker"] != 0xf0f0:
                raise ValueError("graphics sample marker differs")
            cursor += 2
        table["values"] = [int.from_bytes(rom[pos:pos + 2], "little")
                           for pos in range(cursor, cursor + 2 * count, 2)]
        cursor += 2 * count
        if index >= 2:
            if rom[cursor:cursor + 2] != b"\0\0":
                raise ValueError("graphics sample alignment differs")
            cursor += 2
        tables.append(table)
    if cursor != sample_end:
        raise ValueError("graphics sample tail boundary differs")
    specs = [(FRAME_TAIL, "frame_and_byte_pairs", first_fields),
             (SAMPLE_TAIL, "counted_halfword_tables", {"tables": tables})]
    entries = []
    for (start, end), format_name, fields in specs:
        name = f"tail-0x{start:06x}.json"
        (output / name).write_text(json.dumps(fields, indent=2) + "\n")
        entry = {"start": start, "end": end, "format": format_name,
                 "file": name, "source_sha256": sha256(rom[start:end]),
                 "padding_bytes": 8 if format_name == "counted_halfword_tables" else 2}
        if encode_tail(entry, output) != rom[start:end]:
            raise ValueError("graphics sample tail does not round-trip")
        entries.append(entry)
    manifest = {"reference_sha256": ROM_SHA256, "entries": entries,
                "selected_bytes": sum(entry["end"] - entry["start"] for entry in entries),
                "padding_bytes": sum(entry["padding_bytes"] for entry in entries),
                "scope_note": "Only counted fields and observed alignment are represented; rendered meaning is unresolved."}
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"tails": len(entries), "selected_bytes": manifest["selected_bytes"],
            "padding_bytes": manifest["padding_bytes"], "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("graphics sample-tail export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
