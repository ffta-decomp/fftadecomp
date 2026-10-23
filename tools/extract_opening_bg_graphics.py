#!/usr/bin/env python3
"""Export the opening BG tile bank and its two queued screen-entry maps."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TILE_START = 0x9951a0
TILE_END = 0x997f80
MAP_STARTS = (0x99f31c, 0x99fb1c)
MAP_BYTES = 0x800
SOURCES = ((TILE_START, TILE_END, "tiles.json", "4bpp_tiles"),
           (MAP_STARTS[0], MAP_STARTS[0] + MAP_BYTES, "map-0.json", "screen_entries"),
           (MAP_STARTS[1], MAP_STARTS[1] + MAP_BYTES, "map-1.json", "screen_entries"))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode_tiles(data):
    return [[[((value >> shift) & 15) for value in data[start + row * 4:start + row * 4 + 4]
              for shift in (0, 4)] for row in range(8)] for start in range(0, len(data), 32)]


def decode_map(data):
    cells = []
    for start in range(0, len(data), 64):
        row = []
        for offset in range(start, start + 64, 2):
            entry = int.from_bytes(data[offset:offset + 2], "little")
            row.append({"tile_index": entry & 0x3ff,
                        "horizontal_flip": bool(entry & 0x400),
                        "vertical_flip": bool(entry & 0x800),
                        "palette_index": entry >> 12})
        cells.append(row)
    return cells


def encode_segment(manifest, source_dir, start, verify_hash=True):
    matches = [entry for entry in manifest["segments"] if entry["start"] == start]
    if len(matches) != 1:
        raise ValueError("opening BG segment is not unique")
    entry = matches[0]
    expected = next((segment for segment in SOURCES if segment[0] == start), None)
    if expected is None or (entry["start"], entry["end"], entry["file"], entry["format"]) != expected:
        raise ValueError("opening BG segment boundary or format differs")
    asset = json.loads((source_dir / entry["file"]).read_text())
    if entry["format"] == "4bpp_tiles":
        tiles = asset["tiles"]
        if (len(tiles) != (TILE_END - TILE_START) // 32 or
                any(len(tile) != 8 or any(len(row) != 8 or any(
                    type(pixel) is not int or not 0 <= pixel <= 15 for pixel in row)
                    for row in tile) for tile in tiles)):
            raise ValueError("opening BG tile pixel shape differs")
        pixels = [pixel for tile in tiles for row in tile for pixel in row]
        data = bytes(pixels[pos] | pixels[pos + 1] << 4 for pos in range(0, len(pixels), 2))
    else:
        rows = asset["rows"]
        if len(rows) != 32 or any(len(row) != 32 for row in rows):
            raise ValueError("opening BG map dimensions differ")
        encoded = bytearray()
        for row in rows:
            for cell in row:
                if (type(cell["tile_index"]) is not int or not 0 <= cell["tile_index"] <= 1023 or
                        type(cell["horizontal_flip"]) is not bool or
                        type(cell["vertical_flip"]) is not bool or
                        type(cell["palette_index"]) is not int or not 0 <= cell["palette_index"] <= 15):
                    raise ValueError("opening BG map cell differs")
                value = (cell["tile_index"] | (int(cell["horizontal_flip"]) << 10) |
                         (int(cell["vertical_flip"]) << 11) | (cell["palette_index"] << 12))
                encoded += value.to_bytes(2, "little")
        data = bytes(encoded)
    if len(data) != entry["end"] - start or (verify_hash and sha256(data) != entry["source_sha256"]):
        raise ValueError("opening BG segment bytes differ from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if (int.from_bytes(rom[0x1404a0:0x1404a4], "little") != ROM_BASE + TILE_START or
            int.from_bytes(rom[0x1404a8:0x1404ac], "little") != (TILE_END - TILE_START) // 2 or
            any(int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start
                for literal, start in zip((0x1404ac, 0x1404b0), MAP_STARTS)) or
            rom[0x140468:0x14046c] != bytes.fromhex("80 24 e4 00")):
        raise ValueError("opening BG DMA sources or halfword counts differ")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening BG output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    segments = []
    for start, end, file_name, format_name in SOURCES:
        data = rom[start:end]
        fields = {"tiles": decode_tiles(data)} if format_name == "4bpp_tiles" else {"rows": decode_map(data)}
        (output / file_name).write_text(json.dumps(fields, separators=(",", ":")) + "\n")
        segments.append({"start": start, "end": end, "file": file_name,
                         "format": format_name, "source_sha256": sha256(data)})
    manifest = {"reference_sha256": ROM_SHA256, "segments": segments,
                "tile_count": (TILE_END - TILE_START) // 32,
                "map_dimensions": [32, 32],
                "tile_dma_caller": 0x08140454,
                "map_dma_callers": [0x08140464, 0x08140476],
                "scope_note": "The source formats and DMA lengths are bounded; map placement and the full opening frame are unresolved."}
    for start, end, _, _ in SOURCES:
        if encode_segment(manifest, output, start) != rom[start:end]:
            raise ValueError("opening BG export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"segments": len(segments), "tile_count": manifest["tile_count"],
            "source_bytes": sum(end - start for start, end, _, _ in SOURCES),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
