#!/usr/bin/env python3
"""Export pointer-indexed opening tilemap frames and their descriptor table."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_opening_tilemaps import decode_cell, encode_cell

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TABLE_START = 0x3a932c
TABLE_END = 0x3a93a4
MAP_START = 0x99a39c
MAP_END = 0x99f25c
ENTRY_COUNT = 15
ROW_WIDTH = 30
POINTER_LITERALS = (0x140810, 0x1408b4, 0x1408e0)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_table(manifest, verify_hash=True):
    if manifest["reference_sha256"] != ROM_SHA256 or len(manifest["entries"]) != ENTRY_COUNT:
        raise ValueError("opening indexed-map table revision or count differs")
    output = bytearray()
    for entry in manifest["entries"]:
        start = entry["start"]
        field_04 = entry["field_04"]
        if (type(start) is not int or not MAP_START <= start < MAP_END or
                type(field_04) is not int or not 0 <= field_04 <= 0xffffffff):
            raise ValueError("opening indexed-map descriptor field differs")
        output += (ROM_BASE + start).to_bytes(4, "little")
        output += field_04.to_bytes(4, "little")
    data = bytes(output)
    if len(data) != TABLE_END - TABLE_START or (
            verify_hash and sha256(data) != manifest["table_sha256"]):
        raise ValueError("opening indexed-map table differs from retail")
    return data


def encode_maps(manifest, source_dir, verify_hash=True):
    if manifest["reference_sha256"] != ROM_SHA256 or len(manifest["entries"]) != ENTRY_COUNT:
        raise ValueError("opening indexed-map revision or count differs")
    output = bytearray()
    expected_start = MAP_START
    for index, entry in enumerate(manifest["entries"]):
        rows = 20 if index < 12 else 32
        if (entry["start"] != expected_start or entry["rows"] != rows or
                entry["columns"] != ROW_WIDTH or entry["file"] != f"map-{index}.json"):
            raise ValueError("opening indexed-map boundary or shape differs")
        fields = json.loads((source_dir / entry["file"]).read_text())["rows"]
        if len(fields) != rows or any(len(row) != ROW_WIDTH for row in fields):
            raise ValueError("opening indexed-map dimensions differ")
        data = b"".join(encode_cell(cell).to_bytes(2, "little") for row in fields for cell in row)
        if verify_hash and sha256(data) != entry["source_sha256"]:
            raise ValueError("opening indexed-map frame differs from retail")
        output += data
        expected_start += len(data)
    data = bytes(output)
    if expected_start != MAP_END or (verify_hash and sha256(data) != manifest["map_run_sha256"]):
        raise ValueError("opening indexed-map run differs from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening indexed-map output must be outside the source tree")
    if any(int.from_bytes(rom[p:p + 4], "little") != ROM_BASE + TABLE_START
           for p in POINTER_LITERALS):
        raise ValueError("opening indexed-map callers no longer reference the table")
    if int.from_bytes(rom[TABLE_END:TABLE_END + 4], "little") != 0x08140311:
        raise ValueError("opening indexed-map table terminator differs")
    output.mkdir(parents=True, exist_ok=True)
    entries = []
    expected_start = MAP_START
    for index in range(ENTRY_COUNT):
        table_offset = TABLE_START + index * 8
        start = int.from_bytes(rom[table_offset:table_offset + 4], "little") - ROM_BASE
        field_04 = int.from_bytes(rom[table_offset + 4:table_offset + 8], "little")
        rows = 20 if index < 12 else 32
        size = rows * ROW_WIDTH * 2
        if start != expected_start:
            raise ValueError("opening indexed-map pointer sequence differs")
        data = rom[start:start + size]
        values = [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, size, 2)]
        name = f"map-{index}.json"
        (output / name).write_text(json.dumps({"rows": [
            [decode_cell(value) for value in values[row * ROW_WIDTH:(row + 1) * ROW_WIDTH]]
            for row in range(rows)]}, separators=(",", ":")) + "\n")
        entries.append({"start": start, "rows": rows, "columns": ROW_WIDTH,
                        "field_04": field_04, "file": name, "source_sha256": sha256(data)})
        expected_start += size
    if expected_start != MAP_END:
        raise ValueError("opening indexed-map run end differs")
    manifest = {
        "reference_sha256": ROM_SHA256, "table_start": TABLE_START, "table_end": TABLE_END,
        "table_sha256": sha256(rom[TABLE_START:TABLE_END]),
        "map_start": MAP_START, "map_end": MAP_END,
        "map_run_sha256": sha256(rom[MAP_START:MAP_END]),
        "entries": entries,
        "consumer": 0x08140832,
        "caveat": "The three callers index eight-byte pointer records. Field_04 is preserved without a game-semantic name. The 30-column source grouping round-trips, while destination placement and final image composition remain unresolved.",
    }
    if (encode_table(manifest) != rom[TABLE_START:TABLE_END] or
            encode_maps(manifest, output) != rom[MAP_START:MAP_END]):
        raise ValueError("opening indexed-map export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"entries": len(entries), "table_bytes": TABLE_END - TABLE_START,
            "map_bytes": MAP_END - MAP_START,
            "cells": sum(entry["rows"] * entry["columns"] for entry in entries),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
