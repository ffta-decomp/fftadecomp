#!/usr/bin/env python3
"""Extract and rebuild the scene coordinate-path table without ROM byte copying."""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0xA19D18
END = 0xA1A908
RECORD_COUNT = 210


def extract(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    offsets = struct.unpack_from("<" + "I" * RECORD_COUNT, rom, START)
    if offsets[0] != 4 * RECORD_COUNT:
        raise ValueError("coordinate-path offset table has a different extent")
    records = []
    cursor = 4 * RECORD_COUNT
    for offset in offsets:
        if offset != cursor or START + offset + 2 > END:
            raise ValueError("coordinate-path offsets are not contiguous")
        count = struct.unpack_from("<H", rom, START + offset)[0]
        pair_start = START + offset + 2
        pair_end = pair_start + 2 * count
        if pair_end > END:
            raise ValueError("coordinate-path record exceeds the table")
        pairs = [list(rom[position:position + 2])
                 for position in range(pair_start, pair_end, 2)]
        cursor = pair_end - START
        alignment = (-cursor) % 4
        if rom[START + cursor:START + cursor + alignment] != b"\xff" * alignment:
            raise ValueError("coordinate-path alignment differs")
        cursor += alignment
        records.append({"offset": offset, "count": count, "pairs": pairs})
    if START + cursor != END:
        raise ValueError("coordinate-path table leaves unclassified bytes")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "start": START, "end": END, "record_count": RECORD_COUNT,
            "records": records}


def encode(asset):
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("start"), asset.get("end")) != (START, END) or
            asset.get("record_count") != RECORD_COUNT or
            len(asset.get("records", [])) != RECORD_COUNT):
        raise ValueError("coordinate-path metadata differs")
    offsets = []
    payload = bytearray()
    cursor = 4 * RECORD_COUNT
    for record in asset["records"]:
        pairs = record.get("pairs")
        if (type(record.get("offset")) is not int or record["offset"] != cursor or
                type(record.get("count")) is not int or
                not isinstance(pairs, list) or record["count"] != len(pairs) or
                not 0 <= record["count"] <= 0xFFFF):
            raise ValueError("coordinate-path count or offset differs")
        offsets.append(cursor)
        payload.extend(struct.pack("<H", len(pairs)))
        for pair in pairs:
            if (not isinstance(pair, list) or len(pair) != 2 or
                    any(type(value) is not int or not 0 <= value <= 0xFF
                        for value in pair)):
                raise ValueError("coordinate-path coordinate is not a byte pair")
            payload.extend(pair)
        cursor = 4 * RECORD_COUNT + len(payload)
        payload.extend(b"\xff" * ((-cursor) % 4))
        cursor = 4 * RECORD_COUNT + len(payload)
    result = struct.pack("<" + "I" * RECORD_COUNT, *offsets) + payload
    if len(result) != END - START:
        raise ValueError("coordinate-path table changed its physical extent")
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output == root or root in output.parents:
        parser.error("extracted assets must be outside the source tree")
    rom = args.rom.read_bytes()
    asset = extract(rom)
    rebuilt = encode(asset)
    if rebuilt != rom[START:END]:
        raise ValueError("coordinate-path roundtrip differs from retail")
    typed_bytes = 4 * RECORD_COUNT + sum(2 + 2 * record["count"]
                                         for record in asset["records"])
    alignment_bytes = len(rebuilt) - typed_bytes
    if alignment_bytes != 84:
        raise ValueError("coordinate-path alignment total differs")
    output.mkdir(parents=True, exist_ok=True)
    (output / "manifest.json").write_text(json.dumps(asset, indent=2) + "\n")
    print(json.dumps({"records": RECORD_COUNT, "table_bytes": len(rebuilt),
                      "typed_bytes": typed_bytes,
                      "alignment_bytes": alignment_bytes,
                      "sha256": hashlib.sha256(rebuilt).hexdigest()}))


if __name__ == "__main__":
    main()
