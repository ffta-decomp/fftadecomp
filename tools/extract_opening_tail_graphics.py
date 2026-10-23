#!/usr/bin/env python3
"""Export two additional bounded opening DMA sources as editable tile candidates."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
SOURCES = (
    (0x985080, 0x985180, 0x140d18, 0x140cfc, 0x80, "small-obj-tiles.json"),
    (0x993f64, 0x9950e4, 0x140cd0, 0x140c0e, 0x8c0, "queued-tiles.json"),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode_tiles(data):
    return [[[value >> shift & 15 for value in data[start + row * 4:start + row * 4 + 4]
              for shift in (0, 4)] for row in range(8)] for start in range(0, len(data), 32)]


def encode_segment(manifest, source_dir, start, verify_hash=True):
    matches = [entry for entry in manifest["segments"] if entry["start"] == start]
    specs = [spec for spec in SOURCES if spec[0] == start]
    if len(matches) != 1 or len(specs) != 1:
        raise ValueError("opening DMA source is not unique")
    entry, spec = matches[0], specs[0]
    if (entry["start"], entry["end"], entry["literal"], entry["halfword_count"],
            entry["file"]) != (spec[0], spec[1], spec[2], spec[4], spec[5]):
        raise ValueError("opening DMA source boundary differs")
    tiles = json.loads((source_dir / entry["file"]).read_text())["tiles"]
    if len(tiles) != (spec[1] - spec[0]) // 32 or any(
            len(tile) != 8 or any(len(row) != 8 or any(
                type(pixel) is not int or not 0 <= pixel <= 15 for pixel in row)
                for row in tile) for tile in tiles):
        raise ValueError("opening DMA tile shape differs")
    pixels = [pixel for tile in tiles for row in tile for pixel in row]
    data = bytes(pixels[i] | pixels[i + 1] << 4 for i in range(0, len(pixels), 2))
    if len(data) != spec[1] - spec[0] or (verify_hash and sha256(data) != entry["source_sha256"]):
        raise ValueError("opening DMA source differs from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening DMA output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    segments = []
    for start, end, literal, count_instruction, halfwords, file_name in SOURCES:
        if (end - start != halfwords * 2 or (end - start) % 32 or
                int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start):
            raise ValueError("opening DMA source pointer or count differs")
        if halfwords == 0x80:
            if rom[count_instruction:count_instruction + 2] != b"\x80\x23":
                raise ValueError("opening DMA small halfword count differs")
        elif rom[count_instruction:count_instruction + 4] != bytes.fromhex("8c 23 1b 01"):
            raise ValueError("opening DMA queued halfword count differs")
        data = rom[start:end]
        (output / file_name).write_text(json.dumps({"tiles": decode_tiles(data)}, separators=(",", ":")) + "\n")
        segments.append({"start": start, "end": end, "literal": literal,
                         "halfword_count": halfwords, "format": "candidate_4bpp_tiles",
                         "file": file_name, "source_sha256": sha256(data)})
    manifest = {
        "reference_sha256": ROM_SHA256, "segments": segments,
        "caveat": "These ROM sources and copy lengths are established. Four-bit tile grouping is reversible but provisional; the first destination is a runtime descriptor and final display mode is not established.",
    }
    for entry in segments:
        if encode_segment(manifest, output, entry["start"]) != rom[entry["start"]:entry["end"]]:
            raise ValueError("opening DMA source does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"segments": len(segments), "tile_candidates": sum(
                (entry["end"] - entry["start"]) // 32 for entry in segments),
            "source_bytes": sum(entry["end"] - entry["start"] for entry in segments),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
