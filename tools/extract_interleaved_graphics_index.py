#!/usr/bin/env python3
"""Export the indexed four-byte records before the 44-entry A7 archive."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x3b8f50
END = 0x3b9004
RECORD_COUNT = 45
CALLER_LITERAL = 0xcba38
NEXT_ARCHIVE_LITERAL = 0xcba10


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_index(manifest):
    records = manifest["record_nibbles"]
    if (manifest["start"] != START or manifest["end"] != END or
            len(records) != RECORD_COUNT or
            any(len(record) != 8 or any(type(value) is not int or not 0 <= value <= 15
                for value in record) for record in records)):
        raise ValueError("interleaved graphics index shape differs")
    encoded = bytes(record[index] | record[index + 1] << 4
                    for record in records for index in range(0, 8, 2))
    if len(encoded) != END - START or sha256(encoded) != manifest["source_sha256"]:
        raise ValueError("interleaved graphics index differs from retail")
    return encoded


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("interleaved graphics index output must be outside the source tree")
    if (int.from_bytes(rom[CALLER_LITERAL:CALLER_LITERAL + 4], "little") != ROM_BASE + START or
            int.from_bytes(rom[NEXT_ARCHIVE_LITERAL:NEXT_ARCHIVE_LITERAL + 4], "little") != ROM_BASE + END):
        raise ValueError("interleaved graphics index caller or following archive differs")
    data = rom[START:END]
    if len(data) != 4 * RECORD_COUNT:
        raise ValueError("interleaved graphics index count differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "record_count": RECORD_COUNT,
                "record_nibbles": [[(value >> shift) & 15
                                    for value in data[pos:pos + 4]
                                    for shift in (0, 4)]
                                   for pos in range(0, len(data), 4)],
                "caller_literal": CALLER_LITERAL,
                "next_archive_literal": NEXT_ARCHIVE_LITERAL,
                "source_sha256": sha256(data),
                "scope_note": "Retail code indexes four-byte records with a one-based value and reads the first byte's high nibble. Other nibbles remain uninterpreted."}
    if encode_index(manifest) != data:
        raise ValueError("interleaved graphics index does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": RECORD_COUNT, "source_bytes": len(data),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
