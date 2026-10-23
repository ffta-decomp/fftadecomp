#!/usr/bin/env python3
"""Export two directly indexed BGR555 palette banks beside the tile data."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
PALETTE_COLORS = 16
PALETTE_BYTES = 32
BANKS = ((0x419d60, 0x419f60, 0xcba80),
         (0x419f60, 0x41a160, 0xcbaa8))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_bank(manifest, start):
    matches = [bank for bank in manifest["banks"] if bank["start"] == start]
    if len(matches) != 1:
        raise ValueError("direct graphics palette bank is not unique")
    bank = matches[0]
    if bank["end"] - start != len(bank["palettes"]) * PALETTE_BYTES:
        raise ValueError("direct graphics palette bank boundary differs")
    colors = [color for palette in bank["palettes"] for color in palette]
    if (any(len(palette) != PALETTE_COLORS for palette in bank["palettes"]) or
            any(type(color) is not int or not 0 <= color < 0x8000 for color in colors)):
        raise ValueError("direct graphics BGR555 palette differs")
    encoded = b"".join(color.to_bytes(2, "little") for color in colors)
    if sha256(encoded) != bank["source_sha256"]:
        raise ValueError("direct graphics palette bank differs from retail")
    return encoded


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("direct graphics palette output must be outside the source tree")
    banks = []
    for start, end, literal in BANKS:
        if int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start:
            raise ValueError("direct graphics palette caller differs")
        data = rom[start:end]
        if len(data) != 16 * PALETTE_BYTES:
            raise ValueError("direct graphics palette bank size differs")
        colors = [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, len(data), 2)]
        if any(color & 0x8000 for color in colors):
            raise ValueError("direct graphics palette uses non-color high bits")
        bank = {"start": start, "end": end, "literal": literal,
                "palettes": [colors[index:index + PALETTE_COLORS]
                             for index in range(0, len(colors), PALETTE_COLORS)],
                "source_sha256": sha256(data)}
        banks.append(bank)
    manifest = {"reference_sha256": ROM_SHA256, "banks": banks,
                "source_bytes": sum(bank["end"] - bank["start"] for bank in banks),
                "scope_note": "Each bank has 16 indexed BGR555 palettes. Tile-to-palette assignment is not yet established."}
    for bank in banks:
        if encode_bank(manifest, bank["start"]) != rom[bank["start"]:bank["end"]]:
            raise ValueError("direct graphics palette export does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"banks": len(banks), "palettes": sum(len(bank["palettes"]) for bank in banks),
            "source_bytes": manifest["source_bytes"], "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
