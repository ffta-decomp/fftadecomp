#!/usr/bin/env python3
"""Export the 19 pointer-indexed halfword blocks beside scene data."""

import argparse
import hashlib
import json
import struct
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TABLE_START = 0x3A832C
TABLE_END = 0x3A8410
DATA_START = 0xA3311C
DATA_END = 0xA38A2C
COUNT = 19
BLOCK_BYTES = 1200
TABLE_LITERAL = 0x12BE14
FOLLOWING_LITERAL = 0x12C1F4


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def validate_manifest(manifest):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["table_start"] != TABLE_START or
            manifest["table_end"] != TABLE_END or
            manifest["data_start"] != DATA_START or
            manifest["data_end"] != DATA_END or
            len(manifest["records"]) != COUNT):
        raise ValueError("indexed halfword map revision or boundary differs")


def encode_table(manifest, verify_hash=True):
    validate_manifest(manifest)
    output = bytearray()
    cumulative_end = 0
    for index, record in enumerate(manifest["records"]):
        expected_start = DATA_START + index * BLOCK_BYTES
        if (record["index"] != index or record["map_start"] != expected_start or
                record["cumulative_offset"] != cumulative_end or
                type(record["range_length"]) is not int or
                not 0 <= record["range_length"] <= 0xffffffff):
            raise ValueError("indexed halfword map descriptor differs")
        output += struct.pack("<III", cumulative_end, record["range_length"],
                              ROM_BASE + expected_start)
        cumulative_end += record["range_length"]
        if cumulative_end > 0xffffffff:
            raise ValueError("indexed halfword map cumulative range overflows")
    data = bytes(output)
    if len(data) != TABLE_END - TABLE_START or (
            verify_hash and sha256(data) != manifest["table_sha256"]):
        raise ValueError("indexed halfword map table differs from retail")
    return data


def encode_data(manifest, source_dir, verify_hash=True):
    validate_manifest(manifest)
    output = bytearray()
    for record in manifest["records"]:
        values = json.loads((source_dir / record["file"]).read_text())["halfwords"]
        if len(values) != BLOCK_BYTES // 2 or any(
                type(value) is not int or not 0 <= value <= 0xffff for value in values):
            raise ValueError("indexed halfword map block count or value differs")
        data = struct.pack("<600H", *values)
        if verify_hash and sha256(data) != record["source_sha256"]:
            raise ValueError("indexed halfword map block differs from retail")
        output += data
    data = bytes(output)
    if len(data) != DATA_END - DATA_START or (
            verify_hash and sha256(data) != manifest["data_sha256"]):
        raise ValueError("indexed halfword map bank differs from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed halfword map export must be outside the source tree")
    if (struct.unpack_from("<I", rom, TABLE_LITERAL)[0] != ROM_BASE + TABLE_START or
            struct.unpack_from("<I", rom, FOLLOWING_LITERAL)[0] != ROM_BASE + TABLE_END or
            TABLE_END - TABLE_START != COUNT * 12 or
            DATA_END - DATA_START != COUNT * BLOCK_BYTES):
        raise ValueError("indexed halfword map anchors or sizes differ")
    output.mkdir(parents=True, exist_ok=True)
    records = []
    cumulative_end = 0
    for index in range(COUNT):
        descriptor = TABLE_START + index * 12
        cumulative_offset, range_length, pointer = struct.unpack_from("<III", rom, descriptor)
        map_start = DATA_START + index * BLOCK_BYTES
        if cumulative_offset != cumulative_end or pointer != ROM_BASE + map_start:
            raise ValueError("indexed halfword map descriptor chain differs")
        cumulative_end += range_length
        data = rom[map_start:map_start + BLOCK_BYTES]
        file_name = f"block-{index:02d}.json"
        (output / file_name).write_text(json.dumps({"halfwords": list(struct.unpack("<600H", data))},
                                                  separators=(",", ":")) + "\n")
        records.append({"index": index, "cumulative_offset": cumulative_offset,
                        "range_length": range_length, "map_start": map_start,
                        "file": file_name, "source_sha256": sha256(data)})
    manifest = {"reference_sha256": ROM_SHA256, "table_start": TABLE_START,
                "table_end": TABLE_END, "data_start": DATA_START, "data_end": DATA_END,
                "table_literal": TABLE_LITERAL, "following_literal": FOLLOWING_LITERAL,
                "table_sha256": sha256(rom[TABLE_START:TABLE_END]),
                "data_sha256": sha256(rom[DATA_START:DATA_END]), "records": records,
                "caveat": "The descriptor chain, pointers, and 600-halfword block sizes are established. The role of the halfwords and the descriptor ranges is not assigned."}
    if (encode_table(manifest) != rom[TABLE_START:TABLE_END] or
            encode_data(manifest, output) != rom[DATA_START:DATA_END]):
        raise ValueError("indexed halfword map export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": COUNT, "source_bytes": TABLE_END - TABLE_START + DATA_END - DATA_START,
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
