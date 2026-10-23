#!/usr/bin/env python3
"""Export six pointer-indexed BGR555 color blocks beside A7 graphics."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x3c2b60
END = 0x3c2fe0
POINTER_TABLE = 0x394058
LENGTH_TABLE = 0x394070
BLOCK_COUNT = 6
BLOCK_BYTES = 0xc0
COLORS_PER_BLOCK = BLOCK_BYTES // 2


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_palette_blocks(manifest):
    blocks = manifest["blocks"]
    if (manifest["start"] != START or manifest["end"] != END or
            len(blocks) != BLOCK_COUNT):
        raise ValueError("indexed palette block boundary differs")
    output = bytearray()
    for index, block in enumerate(blocks):
        if block["start"] != START + index * BLOCK_BYTES or len(block["colors_bgr555"]) != COLORS_PER_BLOCK:
            raise ValueError("indexed palette block shape differs")
        for color in block["colors_bgr555"]:
            if type(color) is not int or not 0 <= color <= 0x7fff:
                raise ValueError("indexed palette color differs")
            output.extend(color.to_bytes(2, "little"))
    if len(output) != END - START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("indexed palette bytes differ from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("indexed palette output must be outside the source tree")
    blocks = []
    for index in range(BLOCK_COUNT):
        start = START + index * BLOCK_BYTES
        pointer_site = POINTER_TABLE + 4 * index
        length_site = LENGTH_TABLE + 4 * index
        if (int.from_bytes(rom[pointer_site:pointer_site + 4], "little") != ROM_BASE + start or
                int.from_bytes(rom[length_site:length_site + 4], "little") != BLOCK_BYTES):
            raise ValueError("indexed palette pointer or byte count differs")
        data = rom[start:start + BLOCK_BYTES]
        colors = [int.from_bytes(data[pos:pos + 2], "little")
                  for pos in range(0, BLOCK_BYTES, 2)]
        if any(color > 0x7fff for color in colors):
            raise ValueError("indexed palette high bit is set")
        blocks.append({"start": start, "pointer_site": pointer_site,
                       "length_site": length_site, "colors_bgr555": colors})
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "block_count": BLOCK_COUNT, "block_bytes": BLOCK_BYTES,
                "colors_per_block": COLORS_PER_BLOCK, "blocks": blocks,
                "source_sha256": sha256(rom[START:END]),
                "scope_note": "Six pointers and six 0xc0 byte counts bound six BGR555 color blocks. Their final display assignment remains unresolved."}
    if encode_palette_blocks(manifest) != rom[START:END]:
        raise ValueError("indexed palette blocks do not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"blocks": BLOCK_COUNT, "colors": BLOCK_COUNT * COLORS_PER_BLOCK,
            "source_bytes": END - START, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
