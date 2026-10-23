#!/usr/bin/env python3
"""Export two offset-indexed banks of custom-LZSS graphics tiles."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_map_graphics import decode_lzss, encode_lzss_plan


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
BANKS = ((0x427a04, 0x42cc80, (0x1a404, 0x1a4f8)),
         (0x42cc80, 0x431a5c, (0x1a424, 0x1a514)))
RECORD_COUNT = 157
TABLE_BYTES = 2 * (RECORD_COUNT + 1)
EXPECTED_SOURCE_BYTES = 41048
EXPECTED_ENCODED_BYTES = 39933


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_bank(bank, source_dir):
    records = bank["records"]
    if len(records) != RECORD_COUNT:
        raise ValueError("indexed custom-LZSS record count differs")
    output = bytearray()
    for record in records:
        offset = record["start"] - bank["start"]
        if not TABLE_BYTES <= offset <= 0xffff:
            raise ValueError("indexed custom-LZSS offset differs")
        output += offset.to_bytes(2, "little")
    output += b"\0\0"
    for record in records:
        if len(output) != record["start"] - bank["start"]:
            raise ValueError("indexed custom-LZSS record boundary differs")
        raw = (source_dir / record["file"]).read_bytes()
        if len(raw) != 256 or sha256(raw) != record["decoded_sha256"]:
            raise ValueError("indexed custom-LZSS decoded tile differs")
        compressed = encode_lzss_plan(raw, record["token_plan"])
        if len(compressed) != record["encoded_bytes"] or sha256(compressed) != record["encoded_sha256"]:
            raise ValueError("indexed custom-LZSS token stream differs")
        padding = record["padding_bytes"]
        if type(padding) is not int or not 0 <= padding <= 3:
            raise ValueError("indexed custom-LZSS padding differs")
        output += compressed + bytes(padding)
    if len(output) != bank["end"] - bank["start"] or sha256(output) != bank["source_sha256"]:
        raise ValueError("indexed custom-LZSS bank differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed custom-LZSS output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    decoded_dir = output / "decoded"
    decoded_dir.mkdir(exist_ok=True)
    banks = []
    for start, end, literal_sites in BANKS:
        for site in literal_sites:
            if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + start:
                raise ValueError("indexed custom-LZSS caller no longer references bank")
        offsets = [int.from_bytes(rom[start + index * 2:start + index * 2 + 2], "little")
                   for index in range(RECORD_COUNT + 1)]
        if offsets[0] != TABLE_BYTES or offsets[-1] != 0 or offsets[:-1] != sorted(set(offsets[:-1])):
            raise ValueError("indexed custom-LZSS offset directory differs")
        records = []
        for index, offset in enumerate(offsets[:-1]):
            record_start = start + offset
            next_start = start + offsets[index + 1] if index + 1 < RECORD_COUNT else end
            if record_start >= next_start:
                raise ValueError("indexed custom-LZSS record ordering differs")
            raw, consumed, plan = decode_lzss(rom, record_start, capture_plan=True)
            if len(raw) != 256 or record_start + consumed > next_start:
                raise ValueError("indexed custom-LZSS tile size or boundary differs")
            padding = next_start - record_start - consumed
            if padding > 3 or any(rom[record_start + consumed:next_start]):
                raise ValueError("indexed custom-LZSS alignment differs")
            compressed = rom[record_start:record_start + consumed]
            if encode_lzss_plan(raw, plan) != compressed:
                raise ValueError("indexed custom-LZSS stream does not round-trip")
            name = f"tile-0x{record_start:06x}.bin"
            (decoded_dir / name).write_bytes(raw)
            records.append({"start": record_start, "encoded_bytes": consumed,
                            "decoded_sha256": sha256(raw), "encoded_sha256": sha256(compressed),
                            "padding_bytes": padding, "token_plan": plan,
                            "file": f"decoded/{name}"})
        bank = {"start": start, "end": end, "literal_sites": literal_sites,
                "record_count": len(records), "records": records,
                "source_sha256": sha256(rom[start:end])}
        if encode_bank(bank, output) != rom[start:end]:
            raise ValueError("indexed custom-LZSS bank does not round-trip")
        banks.append(bank)
    source_bytes = sum(bank["end"] - bank["start"] for bank in banks)
    encoded_bytes = sum(record["encoded_bytes"] for bank in banks for record in bank["records"])
    padding_bytes = sum(record["padding_bytes"] for bank in banks for record in bank["records"])
    if (source_bytes != EXPECTED_SOURCE_BYTES or encoded_bytes != EXPECTED_ENCODED_BYTES or
            len(banks) * RECORD_COUNT != 314 or TABLE_BYTES * len(banks) + encoded_bytes + padding_bytes != source_bytes):
        raise ValueError("indexed custom-LZSS bank coverage differs")
    manifest = {"reference_sha256": ROM_SHA256, "banks": banks,
                "source_bytes": source_bytes, "encoded_bytes": encoded_bytes,
                "decoded_bytes": 256 * RECORD_COUNT * len(banks),
                "table_bytes": TABLE_BYTES * len(banks), "padding_bytes": padding_bytes,
                "scope_note": "The 314 streams have complete source and output boundaries; tile placement and palettes are unresolved."}
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"banks": len(banks), "streams": RECORD_COUNT * len(banks),
            "source_bytes": source_bytes, "decoded_bytes": manifest["decoded_bytes"],
            "padding_bytes": padding_bytes, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
