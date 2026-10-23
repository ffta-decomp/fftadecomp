#!/usr/bin/env python3
"""Export the 103-entry type-4 custom-LZSS graphics archive."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_map_graphics import decode_lzss, encode_lzss_plan


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
BANK_START = 0x3e105c
BANK_END = 0x417f88
CALLER_LITERAL_SITES = (0xcb864, 0xcb8d0)
RECORD_COUNT = 103
TABLE_BYTES = 4 + 4 * RECORD_COUNT
EXPECTED_ENCODED_BYTES = 224516
EXPECTED_DECODED_BYTES = 353536
EXPECTED_PADDING_BYTES = 136


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_archive(manifest, source_dir):
    entries = manifest["records"]
    if len(entries) != RECORD_COUNT or manifest["start"] != BANK_START or manifest["end"] != BANK_END:
        raise ValueError("indexed graphics archive boundary differs")
    output = bytearray((4).to_bytes(2, "little") + RECORD_COUNT.to_bytes(2, "little"))
    for record in entries:
        offset = record["start"] - BANK_START - 4
        if not 0 <= offset <= 0xffffffff:
            raise ValueError("indexed graphics archive offset differs")
        output += offset.to_bytes(4, "little")
    for record in entries:
        if BANK_START + len(output) != record["start"]:
            raise ValueError("indexed graphics record position differs")
        raw = (source_dir / record["file"]).read_bytes()
        if len(raw) != record["decoded_bytes"] or sha256(raw) != record["decoded_sha256"]:
            raise ValueError("indexed graphics decoded file differs")
        encoded = encode_lzss_plan(raw, record["token_plan"])
        if len(encoded) != record["encoded_bytes"] or sha256(encoded) != record["encoded_sha256"]:
            raise ValueError("indexed graphics compressed record differs")
        padding = record["padding_bytes"]
        if type(padding) is not int or not 0 <= padding <= 3:
            raise ValueError("indexed graphics alignment differs")
        output += encoded + bytes(padding)
    if len(output) != BANK_END - BANK_START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("indexed graphics archive differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed graphics archive output must be outside the source tree")
    for site in CALLER_LITERAL_SITES:
        if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + BANK_START:
            raise ValueError("indexed graphics archive caller differs")
    if (rom[BANK_START:BANK_START + 4] != b"\x04\x00\x67\x00" or
            rom[BANK_END:BANK_END + 4] != b"\x02\x00\x67\x00"):
        raise ValueError("indexed graphics archive header or following bank differs")
    offsets = [int.from_bytes(rom[BANK_START + 4 + 4 * index:BANK_START + 8 + 4 * index], "little")
               for index in range(RECORD_COUNT)]
    if offsets[0] != RECORD_COUNT * 4 or offsets != sorted(set(offsets)):
        raise ValueError("indexed graphics archive offset table differs")
    output.mkdir(parents=True, exist_ok=True)
    decoded_dir = output / "decoded"
    decoded_dir.mkdir(exist_ok=True)
    records = []
    for index, offset in enumerate(offsets):
        start = BANK_START + 4 + offset
        next_start = BANK_START + 4 + offsets[index + 1] if index + 1 < RECORD_COUNT else BANK_END
        raw, consumed, plan = decode_lzss(rom, start, capture_plan=True)
        if not raw or len(raw) % 32 or start + consumed > next_start:
            raise ValueError("indexed graphics decoded tile or source boundary differs")
        padding = next_start - start - consumed
        if padding > 3 or any(rom[start + consumed:next_start]):
            raise ValueError("indexed graphics zero alignment differs")
        encoded = rom[start:start + consumed]
        if encode_lzss_plan(raw, plan) != encoded:
            raise ValueError("indexed graphics token plan does not round-trip")
        name = f"record-0x{start:06x}.bin"
        (decoded_dir / name).write_bytes(raw)
        records.append({"start": start, "encoded_bytes": consumed,
                        "decoded_bytes": len(raw), "padding_bytes": padding,
                        "encoded_sha256": sha256(encoded), "decoded_sha256": sha256(raw),
                        "token_plan": plan, "file": f"decoded/{name}"})
    encoded_bytes = sum(record["encoded_bytes"] for record in records)
    decoded_bytes = sum(record["decoded_bytes"] for record in records)
    padding_bytes = sum(record["padding_bytes"] for record in records)
    if (encoded_bytes != EXPECTED_ENCODED_BYTES or decoded_bytes != EXPECTED_DECODED_BYTES or
            padding_bytes != EXPECTED_PADDING_BYTES or
            TABLE_BYTES + encoded_bytes + padding_bytes != BANK_END - BANK_START):
        raise ValueError("indexed graphics archive coverage differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": BANK_START, "end": BANK_END,
                "record_count": RECORD_COUNT, "table_bytes": TABLE_BYTES,
                "encoded_bytes": encoded_bytes, "decoded_bytes": decoded_bytes,
                "padding_bytes": padding_bytes, "caller_literal_sites": CALLER_LITERAL_SITES,
                "source_sha256": sha256(rom[BANK_START:BANK_END]), "records": records,
                "scope_note": "Type-4 offsets, source streams, and alignment are exact; tile placement and the following type-2 bank remain separate."}
    if encode_archive(manifest, output) != rom[BANK_START:BANK_END]:
        raise ValueError("indexed graphics archive does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": RECORD_COUNT, "source_bytes": BANK_END - BANK_START,
            "decoded_bytes": decoded_bytes, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
