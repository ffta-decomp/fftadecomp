#!/usr/bin/env python3
"""Export paired pointer-indexed graphics layout banks."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_BASE = 0x08000000
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"

# Paired literal loads pass these banks into the layout constructor.
PAIRS = (
    ((0x950000, 0x950258, 0x359dc), (0x950f4c, 0x9511a4, 0x359e0)),
    ((0x950258, 0x95030c, 0x358a4), (0x9511a4, 0x9511f8, 0x358a8)),
    ((0x95030c, 0x950320, 0x3201c), (0x9511f8, 0x951220, 0x32020)),
    ((0x950320, 0x950508, 0x36e80), (0x951220, 0x9512e0, 0x36e84)),
    ((0x950508, 0x9506f0, 0x36f38), (0x9512e0, 0x9513a0, 0x36f3c)),
    ((0x9506f0, 0x9508d8, 0x36f88), (0x9513a0, 0x951460, 0x36f8c)),
    ((0x9508d8, 0x950d38, 0x36be8), (0x951460, 0x9514f4, 0x36bec)),
    ((0x950d38, 0x950d98, 0x88f54), (0x9514f4, 0x951550, 0x88f58)),
    ((0x950d98, 0x950f4c, 0x36d3c), (0x951550, 0x951588, 0x36d40)),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def u32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def encode_bank(manifest, start):
    matches = [bank for pair in manifest["pairs"] for bank in (pair["cell_bank"], pair["word_bank"])
               if bank["start"] == start]
    if len(matches) != 1:
        raise ValueError("graphics layout bank is not unique")
    bank = matches[0]
    records = bank["records"]
    offsets = bank["offsets"]
    if len(records) != len(offsets) or len(records) == 0:
        raise ValueError("graphics layout record count differs")
    output = bytearray()
    for offset in offsets:
        if type(offset) is not int or not 0 <= offset <= 0xffffffff:
            raise ValueError("graphics layout offset differs")
        output += offset.to_bytes(4, "little")
    for offset, record in zip(offsets, records):
        if offset != len(output):
            raise ValueError("graphics layout record offset differs")
        count = record["count"]
        if type(count) is not int or not 0 <= count <= 0xffff:
            raise ValueError("graphics layout cell count differs")
        output += count.to_bytes(2, "little")
        if bank["format"] == "six_byte_cells":
            cells = record["cells"]
            if len(cells) != count or any(len(cell) != 3 or any(
                    type(value) is not int or not 0 <= value <= 0xffff for value in cell)
                    for cell in cells):
                raise ValueError("graphics layout six-byte cell differs")
            for cell in cells:
                for value in cell:
                    output += value.to_bytes(2, "little")
            if len(output) % 4:
                if record.get("alignment_halfword") != 0:
                    raise ValueError("graphics layout alignment differs")
                output += b"\0\0"
            elif "alignment_halfword" in record:
                raise ValueError("graphics layout has unexpected alignment")
        elif bank["format"] == "four_byte_cells":
            field_02 = record["field_02"]
            cells = record["cells"]
            if (type(field_02) is not int or not 0 <= field_02 <= 0xffff or len(cells) != count or
                    any(type(value) is not int or not 0 <= value <= 0xffffffff for value in cells)):
                raise ValueError("graphics layout four-byte cell differs")
            output += field_02.to_bytes(2, "little")
            for value in cells:
                output += value.to_bytes(4, "little")
        else:
            raise ValueError("unknown graphics layout bank format")
    if len(output) != bank["end"] - start or sha256(output) != bank["source_sha256"]:
        raise ValueError("graphics layout bank differs from retail")
    return bytes(output)


def decode_bank(rom, start, end, literal, format_name):
    if literal is not None and u32(rom, literal) != ROM_BASE + start:
        raise ValueError("graphics layout caller no longer references its bank")
    data = rom[start:end]
    table_bytes = u32(data, 0)
    if table_bytes < 4 or table_bytes % 4 or table_bytes >= len(data):
        raise ValueError("graphics layout offset table has invalid size")
    offsets = [u32(data, index) for index in range(0, table_bytes, 4)]
    if offsets[0] != table_bytes or offsets != sorted(set(offsets)) or offsets[-1] >= len(data):
        raise ValueError("graphics layout record offsets differ")
    records = []
    for index, offset in enumerate(offsets):
        next_offset = offsets[index + 1] if index + 1 < len(offsets) else len(data)
        count = u16(data, offset)
        if format_name == "six_byte_cells":
            body_end = offset + 2 + count * 6
            expected_end = (body_end + 3) & ~3
            if expected_end != next_offset:
                raise ValueError("graphics layout six-byte record boundary differs")
            cells = [[u16(data, position + component) for component in (0, 2, 4)]
                     for position in range(offset + 2, body_end, 6)]
            record = {"count": count, "cells": cells}
            if body_end != expected_end:
                if data[body_end:expected_end] != b"\0\0":
                    raise ValueError("graphics layout alignment is not zero")
                record["alignment_halfword"] = 0
        else:
            expected_end = offset + 4 + count * 4
            if expected_end != next_offset:
                raise ValueError("graphics layout four-byte record boundary differs")
            record = {"count": count, "field_02": u16(data, offset + 2),
                      "cells": [u32(data, position) for position in range(offset + 4, expected_end, 4)]}
        records.append(record)
    return {"start": start, "end": end, "literal": literal, "format": format_name,
            "offsets": offsets, "records": records, "source_sha256": sha256(data)}


def export(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    pairs = []
    for cell_spec, word_spec in PAIRS:
        pair = {"cell_bank": decode_bank(rom, *cell_spec, "six_byte_cells"),
                "word_bank": decode_bank(rom, *word_spec, "four_byte_cells")}
        pairs.append(pair)
    manifest = {"reference_sha256": ROM_SHA256, "pairs": pairs,
                "consumer": 0x0804c4d4,
                "caveat": "The paired offset and cell formats are verified. Cell meaning and visual composition remain unresolved."}
    for pair in pairs:
        for bank in (pair["cell_bank"], pair["word_bank"]):
            if encode_bank(manifest, bank["start"]) != rom[bank["start"]:bank["end"]]:
                raise ValueError("graphics layout bank does not round-trip")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output.is_relative_to(root):
        raise SystemExit("graphics layout export must be outside the source tree")
    manifest = export(args.rom.read_bytes())
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"pairs": len(manifest["pairs"]),
                      "source_bytes": sum(bank["end"] - bank["start"] for pair in manifest["pairs"]
                                          for bank in (pair["cell_bank"], pair["word_bank"])),
                      "manifest_sha256": sha256(path.read_bytes())}))


if __name__ == "__main__":
    main()
