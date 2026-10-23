#!/usr/bin/env python3
"""Export bounded residual tilemaps and a shared opening halfword prefix."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_opening_tilemaps import decode_cell, encode_cell

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
SMALL_START = 0x9551f2
SMALL_END = 0x955250
PREFIX_START = 0x99f25c
PREFIX_END = 0x99f31c
SMALL_MAPS = ((0x9551f4, 3, 10, 0x38b54), (0x955230, 4, 4, 0x38b28))
PREFIX_LITERAL = 0x140cd8
PREFIX_COPY_LAST_INDEX = 0x257


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_small_maps(manifest, source_dir, verify_hash=True):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            len(manifest["small_maps"]) != len(SMALL_MAPS) or
            manifest["small_padding_bytes"] != 2):
        raise ValueError("residual tilemap revision or layout differs")
    output = bytearray(b"\0\0")
    for entry, (start, rows, columns, literal) in zip(manifest["small_maps"], SMALL_MAPS):
        if (entry["start"], entry["rows"], entry["columns"], entry["literal"]) != (
                start, rows, columns, literal) or SMALL_START + len(output) != start:
            raise ValueError("residual tilemap boundary differs")
        fields = json.loads((source_dir / entry["file"]).read_text())["rows"]
        if len(fields) != rows or any(len(row) != columns for row in fields):
            raise ValueError("residual tilemap dimensions differ")
        encoded = b"".join(encode_cell(cell).to_bytes(2, "little") for row in fields for cell in row)
        if verify_hash and sha256(encoded) != entry["source_sha256"]:
            raise ValueError("residual tilemap differs from retail")
        output += encoded
    data = bytes(output)
    if len(data) != SMALL_END - SMALL_START or (
            verify_hash and sha256(data) != manifest["small_run_sha256"]):
        raise ValueError("residual tilemap run differs from retail")
    return data


def encode_prefix(manifest, source_dir, verify_hash=True):
    if manifest["reference_sha256"] != ROM_SHA256:
        raise ValueError("opening halfword prefix revision differs")
    values = json.loads((source_dir / manifest["prefix_file"]).read_text())["halfwords"]
    if len(values) != (PREFIX_END - PREFIX_START) // 2 or any(
            type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("opening halfword prefix count or value differs")
    data = b"".join(value.to_bytes(2, "little") for value in values)
    if verify_hash and sha256(data) != manifest["prefix_sha256"]:
        raise ValueError("opening halfword prefix differs from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("residual map export must be outside the source tree")
    if rom[SMALL_START:SMALL_START + 2] != b"\0\0":
        raise ValueError("residual map leading alignment differs")
    if (int.from_bytes(rom[PREFIX_LITERAL:PREFIX_LITERAL + 4], "little") != ROM_BASE + PREFIX_START or
            int.from_bytes(rom[0x140cdc:0x140ce0], "little") != PREFIX_COPY_LAST_INDEX):
        raise ValueError("opening halfword source or copy limit differs")
    output.mkdir(parents=True, exist_ok=True)
    small_maps = []
    expected_start = SMALL_START + 2
    for index, (start, rows, columns, literal) in enumerate(SMALL_MAPS):
        size = rows * columns * 2
        if (start != expected_start or
                int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start):
            raise ValueError("residual tilemap caller or boundary differs")
        data = rom[start:start + size]
        values = [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, size, 2)]
        file_name = f"small-map-{index}.json"
        (output / file_name).write_text(json.dumps({"rows": [
            [decode_cell(value) for value in values[row * columns:(row + 1) * columns]]
            for row in range(rows)]}, separators=(",", ":")) + "\n")
        small_maps.append({"start": start, "rows": rows, "columns": columns,
                           "literal": literal, "file": file_name,
                           "source_sha256": sha256(data)})
        expected_start += size
    if expected_start != SMALL_END:
        raise ValueError("residual tilemap run end differs")
    prefix = rom[PREFIX_START:PREFIX_END]
    values = [int.from_bytes(prefix[pos:pos + 2], "little") for pos in range(0, len(prefix), 2)]
    prefix_file = "low-byte-source-prefix.json"
    (output / prefix_file).write_text(json.dumps({"halfwords": values}, separators=(",", ":")) + "\n")
    manifest = {
        "reference_sha256": ROM_SHA256,
        "small_start": SMALL_START, "small_end": SMALL_END,
        "small_padding_bytes": 2, "small_run_sha256": sha256(rom[SMALL_START:SMALL_END]),
        "small_maps": small_maps,
        "prefix_start": PREFIX_START, "prefix_end": PREFIX_END,
        "prefix_file": prefix_file, "prefix_sha256": sha256(prefix),
        "prefix_copy_halfwords": PREFIX_COPY_LAST_INDEX + 1,
        "caveat": "The 600-halfword low-byte read begins at the exported 96-halfword prefix and continues into the already reconstructed BG maps. Only unique prefix bytes are selected here.",
    }
    if (encode_small_maps(manifest, output) != rom[SMALL_START:SMALL_END] or
            encode_prefix(manifest, output) != prefix):
        raise ValueError("residual maps do not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"small_map_bytes": SMALL_END - SMALL_START, "small_map_padding": 2,
            "prefix_bytes": PREFIX_END - PREFIX_START,
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
