#!/usr/bin/env python3
"""Export the 32 offset-indexed color rows copied by the retail renderer."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
BANK_START = 0x425104
BANK_END = 0x427a04
CALLER_LITERAL_SITES = (0x1d9bc, 0x1dcb4)
RECORD_COUNT = 32
ROW_COLORS = 160
HEADER_BYTES = 6
RECORD_BYTES = HEADER_BYTES + ROW_COLORS * 2


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def halfwords(data):
    if len(data) % 2:
        raise ValueError("indexed color data is not halfword-aligned")
    return [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, len(data), 2)]


def encode_halfwords(values):
    if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("indexed color halfword differs")
    return b"".join(value.to_bytes(2, "little") for value in values)


def encode_bank(manifest):
    if (manifest["start"] != BANK_START or manifest["end"] != BANK_END or
            len(manifest["records"]) != RECORD_COUNT):
        raise ValueError("indexed color bank boundary differs")
    output = bytearray()
    for index, record in enumerate(manifest["records"]):
        expected_start = BANK_START + 2 * RECORD_COUNT + index * RECORD_BYTES
        if record["start"] != expected_start:
            raise ValueError("indexed color record offset differs")
        output += encode_halfwords([expected_start - BANK_START])
    for record in manifest["records"]:
        if BANK_START + len(output) != record["start"]:
            raise ValueError("indexed color record position differs")
        if record["header"] != [ROW_COLORS, ROW_COLORS, 0] or len(record["bgr555"]) != ROW_COLORS:
            raise ValueError("indexed color row header or width differs")
        output += encode_halfwords(record["header"] + record["bgr555"])
    if len(output) != BANK_END - BANK_START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("indexed color bank differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed color output must be outside the source tree")
    for site in CALLER_LITERAL_SITES:
        if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + BANK_START:
            raise ValueError("indexed color caller differs")
    if BANK_END - BANK_START != 2 * RECORD_COUNT + RECORD_COUNT * RECORD_BYTES:
        raise ValueError("indexed color bank size differs")
    offsets = halfwords(rom[BANK_START:BANK_START + 2 * RECORD_COUNT])
    expected = [2 * RECORD_COUNT + index * RECORD_BYTES for index in range(RECORD_COUNT)]
    if offsets != expected:
        raise ValueError("indexed color offset table differs")
    records = []
    for offset in offsets:
        start = BANK_START + offset
        values = halfwords(rom[start:start + RECORD_BYTES])
        if values[:3] != [ROW_COLORS, ROW_COLORS, 0] or any(value & 0x8000 for value in values[3:]):
            raise ValueError("indexed color record shape differs")
        records.append({"start": start, "header": values[:3], "bgr555": values[3:]})
    manifest = {"reference_sha256": ROM_SHA256, "start": BANK_START, "end": BANK_END,
                "record_count": RECORD_COUNT, "record_bytes": RECORD_BYTES,
                "caller_literal_sites": CALLER_LITERAL_SITES,
                "source_sha256": sha256(rom[BANK_START:BANK_END]), "records": records,
                "scope_note": "The retail caller copies 160 halfwords after each six-byte header; screen placement remains unresolved."}
    if encode_bank(manifest) != rom[BANK_START:BANK_END]:
        raise ValueError("indexed color export does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": RECORD_COUNT, "source_bytes": BANK_END - BANK_START,
            "colors_per_record": ROW_COLORS, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
