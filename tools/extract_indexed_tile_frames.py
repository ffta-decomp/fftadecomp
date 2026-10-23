#!/usr/bin/env python3
"""Export ten 256-byte 4bpp tile blocks selected by the retail caller."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_direct_graphics_tiles import decode_tiles


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x418fcc
END = 0x4199cc
BLOCK_BYTES = 256
BLOCK_COUNT = 10
LITERAL = 0xa9118
NEXT_TILE_BANK = 0x4199e0


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_frames(manifest):
    if (manifest["start"] != START or manifest["end"] != END or
            len(manifest["blocks"]) != BLOCK_COUNT):
        raise ValueError("indexed tile frame boundary differs")
    output = bytearray()
    for index, block in enumerate(manifest["blocks"]):
        if block["start"] != START + index * BLOCK_BYTES or len(block["tiles"]) != 8:
            raise ValueError("indexed tile block position differs")
        data = bytearray()
        for tile in block["tiles"]:
            if len(tile) != 64 or any(type(pixel) is not int or not 0 <= pixel <= 15
                                      for pixel in tile):
                raise ValueError("indexed tile pixel differs")
            data += bytes(tile[position] | tile[position + 1] << 4
                          for position in range(0, 64, 2))
        if len(data) != BLOCK_BYTES or sha256(data) != block["source_sha256"]:
            raise ValueError("indexed tile block differs from retail")
        output += data
    if len(output) != END - START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("indexed tile frames differ from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed tile frame output must be outside the source tree")
    if (int.from_bytes(rom[LITERAL:LITERAL + 4], "little") != ROM_BASE + START or
            END - START != BLOCK_COUNT * BLOCK_BYTES or
            NEXT_TILE_BANK - END != 20):
        raise ValueError("indexed tile caller or source boundary differs")
    blocks = []
    for index in range(BLOCK_COUNT):
        start = START + index * BLOCK_BYTES
        data = rom[start:start + BLOCK_BYTES]
        blocks.append({"start": start, "tiles": decode_tiles(data),
                       "source_sha256": sha256(data)})
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "block_bytes": BLOCK_BYTES, "block_count": BLOCK_COUNT,
                "caller_literal": LITERAL, "source_sha256": sha256(rom[START:END]),
                "blocks": blocks,
                "scope_note": "The caller selects a 256-byte block and copies 128 bytes. The following 20 bytes are excluded because their format is unknown."}
    if encode_frames(manifest) != rom[START:END]:
        raise ValueError("indexed tile frame export does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"blocks": BLOCK_COUNT, "tiles": 8 * BLOCK_COUNT,
            "source_bytes": END - START, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
