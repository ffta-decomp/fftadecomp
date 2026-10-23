#!/usr/bin/env python3
"""Export the directly queued opening frame graphics source as tile candidates."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x985324
END = 0x98ba64
TILE_BYTES = 32
SOURCE_LITERAL = 0x140788
HALFWORD_COUNT_LITERAL = 0x14078c
HALFWORD_COUNT = 0x33a0


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_tiles(manifest, source_dir, verify_hash=True):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["start"] != START or manifest["end"] != END or
            manifest["tile_count"] != (END - START) // TILE_BYTES or
            manifest["format"] != "candidate_4bpp_8x8_tiles"):
        raise ValueError("opening frame tile boundary or format differs")
    tiles = json.loads((source_dir / manifest["pixel_file"]).read_text())["tiles"]
    if len(tiles) != manifest["tile_count"] or any(
            len(tile) != 8 or any(len(row) != 8 or any(
                type(pixel) is not int or not 0 <= pixel <= 15 for pixel in row)
                for row in tile) for tile in tiles):
        raise ValueError("opening frame tile pixel shape differs")
    pixels = [pixel for tile in tiles for row in tile for pixel in row]
    data = bytes(pixels[i] | pixels[i + 1] << 4 for i in range(0, len(pixels), 2))
    if len(data) != END - START or (verify_hash and sha256(data) != manifest["source_sha256"]):
        raise ValueError("opening frame tile bytes differ from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if (END - START != HALFWORD_COUNT * 2 or (END - START) % TILE_BYTES or
            int.from_bytes(rom[SOURCE_LITERAL:SOURCE_LITERAL + 4], "little") != ROM_BASE + START or
            int.from_bytes(rom[HALFWORD_COUNT_LITERAL:HALFWORD_COUNT_LITERAL + 4], "little") != HALFWORD_COUNT or
            rom[0x140766:0x140770] != bytes.fromhex("28 18 07 49 12 69 07 4b c0 f6")):
        raise ValueError("opening frame DMA source or halfword count differs")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening frame tile output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    data = rom[START:END]
    tiles = [[[value >> shift & 15 for value in data[start + row * 4:start + row * 4 + 4]
               for shift in (0, 4)] for row in range(8)]
             for start in range(0, len(data), TILE_BYTES)]
    pixel_file = "tiles.json"
    (output / pixel_file).write_text(json.dumps({"tiles": tiles}, separators=(",", ":")) + "\n")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "format": "candidate_4bpp_8x8_tiles", "tile_count": len(tiles),
                "pixel_file": pixel_file, "source_sha256": sha256(data),
                "caller": 0x08140768, "halfword_count": HALFWORD_COUNT,
                "caveat": "The ROM source and copy count are exact. The destination comes from a runtime descriptor, so 4bpp tile grouping and final display mode are provisional."}
    if encode_tiles(manifest, output) != data:
        raise ValueError("opening frame tile export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"tile_candidates": len(tiles), "source_bytes": len(data),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
