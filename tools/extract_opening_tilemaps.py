#!/usr/bin/env python3
"""Export eight directly consumed opening screen-entry tilemaps."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x998e60
END = 0x99a39c

# The caller passes each count and source pointer to 0x0813fb0c. The helper
# writes 16-bit entries into 32-column rows, adding a caller-supplied tile base.
MAPS = (
    (0x998e60, 16, 12, 0x13f9f0, bytes.fromhex("c0 22 0c 23")),
    (0x998fe0, 17, 10, 0x13f92c, bytes.fromhex("aa 22 0a 23")),
    (0x999134, 14, 15, 0x13fd70, bytes.fromhex("d2 22 0f 23")),
    (0x9992d8, 11, 22, 0x13f88c, bytes.fromhex("f2 22 16 23")),
    (0x9994bc, 32, 10, 0x13f764, bytes.fromhex("a0 22 52 00")),
    (0x99973c, 32, 12, 0x13fcdc, bytes.fromhex("c0 22 52 00")),
    (0x999a3c, 20, 30, 0x13f774, bytes.fromhex("96 22 92 00")),
    (0x999eec, 20, 30, 0x13fc78, bytes.fromhex("96 22 92 00")),
)
COUNT_SITES = (0x13f9a6, 0x13f8f2, 0x13fd3a, 0x13f838,
               0x13f684, 0x13fcb2, 0x13f6be, 0x13fc44)
WIDTH_SITES = (0x13f9a8, 0x13f8f4, 0x13fd3c, 0x13f83a,
               0x13f68c, 0x13fcba, 0x13f6c4, 0x13fc4c)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode_cell(value):
    return {"tile_offset": value & 0x3ff,
            "horizontal_flip": bool(value & 0x400),
            "vertical_flip": bool(value & 0x800),
            "palette_index": value >> 12}


def encode_cell(cell):
    tile = cell["tile_offset"]
    palette = cell["palette_index"]
    hflip = cell["horizontal_flip"]
    vflip = cell["vertical_flip"]
    if (type(tile) is not int or not 0 <= tile <= 1023 or
            type(palette) is not int or not 0 <= palette <= 15 or
            type(hflip) is not bool or type(vflip) is not bool):
        raise ValueError("opening tilemap entry field differs")
    return tile | int(hflip) << 10 | int(vflip) << 11 | palette << 12


def encode_map(entry, source_dir, verify_hash=True):
    spec = next((spec for spec in MAPS if spec[0] == entry["start"]), None)
    if spec is None or (entry["rows"], entry["columns"], entry["literal"]) != spec[1:4]:
        raise ValueError("opening tilemap shape or pointer differs")
    rows = json.loads((source_dir / entry["file"]).read_text())["rows"]
    if len(rows) != spec[1] or any(len(row) != spec[2] for row in rows):
        raise ValueError("opening tilemap dimensions differ")
    data = b"".join(encode_cell(cell).to_bytes(2, "little") for row in rows for cell in row)
    if len(data) != spec[1] * spec[2] * 2 or (verify_hash and sha256(data) != entry["source_sha256"]):
        raise ValueError("opening tilemap differs from retail")
    return data


def encode_run(manifest, source_dir, verify_hash=True):
    if manifest["reference_sha256"] != ROM_SHA256 or len(manifest["maps"]) != len(MAPS):
        raise ValueError("opening tilemap revision or count differs")
    data = bytearray()
    offset = START
    for entry, spec in zip(manifest["maps"], MAPS):
        if entry["start"] != offset or entry["start"] != spec[0]:
            raise ValueError("opening tilemap boundary differs")
        encoded = encode_map(entry, source_dir, verify_hash)
        data += encoded
        offset += len(encoded)
    if offset != END or (verify_hash and sha256(data) != manifest["source_sha256"]):
        raise ValueError("opening tilemap run differs from retail")
    return bytes(data)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening tilemap output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    entries = []
    expected_start = START
    for index, (spec, count_site, width_site) in enumerate(zip(MAPS, COUNT_SITES, WIDTH_SITES)):
        start, rows, columns, literal, count_opcode = spec
        size = rows * columns * 2
        if start != expected_start or int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start:
            raise ValueError("opening tilemap pointer or boundary differs")
        if rom[count_site:count_site + len(count_opcode)] != count_opcode:
            raise ValueError("opening tilemap caller count differs")
        if rom[width_site:width_site + 2] != bytes((columns, 0x23)):
            raise ValueError("opening tilemap caller row width differs")
        data = rom[start:start + size]
        values = [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, size, 2)]
        name = f"map-{index}.json"
        (output / name).write_text(json.dumps({"rows": [
            [decode_cell(value) for value in values[row * columns:(row + 1) * columns]]
            for row in range(rows)]}, separators=(",", ":")) + "\n")
        entries.append({"start": start, "rows": rows, "columns": columns,
                        "literal": literal, "file": name, "source_sha256": sha256(data)})
        expected_start += size
    if expected_start != END:
        raise ValueError("opening tilemap run end differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "source_sha256": sha256(rom[START:END]), "maps": entries,
                "consumer": 0x0813fb0c,
                "caveat": "These are source screen-entry fields before the caller adds a tile base. Destination placement and final image composition are unresolved."}
    if encode_run(manifest, output) != rom[START:END]:
        raise ValueError("opening tilemap export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"maps": len(entries), "cells": sum(e["rows"] * e["columns"] for e in entries),
            "source_bytes": END - START, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
