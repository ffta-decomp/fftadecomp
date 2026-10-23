#!/usr/bin/env python3
"""Export the 103-entry type-2 graphics layout bank beside the tile archive."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
BANK_START = 0x417f88
BANK_END = 0x418f14
CALLER_LITERAL_SITES = (0xcb948, 0xcb97c)
RECORD_COUNT = 103
HEADER_BYTES = 4 + 2 * RECORD_COUNT
EXPECTED_PADDING_BYTES = 108


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, position):
    return int.from_bytes(data[position:position + 2], "little")


def encode_u16(values):
    if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("indexed graphics layout halfword differs")
    return b"".join(value.to_bytes(2, "little") for value in values)


def encode_bank(manifest):
    records = manifest["records"]
    if len(records) != RECORD_COUNT or manifest["start"] != BANK_START or manifest["end"] != BANK_END:
        raise ValueError("indexed graphics layout bank boundary differs")
    output = bytearray(encode_u16([2, RECORD_COUNT]))
    for record in records:
        offset = record["start"] - BANK_START - 4
        if not (HEADER_BYTES - 4 <= offset <= 0xffff):
            raise ValueError("indexed graphics layout offset differs")
        output += encode_u16([offset])
    for index, record in enumerate(records):
        if BANK_START + len(output) != record["start"]:
            raise ValueError("indexed graphics layout record position differs")
        cells = record["cells"]
        if (len(cells) != record["count"] or
                any(len(cell) != 3 for cell in cells)):
            raise ValueError("indexed graphics layout cell count differs")
        output += encode_u16([len(cells)])
        for cell in cells:
            output += encode_u16(cell)
        padding = record["padding_bytes"]
        # The final record has two additional bytes before the next archive.
        if (type(padding) is not int or padding not in (0, 2) or
                (index + 1 < RECORD_COUNT and (2 + 6 * len(cells) + padding) % 4)):
            raise ValueError("indexed graphics layout alignment differs")
        output += bytes(padding)
    if len(output) != BANK_END - BANK_START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("indexed graphics layout bank differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed graphics layout output must be outside the source tree")
    for site in CALLER_LITERAL_SITES:
        if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + BANK_START:
            raise ValueError("indexed graphics layout caller differs")
    if rom[BANK_START:BANK_START + 4] != encode_u16([2, RECORD_COUNT]):
        raise ValueError("indexed graphics layout type or record count differs")
    offsets = [u16(rom, BANK_START + 4 + 2 * index) for index in range(RECORD_COUNT)]
    if offsets[0] != 2 * RECORD_COUNT or offsets != sorted(set(offsets)):
        raise ValueError("indexed graphics layout offset table differs")
    records = []
    for index, offset in enumerate(offsets):
        start = BANK_START + 4 + offset
        next_start = BANK_START + 4 + offsets[index + 1] if index + 1 < RECORD_COUNT else BANK_END
        count = u16(rom, start)
        body_end = start + 2 + 6 * count
        padding = next_start - body_end
        if not 1 <= count <= 64 or padding not in (0, 2) or any(rom[body_end:next_start]):
            raise ValueError("indexed graphics layout record boundary differs")
        cells = [[u16(rom, pos + component) for component in (0, 2, 4)]
                 for pos in range(start + 2, body_end, 6)]
        records.append({"start": start, "count": count, "cells": cells,
                        "padding_bytes": padding})
    padding_bytes = sum(record["padding_bytes"] for record in records)
    if padding_bytes != EXPECTED_PADDING_BYTES:
        raise ValueError("indexed graphics layout padding total differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": BANK_START, "end": BANK_END,
                "record_count": RECORD_COUNT, "header_bytes": HEADER_BYTES,
                "padding_bytes": padding_bytes, "caller_literal_sites": CALLER_LITERAL_SITES,
                "source_sha256": sha256(rom[BANK_START:BANK_END]), "records": records,
                "scope_note": "The halfword-offset records are complete; the meanings of their three-halfword cells remain unresolved."}
    if encode_bank(manifest) != rom[BANK_START:BANK_END]:
        raise ValueError("indexed graphics layout does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": RECORD_COUNT, "source_bytes": BANK_END - BANK_START,
            "padding_bytes": padding_bytes, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
