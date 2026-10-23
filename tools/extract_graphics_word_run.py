#!/usr/bin/env python3
"""Export the contiguous run of 28 four-byte graphics layout banks."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_graphics_layout_banks import decode_bank, u16, u32


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
RUN_START = 0x41be20
RUN_END = 0x41ccb8
BANK_COUNT = 28
CONSUMER_LITERAL = 0xa8c80
CONSUMER_TARGET = 0x41be70


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_run(manifest):
    if (manifest["start"] != RUN_START or manifest["end"] != RUN_END or
            len(manifest["banks"]) != BANK_COUNT):
        raise ValueError("graphics word run boundary differs")
    output = bytearray()
    for bank in manifest["banks"]:
        if RUN_START + len(output) != bank["start"]:
            raise ValueError("graphics word bank position differs")
        bank_data = bytearray()
        for offset in bank["offsets"]:
            if type(offset) is not int or not 0 <= offset <= 0xffffffff:
                raise ValueError("graphics word offset differs")
            bank_data += offset.to_bytes(4, "little")
        if not bank["records"] or len(bank["offsets"]) != len(bank["records"]):
            raise ValueError("graphics word record count differs")
        for offset, record in zip(bank["offsets"], bank["records"]):
            count = record["count"]
            field_02 = record["field_02"]
            cells = record["cells"]
            if (len(bank_data) != offset or type(count) is not int or not 0 <= count <= 0xffff or
                    type(field_02) is not int or not 0 <= field_02 <= 0xffff or
                    len(cells) != count or any(type(value) is not int or not 0 <= value <= 0xffffffff
                                               for value in cells)):
                raise ValueError("graphics word record differs")
            bank_data += count.to_bytes(2, "little") + field_02.to_bytes(2, "little")
            for value in cells:
                bank_data += value.to_bytes(4, "little")
        if (len(bank_data) != bank["end"] - bank["start"] or
                sha256(bank_data) != bank["source_sha256"]):
            raise ValueError("graphics word bank differs from retail")
        output += bank_data
    if len(output) != RUN_END - RUN_START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("graphics word run differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("graphics word run output must be outside the source tree")
    if u32(rom, CONSUMER_LITERAL) != ROM_BASE + CONSUMER_TARGET:
        raise ValueError("graphics word consumer pointer differs")
    banks = []
    start = RUN_START
    while start < RUN_END:
        table_bytes = u32(rom, start)
        if table_bytes < 4 or table_bytes > 0x1000 or table_bytes % 4:
            raise ValueError("graphics word offset table width differs")
        final_record = start + u32(rom, start + table_bytes - 4)
        end = final_record + 4 + 4 * u16(rom, final_record)
        if not start < end <= RUN_END:
            raise ValueError("graphics word derived boundary differs")
        banks.append(decode_bank(rom, start, end, None, "four_byte_cells"))
        start = end
    if len(banks) != BANK_COUNT:
        raise ValueError("graphics word bank count differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": RUN_START, "end": RUN_END,
                "bank_count": BANK_COUNT, "consumer_literal": CONSUMER_LITERAL,
                "source_sha256": sha256(rom[RUN_START:RUN_END]), "banks": banks,
                "scope_note": "Twenty-eight consecutive four-byte-cell banks round-trip; field semantics remain unresolved."}
    if encode_run(manifest) != rom[RUN_START:RUN_END]:
        raise ValueError("graphics word run does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"banks": len(banks), "source_bytes": RUN_END - RUN_START,
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
