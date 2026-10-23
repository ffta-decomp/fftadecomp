#!/usr/bin/env python3
"""Export indexed palette words while retaining their optional high bit."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_graphics_layout_banks import decode_bank


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
RUN_START = 0x41a160
RUN_END = 0x41be20
PALETTE_BYTES = 32
PALETTE_COUNT = 230
FOLLOWING_LAYOUT_END = 0x41be70
LITERALS = (
    (0xcbb3c, 0x41a160), (0xcbb2c, 0x41a360), (0xcbbc0, 0x41a560),
    (0xcbb64, 0x41a760), (0xcba64, 0x41a860), (0xcbab8, 0x41aa60),
    (0xcbae8, 0x41ac60), (0xcbaf8, 0x41ae60), (0xcbba4, 0x41b060),
    (0xcbb78, 0x41b260), (0xcba70, 0x41b340), (0xcbb08, 0x41b740),
    (0xcbb18, 0x41b940), (0xcbbb0, 0x41bb40), (0xcbb6c, 0x41bd40),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_run(manifest, verify_retail=True):
    if (manifest["start"] != RUN_START or manifest["end"] != RUN_END or
            len(manifest["palettes"]) != PALETTE_COUNT):
        raise ValueError("graphics palette run boundary differs")
    output = bytearray()
    for palette in manifest["palettes"]:
        colors = palette["bgr555"]
        flagged = palette["high_bit_positions"]
        if (len(colors) != 16 or any(type(color) is not int or not 0 <= color < 0x8000
                                     for color in colors) or
                any(type(index) is not int or not 0 <= index < 16 for index in flagged) or
                flagged != sorted(set(flagged))):
            raise ValueError("graphics palette value or high bit differs")
        for index, color in enumerate(colors):
            output += (color | (0x8000 if index in flagged else 0)).to_bytes(2, "little")
    if (len(output) != RUN_END - RUN_START or
            (verify_retail and sha256(output) != manifest["source_sha256"])):
        raise ValueError("graphics palette run differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("graphics palette run output must be outside the source tree")
    if RUN_END - RUN_START != PALETTE_COUNT * PALETTE_BYTES:
        raise ValueError("graphics palette run size differs")
    for site, target in LITERALS:
        if ((target - RUN_START) % PALETTE_BYTES or
                int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + target):
            raise ValueError("graphics palette caller differs")
    # The next table is a different format and fixes this run's upper boundary.
    decode_bank(rom, RUN_END, FOLLOWING_LAYOUT_END, None, "four_byte_cells")
    palettes = []
    high_bit_count = 0
    for start in range(RUN_START, RUN_END, PALETTE_BYTES):
        words = [int.from_bytes(rom[pos:pos + 2], "little")
                 for pos in range(start, start + PALETTE_BYTES, 2)]
        flagged = [index for index, word in enumerate(words) if word & 0x8000]
        high_bit_count += len(flagged)
        palettes.append({"bgr555": [word & 0x7fff for word in words],
                         "high_bit_positions": flagged})
    manifest = {"reference_sha256": ROM_SHA256, "start": RUN_START, "end": RUN_END,
                "palette_count": PALETTE_COUNT, "high_bit_count": high_bit_count,
                "literal_sites": LITERALS,
                "source_sha256": sha256(rom[RUN_START:RUN_END]), "palettes": palettes,
                "scope_note": "Indexed 16-word records retain their high bits; exact renderer semantics and tile assignment remain unresolved."}
    if encode_run(manifest) != rom[RUN_START:RUN_END]:
        raise ValueError("graphics palette run does not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"palettes": PALETTE_COUNT, "source_bytes": RUN_END - RUN_START,
            "high_bit_words": high_bit_count, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
