#!/usr/bin/env python3
"""Losslessly encode the bounded object-frame and animation record bank."""

import argparse
import hashlib
import json
import struct
from pathlib import Path

from catalog_unclassified_object_assets import catalog
from extract_object_animation_resources import ROM_SHA256


def _pack_table(records, offset_width, record_width):
    if not isinstance(records, list) or not records:
        raise ValueError("object table records are missing")
    if len(records) * offset_width > 0xFFFF:
        raise ValueError("object table directory exceeds u16 range")
    output = bytearray(len(records) * offset_width)
    offset_format = "<H" if offset_width == 2 else "<I"
    for index, record in enumerate(records):
        if not isinstance(record, list) or len(record) > 0xFFFF:
            raise ValueError("invalid object record count")
        struct.pack_into(offset_format, output, index * offset_width, len(output))
        output.extend(struct.pack("<H", len(record)))
        for item in record:
            if not isinstance(item, list) or len(item) != record_width // 2:
                raise ValueError("invalid object record width")
            if any(type(value) is not int or not 0 <= value <= 0xFFFF
                   for value in item):
                raise ValueError("object halfword is outside u16")
            output.extend(struct.pack("<" + "H" * len(item), *item))
        if offset_width == 4 and index + 1 < len(records):
            output.extend(bytes((-len(output)) % 4))
    return bytes(output)


def decode_resource(rom, row):
    """Return editable halfword arrays, including compact step bytes separately."""
    start = row["rom_start"]
    end = row["rom_end_exclusive"]
    flags, second_relative = struct.unpack_from("<HH", rom, start)
    if flags != row["flags"] or start + second_relative != row["secondary_table_start"]:
        raise ValueError("object header differs from catalog")

    from catalog_unclassified_object_assets import parse_table

    frame_end, _, frame_values, _ = parse_table(rom, start + 4, 2, 6)
    if frame_end != row["first_table_end"]:
        raise ValueError("object frame table boundary differs")
    second_start = row["secondary_table_start"]
    if rom[frame_end:second_start] != bytes(second_start - frame_end):
        raise ValueError("object inter-table alignment differs")
    wide = flags == 4
    sequence_end, _, sequence_values, _ = parse_table(
        rom, second_start, 4 if wide else 2, 4 if wide else 2)
    if sequence_end != end:
        raise ValueError("object sequence table boundary differs")
    frames = [[list(values[index:index + 3])
               for index in range(0, len(values), 3)]
              for values in frame_values]
    sequences = []
    for values in sequence_values:
        if wide:
            sequences.append([[values[index], values[index + 1]]
                              for index in range(0, len(values), 2)])
        else:
            sequences.append([[word & 0xFF, word >> 8] for word in values])
    return {"schema_version": 2, "reference_sha256": ROM_SHA256,
            "rom_start": start, "rom_end_exclusive": end, "flags": flags,
            "frames": frames, "sequences": sequences}


def encode_resource(asset, row):
    """Rebuild one span and its following zero alignment without source bytes."""
    if (asset.get("schema_version") != 2 or
            asset.get("reference_sha256") != ROM_SHA256 or
            asset.get("rom_start") != row["rom_start"] or
            asset.get("rom_end_exclusive") != row["rom_end_exclusive"] or
            asset.get("flags") != row["flags"]):
        raise ValueError("object asset metadata differs")
    frames = asset.get("frames")
    sequences = asset.get("sequences")
    if (not isinstance(frames, list) or len(frames) != row["frame_count"] or
            not isinstance(sequences, list) or len(sequences) != row["sequence_count"]):
        raise ValueError("object frame or sequence count differs")

    primary = _pack_table(frames, 2, 6)
    if row["rom_start"] + 4 + len(primary) != row["first_table_end"]:
        raise ValueError("object frame table changed physical extent")
    inter_alignment = row["inter_table_alignment_bytes"]
    second_relative = 4 + len(primary) + inter_alignment
    if row["rom_start"] + second_relative != row["secondary_table_start"]:
        raise ValueError("object secondary table changed address")
    wide = row["flags"] == 4
    second_records = []
    for steps in sequences:
        if not isinstance(steps, list):
            raise ValueError("object sequence steps are missing")
        encoded_steps = []
        for step in steps:
            if (not isinstance(step, list) or len(step) != 2 or
                    any(type(value) is not int or value < 0 or
                        value > (0xFFFF if wide else 0xFF) for value in step)):
                raise ValueError("object sequence step exceeds storage width")
            frame_index, duration = step
            if frame_index >= len(frames):
                raise ValueError("object sequence references absent frame")
            encoded_steps.append(step if wide else [frame_index | (duration << 8)])
        second_records.append(encoded_steps)
    secondary = _pack_table(second_records, 4 if wide else 2,
                            4 if wide else 2)
    span = (struct.pack("<HH", row["flags"], second_relative) + primary +
            bytes(inter_alignment) + secondary)
    if len(span) != row["span_bytes"]:
        raise ValueError("object resource changed physical extent")
    return span + bytes(row["following_alignment_bytes"])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--catalog", type=Path,
                        default=Path(__file__).resolve().parents[1] /
                        "config/unclassified-object-assets.json")
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output == root or output.is_relative_to(root):
        parser.error("extracted assets must remain outside the source tree")
    rom = args.rom.read_bytes()
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    expected = json.loads(args.catalog.read_text())
    actual = catalog(rom)
    if expected != actual:
        raise ValueError("object address catalog differs from pinned ROM")
    output.mkdir(parents=True, exist_ok=True)
    rows = []
    for row in expected["resources"]:
        asset = decode_resource(rom, row)
        rebuilt = encode_resource(asset, row)
        start = row["rom_start"]
        if rebuilt != rom[start:start + len(rebuilt)]:
            raise ValueError("object asset does not round-trip")
        file = f"{start:08x}.json"
        (output / file).write_text(json.dumps(asset, indent=2) + "\n")
        rows.append({"rom_start": start, "file": file,
                     "sha256": hashlib.sha256(rebuilt).hexdigest()})
    (output / "manifest.json").write_text(json.dumps({
        "schema_version": 2, "reference_sha256": ROM_SHA256,
        "resources": rows}, indent=2) + "\n")
    print(json.dumps({"resources": len(rows),
                      "bytes": sum(row["span_bytes"] + row["following_alignment_bytes"]
                                   for row in expected["resources"])}))


if __name__ == "__main__":
    main()
