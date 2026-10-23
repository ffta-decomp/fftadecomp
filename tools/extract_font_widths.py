#!/usr/bin/env python3
"""Export the font's directly indexed width bytes and trailing width block."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x4966b0
END = 0x497418
GLYPH_COUNT = 3175
TRAILING_COUNT = 256
LITERAL_SITES = (0x13480, 0x13a7c)
NEXT_TABLE_SITES = (0x237f4, 0x27484, 0x274dc)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_widths(manifest):
    if manifest["start"] != START or manifest["end"] != END:
        raise ValueError("font width boundary differs")
    widths = manifest["glyph_widths"]
    trailing = manifest["trailing_width_bytes"]
    if (len(widths) != GLYPH_COUNT or len(trailing) != TRAILING_COUNT or
            any(type(value) is not int or not 0 <= value <= 255
                for value in widths + trailing) or
            manifest["alignment_byte"] != 0):
        raise ValueError("font width count, byte, or alignment differs")
    output = bytes(widths + trailing + [0])
    if len(output) != END - START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("font width bytes differ from retail")
    return output


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("font width output must be outside the source tree")
    for site in LITERAL_SITES:
        if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + START:
            raise ValueError("font width caller differs")
    for site in NEXT_TABLE_SITES:
        if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + END:
            raise ValueError("following font table caller differs")
    data = rom[START:END]
    if (len(data) != GLYPH_COUNT + TRAILING_COUNT + 1 or
            data[GLYPH_COUNT:GLYPH_COUNT + TRAILING_COUNT] != bytes([16]) * TRAILING_COUNT or
            data[-1] != 0):
        raise ValueError("font width block shape differs")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "glyph_count": GLYPH_COUNT, "glyph_widths": list(data[:GLYPH_COUNT]),
                "trailing_width_bytes": list(data[GLYPH_COUNT:-1]),
                "alignment_byte": data[-1], "literal_sites": LITERAL_SITES,
                "next_table_sites": NEXT_TABLE_SITES,
                "source_sha256": sha256(data),
                "scope_note": "The first 3175 bytes align with the 3175 glyphs. The role of the trailing 256 width-like bytes remains unresolved."}
    if encode_widths(manifest) != data:
        raise ValueError("font width export does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"glyph_widths": GLYPH_COUNT, "trailing_bytes": TRAILING_COUNT,
            "source_bytes": len(data), "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
