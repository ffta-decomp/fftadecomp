#!/usr/bin/env python3
"""Export the four-nibble records indexed beside the item icon archive."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x3c7fe4
END = 0x3c83fc
ARCHIVE_START = END
RECORD_COUNT = 522
CALLER_LITERAL = 0xcb9ac
ARCHIVE_LITERAL = 0xcb998


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_index_fields(manifest):
    if manifest["start"] != START or manifest["end"] != END:
        raise ValueError("item icon field boundary differs")
    header = manifest["header_halfwords"]
    records = manifest["record_nibbles"]
    if (len(header) != 2 or len(records) != RECORD_COUNT or
            any(type(value) is not int or not 0 <= value <= 65535 for value in header) or
            any(len(record) != 4 or any(type(value) is not int or not 0 <= value <= 15
                for value in record) for record in records)):
        raise ValueError("item icon field shape differs")
    output = bytearray()
    for value in header:
        output.extend(value.to_bytes(2, "little"))
    for low0, high0, low1, high1 in records:
        output.extend((low0 | high0 << 4, low1 | high1 << 4))
    if len(output) != END - START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("item icon field bytes differ from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("item icon field output must be outside the source tree")
    if (int.from_bytes(rom[CALLER_LITERAL:CALLER_LITERAL + 4], "little") != ROM_BASE + START or
            int.from_bytes(rom[ARCHIVE_LITERAL:ARCHIVE_LITERAL + 4], "little") != ROM_BASE + ARCHIVE_START):
        raise ValueError("item icon field/archive caller differs")
    data = rom[START:END]
    if len(data) != 4 + RECORD_COUNT * 2:
        raise ValueError("item icon field count differs")
    manifest = {
        "reference_sha256": ROM_SHA256, "start": START, "end": END,
        "header_halfwords": [int.from_bytes(data[index:index + 2], "little")
                             for index in (0, 2)],
        "record_count": RECORD_COUNT,
        "record_nibbles": [[data[index] & 15, data[index] >> 4,
                            data[index + 1] & 15, data[index + 1] >> 4]
                           for index in range(4, len(data), 2)],
        "caller_literal": CALLER_LITERAL, "archive_literal": ARCHIVE_LITERAL,
        "source_sha256": sha256(data),
        "scope_note": "The caller indexes two-byte records after a four-byte header and reads the high nibble of the first byte. Other nibble meanings are unresolved.",
    }
    if encode_index_fields(manifest) != data:
        raise ValueError("item icon field export does not round-trip")
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
