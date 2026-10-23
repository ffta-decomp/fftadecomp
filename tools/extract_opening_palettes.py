#!/usr/bin/env python3
"""Export the bounded opening-scene 16-color BGR555 palette bank."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x997f80
END = 0x998e60
COLORS_PER_PALETTE = 16
PALETTE_BYTES = COLORS_PER_PALETTE * 2
PALETTE_COUNT = (END - START) // PALETTE_BYTES
POINTER_SITES = ((0x13f9e0, START), (0x140438, 0x998900),
                 (0x140ce8, 0x998bc0), (0x13f9f0, END))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_bank(manifest, source_dir, verify_hash=True):
    if (manifest["start"] != START or manifest["end"] != END or
            manifest["palette_count"] != PALETTE_COUNT or
            manifest["colors_per_palette"] != COLORS_PER_PALETTE):
        raise ValueError("opening palette boundary or shape differs")
    palettes = json.loads((source_dir / manifest["palette_file"]).read_text())["palettes"]
    if (len(palettes) != PALETTE_COUNT or any(len(palette) != COLORS_PER_PALETTE or any(
            type(color) is not int or not 0 <= color <= 0x7fff for color in palette)
            for palette in palettes)):
        raise ValueError("opening palette colors differ")
    data = b"".join(color.to_bytes(2, "little") for palette in palettes for color in palette)
    if len(data) != END - START or (verify_hash and sha256(data) != manifest["source_sha256"]):
        raise ValueError("opening palette bytes differ from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if any(int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + target
           for site, target in POINTER_SITES):
        raise ValueError("opening palette consumer or following boundary differs")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening palette output must be outside the source tree")
    data = rom[START:END]
    colors = [int.from_bytes(data[pos:pos + 2], "little") for pos in range(0, len(data), 2)]
    if len(colors) != PALETTE_COUNT * COLORS_PER_PALETTE or any(color & 0x8000 for color in colors):
        raise ValueError("opening palette bank is not plain BGR555")
    palettes = [colors[pos:pos + COLORS_PER_PALETTE]
                for pos in range(0, len(colors), COLORS_PER_PALETTE)]
    output.mkdir(parents=True, exist_ok=True)
    palette_file = "palettes.json"
    (output / palette_file).write_text(json.dumps({"palettes": palettes}, separators=(",", ":")) + "\n")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "palette_count": PALETTE_COUNT, "colors_per_palette": COLORS_PER_PALETTE,
                "palette_file": palette_file, "source_sha256": sha256(data),
                "pointer_sites": [{"site": site, "target": target} for site, target in POINTER_SITES],
                "scope_note": "The bank and direct references are bounded; tile-to-palette assignment is not established."}
    if encode_bank(manifest, output) != data:
        raise ValueError("opening palette export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"palette_count": PALETTE_COUNT, "source_bytes": END - START,
            "manifest_sha256": sha256(path.read_bytes()),
            "colors_sha256": sha256((output / palette_file).read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
