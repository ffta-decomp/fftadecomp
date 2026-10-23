#!/usr/bin/env python3
"""Export the contiguous run of 28 offset-indexed graphics cell banks."""

import argparse
import json
from pathlib import Path

from extract_graphics_layout_banks import (ROM_BASE, ROM_SHA256, decode_bank,
                                           sha256, u16, u32)


RUN_START = 0x41cf14
RUN_END = 0x420774
BANK_COUNT = 28
CONSUMER_LITERAL = 0xa8c84
CONSUMER_TARGET = 0x41d050


def encode_run(manifest):
    if (manifest["start"] != RUN_START or manifest["end"] != RUN_END or
            len(manifest["banks"]) != BANK_COUNT):
        raise ValueError("graphics cell run boundary differs")
    output = bytearray()
    for bank in manifest["banks"]:
        if RUN_START + len(output) != bank["start"]:
            raise ValueError("graphics cell bank position differs")
        bank_data = bytearray()
        for offset in bank["offsets"]:
            if type(offset) is not int or not 0 <= offset <= 0xffffffff:
                raise ValueError("graphics cell offset differs")
            bank_data += offset.to_bytes(4, "little")
        if not bank["records"] or len(bank["offsets"]) != len(bank["records"]):
            raise ValueError("graphics cell record count differs")
        for offset, record in zip(bank["offsets"], bank["records"]):
            if len(bank_data) != offset or len(record["cells"]) != record["count"]:
                raise ValueError("graphics cell record offset or count differs")
            bank_data += record["count"].to_bytes(2, "little")
            for cell in record["cells"]:
                if len(cell) != 3 or any(type(value) is not int or not 0 <= value <= 0xffff
                                         for value in cell):
                    raise ValueError("graphics cell value differs")
                for value in cell:
                    bank_data += value.to_bytes(2, "little")
            if len(bank_data) % 4:
                if record.get("alignment_halfword") != 0:
                    raise ValueError("graphics cell alignment differs")
                bank_data += b"\0\0"
            elif "alignment_halfword" in record:
                raise ValueError("unexpected graphics cell alignment")
        if (bank["end"] - bank["start"] != len(bank_data) or
                sha256(bank_data) != bank["source_sha256"]):
            raise ValueError("graphics cell bank differs from retail")
        output += bank_data
    if len(output) != RUN_END - RUN_START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("graphics cell run differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("graphics cell run output must be outside the source tree")
    if u32(rom, CONSUMER_LITERAL) != ROM_BASE + CONSUMER_TARGET:
        raise ValueError("graphics cell consumer pointer differs")
    banks = []
    start = RUN_START
    while start < RUN_END:
        table_bytes = u32(rom, start)
        if table_bytes < 4 or table_bytes > 0x1000 or table_bytes % 4:
            raise ValueError("graphics cell offset table width differs")
        last_offset = u32(rom, start + table_bytes - 4)
        final_record = start + last_offset
        end = (final_record + 2 + 6 * u16(rom, final_record) + 3) & ~3
        if not start < end <= RUN_END:
            raise ValueError("graphics cell derived boundary differs")
        banks.append(decode_bank(rom, start, end, None, "six_byte_cells"))
        start = end
    padding_bytes = sum(2 for bank in banks for record in bank["records"]
                        if "alignment_halfword" in record)
    if len(banks) != BANK_COUNT:
        raise ValueError("graphics cell bank count differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": RUN_START, "end": RUN_END,
                "bank_count": BANK_COUNT, "padding_bytes": padding_bytes,
                "consumer_literal": CONSUMER_LITERAL,
                "source_sha256": sha256(rom[RUN_START:RUN_END]), "banks": banks,
                "scope_note": "Twenty-eight consecutive offset-indexed six-byte-cell banks round-trip; cell meanings remain unresolved."}
    if encode_run(manifest) != rom[RUN_START:RUN_END]:
        raise ValueError("graphics cell run does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"banks": len(banks), "source_bytes": RUN_END - RUN_START,
            "padding_bytes": padding_bytes, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
