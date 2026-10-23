#!/usr/bin/env python3
"""Export the pointer-selected Ivalice map palette data as BGR555 colors."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TABLE_START = 0x391960
TABLE_COUNT = 8
PALETTE_START = 0x9552b8
PALETTE_END = 0x955eb8
PALETTE_BYTES = 0x200


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_palette_table(manifest):
    entries = manifest["pointer_table"]["palette_indices"]
    if len(entries) != TABLE_COUNT or any(type(index) is not int or not 0 <= index < 6
                                           for index in entries):
        raise ValueError("invalid world-map palette pointer indices")
    return b"".join((ROM_BASE + PALETTE_START + index * PALETTE_BYTES).to_bytes(4, "little")
                    for index in entries)


def encode_palette_bank(manifest):
    palettes = manifest["palettes"]
    if len(palettes) != 6:
        raise ValueError("world-map palette bank must contain six palettes")
    output = bytearray()
    for palette_index, palette in enumerate(palettes):
        colors = palette["bgr555"]
        if (palette["rom_offset"] != PALETTE_START + palette_index * PALETTE_BYTES or
                len(colors) != 256 or any(type(color) is not int or not 0 <= color <= 0xffff
                                       for color in colors)):
            raise ValueError("invalid world-map palette record")
        encoded = b"".join(color.to_bytes(2, "little") for color in colors)
        if sha256(encoded) != palette["source_sha256"]:
            raise ValueError("world-map palette differs from exported source")
        output += encoded
    return bytes(output)


def export(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    # 0x080314d0 loads this table, selects entries 0/2/4/6, then makes two
    # CpuSet copies of 0x100 halfwords from the pointer and pointer + 0x200.
    if int.from_bytes(rom[0x31544:0x31548], "little") != ROM_BASE + TABLE_START:
        raise ValueError("world-map palette caller no longer references the table")
    if rom[0x314d0:0x314f2].hex() != (
            "1c4e1d4c1d48241820788007c00e801900681b4f3968a031"
            "80256d002a1c10f1bdf9"):
        raise ValueError("world-map palette selection or copy sequence changed")
    pointers = [int.from_bytes(rom[TABLE_START + index * 4:TABLE_START + index * 4 + 4],
                               "little") for index in range(TABLE_COUNT)]
    indices = [(pointer - ROM_BASE - PALETTE_START) // PALETTE_BYTES for pointer in pointers]
    if indices != [0, 1, 4, 5, 2, 3, 0, 1] or any(
            pointer != ROM_BASE + PALETTE_START + index * PALETTE_BYTES
            for pointer, index in zip(pointers, indices)):
        raise ValueError("world-map palette pointers changed")
    palettes = []
    for index in range(6):
        start = PALETTE_START + index * PALETTE_BYTES
        data = rom[start:start + PALETTE_BYTES]
        palettes.append({"rom_offset": start, "source_sha256": sha256(data),
                         "bgr555": [int.from_bytes(data[pos:pos + 2], "little")
                                    for pos in range(0, len(data), 2)]})
    manifest = {
        "reference_sha256": ROM_SHA256,
        "pointer_table": {"start": TABLE_START, "end": TABLE_START + TABLE_COUNT * 4,
                          "palette_indices": indices,
                          "source_sha256": sha256(rom[TABLE_START:TABLE_START + 32])},
        "palette_bank": {"start": PALETTE_START, "end": PALETTE_END,
                         "source_sha256": sha256(rom[PALETTE_START:PALETTE_END])},
        "palettes": palettes,
        "consumer": {"entry": 0x080314c8, "table_literal": 0x08031544,
                     "copy_halfwords_per_block": 0x100, "bios_stub": 0x0814186c},
        "caveat": "The selected 512-byte pairs feed a RAM buffer; final screen composition and color assignment remain unverified.",
    }
    if (encode_palette_table(manifest) != rom[TABLE_START:TABLE_START + 32] or
            encode_palette_bank(manifest) != rom[PALETTE_START:PALETTE_END]):
        raise ValueError("world-map palette export does not round-trip")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    manifest = export(args.rom.read_bytes())
    args.output_dir.mkdir(parents=True, exist_ok=True)
    (args.output_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"pointer_table_bytes": 32, "palette_bank_bytes": PALETTE_END - PALETTE_START,
                      "manifest_sha256": sha256((args.output_dir / "manifest.json").read_bytes())}))


if __name__ == "__main__":
    main()
