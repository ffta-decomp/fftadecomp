#!/usr/bin/env python3
"""Export the directly loaded world-map display tiles, maps, and palettes."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
PALETTE_TABLE = 0x3a8c54
PALETTE_START = 0x9581d8
PALETTE_END = 0x958dd8
PALETTE_BYTES = 0x200
EXISTING_INTRO_PALETTE = (0x9569b4, 0x9569d0)
EXISTING_INTRO_GRAPHICS = (0x96a1ac, 0x96bdea)
SOURCES = (
    (0x9564fc, 1200, "u16_tilemap", 0x13bf4c),
    (0x9569ac, 32, "bgr555_palette", 0x13bf58),
    (0x9569f8, 0x980, "4bpp_tiles", 0x13bf3c),
    (0x957378, 1280, "u16_tilemap", 0x135e58),
    (0x957878, 1200, "u16_tilemap", 0x135e60),
    (0x957d28, 1200, "u16_tilemap", 0x135e68),
    (0x958dd8, 0x8000, "4bpp_tiles", 0x135e3c),
    (0x960ec0, 0x39a8, "vram_halfwords", 0x135e40),
    (0x964838, 0x2d78, "vram_halfwords", 0x135e4c),
    (0x9675ac, 0x2cb4, "vram_halfwords", 0x135f1c),
)
DISPLAY_CORE_EXCLUDED_SOURCES = {0x9569f8, 0x9675ac}


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def union_size(ranges):
    total = 0
    end = 0
    for start, next_end in sorted(ranges):
        if next_end < start:
            raise ValueError("world-map display range is reversed")
        total += max(0, next_end - max(start, end))
        end = max(end, next_end)
    return total


def encode_halfwords(values, expected_count):
    if len(values) != expected_count or any(type(value) is not int or not 0 <= value <= 0xffff
                                            for value in values):
        raise ValueError("world-map halfword count or value differs")
    return b"".join(value.to_bytes(2, "little") for value in values)


def encode_display_source(manifest, source_dir, offset):
    matches = [entry for entry in manifest["sources"] if entry["start"] == offset]
    if len(matches) != 1:
        raise ValueError("world-map display source is not unique")
    entry = matches[0]
    path = source_dir / entry["file"]
    if entry["format"] == "4bpp_tiles":
        data = path.read_bytes()
        if len(data) % 32:
            raise ValueError("world-map tile bank is not 4bpp tile-aligned")
    else:
        field = "bgr555" if entry["format"] == "bgr555_palette" else "halfwords"
        data = encode_halfwords(json.loads(path.read_text())[field], entry["size"] // 2)
    if len(data) != entry["size"] or sha256(data) != entry["source_sha256"]:
        raise ValueError("world-map display source differs from retail")
    return data


def encode_palette_bank(manifest, source_dir):
    data = bytearray()
    for index, entry in enumerate(manifest["palettes"]):
        if entry["start"] != PALETTE_START + index * PALETTE_BYTES:
            raise ValueError("world-map palette order differs")
        values = json.loads((source_dir / entry["file"]).read_text())["bgr555"]
        encoded = encode_halfwords(values, 256)
        if sha256(encoded) != entry["source_sha256"]:
            raise ValueError("world-map palette differs from retail")
        data += encoded
    if len(data) != PALETTE_END - PALETTE_START or sha256(data) != manifest["palette_bank"]["source_sha256"]:
        raise ValueError("world-map palette bank differs from retail")
    return bytes(data)


def encode_palette_table(manifest):
    indices = manifest["palette_table"]["indices"]
    if len(indices) != 6 or any(type(index) is not int or not 0 <= index < 6 for index in indices):
        raise ValueError("world-map palette table index differs")
    data = b"".join((ROM_BASE + PALETTE_START + index * PALETTE_BYTES).to_bytes(4, "little")
                    for index in indices)
    if sha256(data) != manifest["palette_table"]["source_sha256"]:
        raise ValueError("world-map palette table differs from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if int.from_bytes(rom[0x135f24:0x135f28], "little") != 0x165a:
        raise ValueError("world-map CpuSet halfword count differs")
    if int.from_bytes(rom[0x13bf40:0x13bf44], "little") != 0x4d6:
        raise ValueError("small-map CpuSet halfword count differs")
    output.mkdir(parents=True, exist_ok=True)
    sources = []
    for offset, size, format_name, literal in SOURCES:
        if int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + offset:
            raise ValueError("world-map display caller no longer references its source")
        data = rom[offset:offset + size]
        if format_name == "4bpp_tiles":
            name = f"display-0x{offset:06x}.4bpp"
            (output / name).write_bytes(data)
        else:
            name = f"display-0x{offset:06x}.json"
            field = "bgr555" if format_name == "bgr555_palette" else "halfwords"
            (output / name).write_text(json.dumps({field: [int.from_bytes(data[pos:pos + 2], "little")
                                                   for pos in range(0, size, 2)]}, indent=2) + "\n")
        sources.append({"start": offset, "size": size, "format": format_name,
                        "literal": literal, "file": name, "source_sha256": sha256(data)})
    table = rom[PALETTE_TABLE:PALETTE_TABLE + 24]
    indices = [(int.from_bytes(table[pos:pos + 4], "little") - ROM_BASE - PALETTE_START) // PALETTE_BYTES
               for pos in range(0, 24, 4)]
    if indices != [0, 1, 4, 5, 2, 3] or any(
            int.from_bytes(table[pos:pos + 4], "little") != ROM_BASE + PALETTE_START + indices[pos // 4] * PALETTE_BYTES
            for pos in range(0, 24, 4)):
        raise ValueError("world-map palette table layout differs")
    palettes = []
    for index in range(6):
        start = PALETTE_START + index * PALETTE_BYTES
        data = rom[start:start + PALETTE_BYTES]
        name = f"palette-{index}.json"
        (output / name).write_text(json.dumps({"bgr555": [int.from_bytes(data[pos:pos + 2], "little")
                                                           for pos in range(0, PALETTE_BYTES, 2)]}, indent=2) + "\n")
        palettes.append({"start": start, "file": name, "source_sha256": sha256(data)})
    exported_ranges = ([(entry["start"], entry["start"] + entry["size"]) for entry in sources]
                       + [(PALETTE_TABLE, PALETTE_TABLE + 24), (PALETTE_START, PALETTE_END)])
    exported_bytes = sum(end - start for start, end in exported_ranges)
    unique_bytes = union_size(exported_ranges)
    existing_ranges = [EXISTING_INTRO_PALETTE, EXISTING_INTRO_GRAPHICS]
    new_bytes = union_size(exported_ranges + existing_ranges) - union_size(existing_ranges)
    core_ranges = ([(entry["start"], entry["start"] + entry["size"]) for entry in sources
                    if entry["start"] not in DISPLAY_CORE_EXCLUDED_SOURCES]
                   + [(PALETTE_TABLE, PALETTE_TABLE + 24), (PALETTE_START, PALETTE_END)])
    display_core_coverage = {
        "exported_bytes": sum(end - start for start, end in core_ranges),
        "unique_source_bytes": union_size(core_ranges),
        "new_selected_bytes": union_size(core_ranges + existing_ranges) - union_size(existing_ranges),
    }
    if display_core_coverage != {"exported_bytes": 67176, "unique_source_bytes": 67128,
                                 "new_selected_bytes": 67104}:
        raise ValueError("world-map display core coverage differs from the pinned build")
    coverage = {"exported_bytes": exported_bytes, "unique_source_bytes": unique_bytes,
                "new_selected_bytes": new_bytes, "existing_intro_palette": list(EXISTING_INTRO_PALETTE),
                "existing_intro_graphics": list(EXISTING_INTRO_GRAPHICS),
                "display_core": display_core_coverage}
    manifest = {"reference_sha256": ROM_SHA256, "sources": sources,
                "palette_table": {"start": PALETTE_TABLE, "end": PALETTE_TABLE + 24,
                                  "indices": indices, "source_sha256": sha256(table)},
                "palette_bank": {"start": PALETTE_START, "end": PALETTE_END,
                                 "source_sha256": sha256(rom[PALETTE_START:PALETTE_END])},
                "palettes": palettes, "coverage": coverage,
                "small_map_copy": {"source_start": 0x9569f8, "source_end": 0x9573a4,
                                   "tile_count": 76, "shared_map_tail_bytes": 44,
                                   "caller": 0x0813bef0, "bios_stub": 0x0814186c},
                "consumers": {"tilemap_writer": 0x08135fa0,
                              "display_loader": 0x08135d6c, "small_map_loader": 0x0813beec},
        "caveat": "The four display-loader VRAM copies and the small-map tile copy use BIOS CpuSet halfword counts. The latter three display-loader sources are exported as VRAM halfwords because their pixel layout is not established; final screen composition remains open."}
    for entry in sources:
        if encode_display_source(manifest, output, entry["start"]) != rom[entry["start"]:entry["start"] + entry["size"]]:
            raise ValueError("world-map display export does not round-trip")
    if (encode_palette_bank(manifest, output) != rom[PALETTE_START:PALETTE_END] or
            encode_palette_table(manifest) != table):
        raise ValueError("world-map palette export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"sources": len(sources), "palette_records": len(palettes),
            "exported_bytes": display_core_coverage["exported_bytes"],
            "unique_source_bytes": display_core_coverage["unique_source_bytes"],
            "new_selected_bytes": display_core_coverage["new_selected_bytes"],
            "all_exported_sources": coverage,
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
