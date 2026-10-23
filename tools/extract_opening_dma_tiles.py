#!/usr/bin/env python3
"""Export the second opening-scene DMA bank as candidate 8bpp tiles."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0x98ba64
SIZE = 0x8500
END = START + SIZE
TILE_BYTES = 64
LITERAL_SOURCE = 0x140fd8
DMA_SETUP = 0x140fae
ROM_BASE = 0x08000000


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_tiles(manifest, source_dir, verify_hash=True):
    if (manifest["start"] != START or manifest["end"] != END or
            manifest["tile_count"] != SIZE // TILE_BYTES or
            manifest["format"] != "8bpp_8x8_dma_tiles"):
        raise ValueError("opening DMA tile boundary or format differs")
    tiles = json.loads((source_dir / manifest["pixel_file"]).read_text())["tiles"]
    if (len(tiles) != manifest["tile_count"] or
            any(len(tile) != 8 or any(len(row) != 8 or any(
                type(pixel) is not int or not 0 <= pixel <= 255 for pixel in row)
                for row in tile) for tile in tiles)):
        raise ValueError("opening DMA tile pixel shape differs")
    data = bytes(pixel for tile in tiles for row in tile for pixel in row)
    if len(data) != SIZE or (verify_hash and sha256(data) != manifest["source_sha256"]):
        raise ValueError("opening DMA tile bytes differ from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if (int.from_bytes(rom[LITERAL_SOURCE:LITERAL_SOURCE + 4], "little") != ROM_BASE + START or
            rom[DMA_SETUP:DMA_SETUP + 4] != bytes.fromhex("85 23 db 01")):
        raise ValueError("opening-scene DMA source or halfword count differs")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening DMA tile output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    data = rom[START:END]
    tiles = [[list(data[start + row * 8:start + row * 8 + 8])
              for row in range(8)] for start in range(0, SIZE, TILE_BYTES)]
    pixel_file = "tiles.json"
    (output / pixel_file).write_text(json.dumps({"tiles": tiles}, separators=(",", ":")) + "\n")
    manifest = {
        "reference_sha256": ROM_SHA256,
        "start": START,
        "end": END,
        "format": "8bpp_8x8_dma_tiles",
        "tile_count": len(tiles),
        "pixel_file": pixel_file,
        "source_sha256": sha256(data),
        "caller": 0x08140fa8,
        "dma_halfword_count": 0x4280,
        "scope_note": "The 64-byte tile grouping is provisional. The DMA destination comes from a runtime descriptor; display mode, palette, and composed frames remain unresolved."
    }
    if encode_tiles(manifest, output) != data:
        raise ValueError("opening DMA tile export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"tile_count": len(tiles), "source_bytes": SIZE,
            "manifest_sha256": sha256(path.read_bytes()),
            "pixels_sha256": sha256((output / pixel_file).read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
