#!/usr/bin/env python3
"""Export pointer-selected halfword overlays used by the world-map tilemap writer."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TABLE_START = 0x391d44
TABLE_END = 0x391de4
DATA_START = 0x955eb8
DATA_END = 0x9564fc
POINTER_DATA_START = 0x955f5a
DIRECT_SOURCES = ((0x955eb8, 2, 27, 0x39718),
                  (0x955f24, 1, 27, 0x3971c))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def halfwords(data):
    if len(data) % 2:
        raise ValueError("world-map overlay source has an odd byte count")
    return [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, len(data), 2)]


def encode_overlay_bank(manifest):
    records = manifest["records"]
    cursor = DATA_START
    output = bytearray()
    for record in records:
        values = record["halfwords"]
        if (record["start"] != cursor or record["end"] != cursor + len(values) * 2 or
                any(type(value) is not int or not 0 <= value <= 0xffff for value in values)):
            raise ValueError("world-map overlay record boundary or halfword differs")
        encoded = b"".join(value.to_bytes(2, "little") for value in values)
        if sha256(encoded) != record["source_sha256"]:
            raise ValueError("world-map overlay record differs from retail")
        output += encoded
        cursor = record["end"]
    if cursor != DATA_END or sha256(output) != manifest["overlay_bank"]["source_sha256"]:
        raise ValueError("world-map overlay bank differs from retail")
    return bytes(output)


def encode_overlay_table(manifest):
    starts = {record["start"] for record in manifest["records"] if record["start"] >= POINTER_DATA_START}
    pointers = manifest["pointer_table"]["record_starts"]
    if len(pointers) != (TABLE_END - TABLE_START) // 4 or any(
            type(start) is not int or start not in starts for start in pointers):
        raise ValueError("world-map overlay pointer is not a record start")
    encoded = b"".join((ROM_BASE + start).to_bytes(4, "little") for start in pointers)
    if sha256(encoded) != manifest["pointer_table"]["source_sha256"]:
        raise ValueError("world-map overlay pointer table differs from retail")
    return encoded


def export(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    for start, width, height, literal in DIRECT_SOURCES:
        if int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start:
            raise ValueError("world-map overlay direct source pointer changed")
        if start + width * height * 2 > POINTER_DATA_START:
            raise ValueError("world-map overlay direct copy exceeds its source")
    for literal in (0x38f98, 0x391b4):
        if int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + TABLE_START:
            raise ValueError("world-map overlay selector no longer references the pointer table")
    pointers = [int.from_bytes(rom[pos:pos + 4], "little") - ROM_BASE
                for pos in range(TABLE_START, TABLE_END, 4)]
    starts = sorted(set(pointers))
    if not starts or starts[0] != POINTER_DATA_START or starts[-1] != 0x9564dc or any(
            start < POINTER_DATA_START or start >= DATA_END or start % 2 for start in starts):
        raise ValueError("world-map overlay pointer range changed")
    boundaries = [DATA_START, 0x955f24, POINTER_DATA_START, *starts[1:], DATA_END]
    records = []
    for start, end in zip(boundaries, boundaries[1:]):
        data = rom[start:end]
        records.append({"start": start, "end": end, "halfwords": halfwords(data),
                        "source_sha256": sha256(data)})
    manifest = {
        "reference_sha256": ROM_SHA256,
        "pointer_table": {"start": TABLE_START, "end": TABLE_END,
                          "record_starts": pointers,
                          "source_sha256": sha256(rom[TABLE_START:TABLE_END])},
        "overlay_bank": {"start": DATA_START, "end": DATA_END,
                         "source_sha256": sha256(rom[DATA_START:DATA_END])},
        "direct_sources": [{"start": start, "width": width, "height": height,
                            "literal": literal} for start, width, height, literal in DIRECT_SOURCES],
        "records": records,
        "consumer": {"halfword_writer": 0x080355e4,
                     "pointer_selectors": [0x08038f1e, 0x080390da]},
        "caveat": "Overlay source halfwords are exact; placement and final screen composition require separate validation.",
    }
    if (encode_overlay_table(manifest) != rom[TABLE_START:TABLE_END] or
            encode_overlay_bank(manifest) != rom[DATA_START:DATA_END]):
        raise ValueError("world-map overlay export does not round-trip")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    manifest = export(args.rom.read_bytes())
    args.output_dir.mkdir(parents=True, exist_ok=True)
    path = args.output_dir / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"records": len(manifest["records"]), "pointers": len(manifest["pointer_table"]["record_starts"]),
                      "source_bytes": DATA_END - DATA_START + TABLE_END - TABLE_START,
                      "manifest_sha256": sha256(path.read_bytes())}))


if __name__ == "__main__":
    main()
