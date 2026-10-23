#!/usr/bin/env python3
"""Export the contiguous 16-color BGR555 graphics palette bank."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_BASE = 0x08000000
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
BANK_START = 0x94ecfc
BANK_END = 0x94f7dc
PALETTE_BYTES = 32
PALETTE_COUNT = 87
FIRST_PALETTE_LITERAL = 0x65770
FIRST_PALETTE_LOAD = 0x65744
FIRST_PALETTE_CALL = 0x6574a
COPY_CALLEE = 0x08142250


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def thumb_bl_target(rom, site):
    first = int.from_bytes(rom[site:site + 2], "little")
    second = int.from_bytes(rom[site + 2:site + 4], "little")
    if first & 0xf800 != 0xf000 or second & 0xf800 != 0xf800:
        raise ValueError("palette consumer no longer uses Thumb BL")
    displacement = ((first & 0x7ff) << 12) | ((second & 0x7ff) << 1)
    if displacement & (1 << 22):
        displacement -= 1 << 23
    return ROM_BASE + site + 4 + displacement


def encode_bank(manifest):
    bank = manifest["bank"]
    if bank["start"] != BANK_START or bank["end"] != BANK_END:
        raise ValueError("graphics palette bank boundary differs")
    palettes = bank["palettes"]
    if len(palettes) != PALETTE_COUNT:
        raise ValueError("graphics palette count differs")
    output = bytearray()
    for index, palette in enumerate(palettes):
        if palette["start"] != BANK_START + index * PALETTE_BYTES or len(palette["colors"]) != 16:
            raise ValueError("graphics palette record boundary differs")
        encoded = bytearray()
        for color in palette["colors"]:
            if set(color) != {"red5", "green5", "blue5"} or any(
                    type(color[channel]) is not int or not 0 <= color[channel] <= 31
                    for channel in ("red5", "green5", "blue5")):
                raise ValueError("graphics palette channel differs")
            value = color["red5"] | (color["green5"] << 5) | (color["blue5"] << 10)
            encoded += value.to_bytes(2, "little")
        if sha256(encoded) != palette["source_sha256"]:
            raise ValueError("graphics palette record differs from retail")
        output += encoded
    if len(output) != BANK_END - BANK_START or sha256(output) != bank["source_sha256"]:
        raise ValueError("graphics palette bank differs from retail")
    return bytes(output)


def export(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    load = int.from_bytes(rom[FIRST_PALETTE_LOAD:FIRST_PALETTE_LOAD + 2], "little")
    literal_target = ((ROM_BASE + FIRST_PALETTE_LOAD + 4) & ~3) + (load & 0xff) * 4
    if (load & 0xf800 != 0x4800 or (load >> 8) & 7 != 1 or
            literal_target != ROM_BASE + FIRST_PALETTE_LITERAL or
            int.from_bytes(rom[FIRST_PALETTE_LITERAL:FIRST_PALETTE_LITERAL + 4], "little") != ROM_BASE + BANK_START or
            int.from_bytes(rom[0x65748:0x6574a], "little") != 0x2220 or
            thumb_bl_target(rom, FIRST_PALETTE_CALL) != COPY_CALLEE):
        raise ValueError("first graphics palette copy differs")
    if BANK_END - BANK_START != PALETTE_COUNT * PALETTE_BYTES:
        raise ValueError("graphics palette bank length differs")
    palettes = []
    for index in range(PALETTE_COUNT):
        start = BANK_START + index * PALETTE_BYTES
        data = rom[start:start + PALETTE_BYTES]
        values = [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, PALETTE_BYTES, 2)]
        if any(value > 0x7fff for value in values):
            raise ValueError("graphics palette contains a non-BGR555 halfword")
        palettes.append({"start": start,
                         "colors": [{"red5": value & 31, "green5": (value >> 5) & 31,
                                     "blue5": (value >> 10) & 31} for value in values],
                         "source_sha256": sha256(data)})
    manifest = {"reference_sha256": ROM_SHA256,
                "bank": {"start": BANK_START, "end": BANK_END, "palettes": palettes,
                         "source_sha256": sha256(rom[BANK_START:BANK_END])},
                "first_palette_consumer": {"load_site": ROM_BASE + FIRST_PALETTE_LOAD,
                                           "call_site": ROM_BASE + FIRST_PALETTE_CALL,
                                           "copy_bytes": PALETTE_BYTES},
                "caveat": "The first 32-byte palette is directly copied by code. The remaining 86 records follow the contiguous 16-color BGR555 format but their individual runtime consumers are not proven."}
    if encode_bank(manifest) != rom[BANK_START:BANK_END]:
        raise ValueError("graphics palette bank does not round-trip")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output.is_relative_to(root):
        raise SystemExit("graphics palette export must be outside the source tree")
    manifest = export(args.rom.read_bytes())
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"palettes": PALETTE_COUNT, "source_bytes": BANK_END - BANK_START,
                      "direct_copy_proven_bytes": PALETTE_BYTES,
                      "manifest_sha256": sha256(path.read_bytes())}))


if __name__ == "__main__":
    main()
