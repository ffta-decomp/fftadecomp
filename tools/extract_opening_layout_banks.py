#!/usr/bin/env python3
"""Export the offset-indexed layout banks following the opening BG maps."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_graphics_layout_banks import decode_bank

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x9a031c
END = 0x9a5cf8

# Consecutive record-table boundaries, established by each table's internal
# offsets, cell counts, alignment, and the next valid table header.
BANKS = (
    (0x9a031c, 0x9a033c, 4), (0x9a033c, 0x9a0390, 4),
    (0x9a0390, 0x9a040c, 6), (0x9a040c, 0x9a04f0, 6),
    (0x9a04f0, 0x9a05b4, 4), (0x9a05b4, 0x9a05ec, 4),
    (0x9a05ec, 0x9a0728, 4), (0x9a0728, 0x9a088c, 4),
    (0x9a088c, 0x9a0990, 4), (0x9a0990, 0x9a0a94, 4),
    (0x9a0a94, 0x9a0ba8, 4), (0x9a0ba8, 0x9a0bb4, 4),
    (0x9a0bb4, 0x9a0c0c, 4), (0x9a0c0c, 0x9a0d48, 4),
    (0x9a0d48, 0x9a0e80, 4), (0x9a0e80, 0x9a0e8c, 4),
    (0x9a0e8c, 0x9a0e98, 4), (0x9a0e98, 0x9a0ea4, 4),
    (0x9a0ea4, 0x9a0eb0, 4), (0x9a0eb0, 0x9a0ebc, 4),
    (0x9a0ebc, 0x9a1414, 6), (0x9a1414, 0x9a1458, 4),
    (0x9a1458, 0x9a1bd0, 6), (0x9a1bd0, 0x9a2218, 6),
    (0x9a2218, 0x9a3448, 6), (0x9a3448, 0x9a413c, 6),
    (0x9a413c, 0x9a4728, 6), (0x9a4728, 0x9a473c, 4),
    (0x9a473c, 0x9a47c0, 6), (0x9a47c0, 0x9a4d04, 6),
    (0x9a4d04, 0x9a5320, 6), (0x9a5320, 0x9a545c, 6),
    (0x9a545c, 0x9a5484, 6), (0x9a5484, 0x9a5530, 6),
    (0x9a5530, 0x9a55a4, 6), (0x9a55a4, 0x9a55b8, 4),
    (0x9a55b8, 0x9a5658, 4), (0x9a5658, 0x9a5cf8, 6),
)
AMBIGUOUS_FORMAT_STARTS = {
    0x9a0ba8, 0x9a0e80, 0x9a0e8c, 0x9a0e98, 0x9a0ea4,
    0x9a0eb0, 0x9a1414, 0x9a4728, 0x9a55a4,
}
LITERAL_ANCHORS = {
    0x1365e4: 0x9a031c, 0x13738c: 0x9a033c,
    0x1365e0: 0x9a0390, 0x137388: 0x9a040c,
    0x140448: 0x9a55b8, 0x140444: 0x9a5658,
}


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def checked_int(value, maximum):
    if type(value) is not int or not 0 <= value <= maximum:
        raise ValueError("opening layout value is out of range")
    return value


def encode_bank(bank, check_hash=True):
    records = bank["records"]
    offsets = bank["offsets"]
    if not records or len(records) != len(offsets):
        raise ValueError("opening layout record count differs")
    output = bytearray()
    for offset in offsets:
        output += checked_int(offset, 0xffffffff).to_bytes(4, "little")
    for offset, record in zip(offsets, records):
        if offset != len(output):
            raise ValueError("opening layout record offset differs")
        count = checked_int(record["count"], 0xffff)
        cells = record["cells"]
        if len(cells) != count:
            raise ValueError("opening layout cell count differs")
        output += count.to_bytes(2, "little")
        if bank["format"] == "four_byte_cells":
            output += checked_int(record["field_02"], 0xffff).to_bytes(2, "little")
            for cell in cells:
                output += checked_int(cell, 0xffffffff).to_bytes(4, "little")
        elif bank["format"] == "six_byte_cells":
            for cell in cells:
                if len(cell) != 3:
                    raise ValueError("opening layout cell width differs")
                for field in cell:
                    output += checked_int(field, 0xffff).to_bytes(2, "little")
            if len(output) % 4:
                if record.get("alignment_halfword") != 0:
                    raise ValueError("opening layout alignment differs")
                output += b"\0\0"
            elif "alignment_halfword" in record:
                raise ValueError("opening layout has unexpected alignment")
        else:
            raise ValueError("unknown opening layout format")
    data = bytes(output)
    if len(data) != bank["end"] - bank["start"]:
        raise ValueError("opening layout bank length differs")
    if check_hash and sha256(data) != bank["source_sha256"]:
        raise ValueError("opening layout bank differs from retail")
    return data


def encode_layout_run(manifest, check_hash=True):
    if manifest["reference_sha256"] != ROM_SHA256:
        raise ValueError("opening layout revision differs")
    banks = manifest["banks"]
    if len(banks) != len(BANKS):
        raise ValueError("opening layout bank count differs")
    output = bytearray()
    for bank, (start, end, cell_bytes) in zip(banks, BANKS):
        if bank["start"] != start or bank["end"] != end:
            raise ValueError("opening layout bank boundary differs")
        if bank["format"] != ("four_byte_cells" if cell_bytes == 4 else "six_byte_cells"):
            raise ValueError("opening layout bank format differs")
        output += encode_bank(bank, check_hash)
    data = bytes(output)
    if len(data) != END - START:
        raise ValueError("opening layout run length differs")
    if check_hash and sha256(data) != manifest["source_sha256"]:
        raise ValueError("opening layout run differs from retail")
    return data


def export(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if BANKS[0][0] != START or BANKS[-1][1] != END or any(
            first[1] != second[0] for first, second in zip(BANKS, BANKS[1:])):
        raise ValueError("opening layout bank ranges are not contiguous")
    for literal, start in LITERAL_ANCHORS.items():
        if int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start:
            raise ValueError("opening layout caller no longer references its bank")
    banks = []
    for start, end, cell_bytes in BANKS:
        bank = decode_bank(rom, start, end, None,
                           "four_byte_cells" if cell_bytes == 4 else "six_byte_cells")
        bank["format_ambiguous"] = start in AMBIGUOUS_FORMAT_STARTS
        banks.append(bank)
    padding = sum("alignment_halfword" in record for bank in banks
                  for record in bank["records"]) * 2
    manifest = {
        "reference_sha256": ROM_SHA256, "start": START, "end": END,
        "source_sha256": sha256(rom[START:END]), "padding_bytes": padding,
        "literal_anchors": LITERAL_ANCHORS, "banks": banks,
        "caveat": "Nine short banks admit both cell widths at the same boundary. Their selected four-byte representation is reversible but its cell meaning is provisional; final image composition is unresolved.",
    }
    if encode_layout_run(manifest) != rom[START:END]:
        raise ValueError("opening layout run does not round-trip")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("opening layout export must be outside the source tree")
    manifest = export(args.rom.read_bytes())
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"banks": len(manifest["banks"]), "source_bytes": END - START,
                      "padding_bytes": manifest["padding_bytes"],
                      "ambiguous_format_banks": sum(bank["format_ambiguous"] for bank in manifest["banks"]),
                      "manifest_sha256": sha256(path.read_bytes())}))


if __name__ == "__main__":
    main()
