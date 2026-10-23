#!/usr/bin/env python3
"""Export directly indexed 4bpp tiles beside the graphics layout banks."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
BANKS = (
    (0x4199e0, 0x419be0, 0xc57cc),
    (0x419be0, 0x419c60, 0xc5608),
    (0x419c60, 0x419ce0, 0xc569c),
    (0x419ce0, 0x419d60, 0xc5718),
)
PALETTE_LITERAL = 0xcba80
PALETTE_START = 0x419d60


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode_tiles(data):
    if len(data) % 32:
        raise ValueError("direct graphics tile bank is not tile-aligned")
    return [[(value >> shift) & 15 for value in data[start:start + 32]
             for shift in (0, 4)] for start in range(0, len(data), 32)]


def encode_bank(manifest, start):
    matches = [bank for bank in manifest["banks"] if bank["start"] == start]
    if len(matches) != 1:
        raise ValueError("direct graphics tile bank is not unique")
    bank = matches[0]
    tiles = bank["tiles"]
    if len(tiles) != bank["tile_count"] or any(len(tile) != 64 or any(
            type(pixel) is not int or not 0 <= pixel <= 15 for pixel in tile)
            for tile in tiles):
        raise ValueError("direct graphics tile shape or index differs")
    encoded = bytes(tile[index] | tile[index + 1] << 4
                    for tile in tiles for index in range(0, 64, 2))
    if len(encoded) != bank["end"] - start or sha256(encoded) != bank["source_sha256"]:
        raise ValueError("direct graphics tile bank differs from retail")
    return encoded


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("direct graphics tile output must be outside the source tree")
    if int.from_bytes(rom[PALETTE_LITERAL:PALETTE_LITERAL + 4], "little") != ROM_BASE + PALETTE_START:
        raise ValueError("following palette boundary differs")
    banks = []
    for start, end, literal in BANKS:
        if int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start:
            raise ValueError("direct graphics tile caller differs")
        data = rom[start:end]
        bank = {"start": start, "end": end, "literal": literal,
                "tile_count": len(data) // 32, "tiles": decode_tiles(data),
                "source_sha256": sha256(data)}
        banks.append(bank)
    manifest = {"reference_sha256": ROM_SHA256, "banks": banks,
                "source_bytes": sum(bank["end"] - bank["start"] for bank in banks),
                "scope_note": "Direct 32-byte tile indexing is observed; palette assignment and final composition remain unresolved."}
    if manifest["source_bytes"] != PALETTE_START - BANKS[0][0]:
        raise ValueError("direct graphics tile coverage differs")
    for bank in banks:
        if encode_bank(manifest, bank["start"]) != rom[bank["start"]:bank["end"]]:
            raise ValueError("direct graphics tile export does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"banks": len(banks), "tiles": sum(bank["tile_count"] for bank in banks),
            "source_bytes": manifest["source_bytes"], "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
