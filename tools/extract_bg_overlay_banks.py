"""Extract the five consumer-indexed BG tile banks and screen-entry grids."""

import hashlib
import json
import struct
from pathlib import Path

from indexed_graphics_codec import (rasterize_4bpp_grid, read_index_png,
                                    serialize_4bpp_grid, write_index_png)


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TILE_POINTER_TABLE = 0x3A7798
TILE_LENGTH_TABLE = 0x3A77AC
MAP_POINTER_TABLE = 0x3A77B8
MAP_DIMENSIONS_TABLE = 0x3A77CC
TILE_START = 0x509F18
MAP_START = 0x519F98
END = 0x51B88C
GROUPS = 5
TILES_PER_PAGE = 64
TILE_STARTS = (0x509F18, 0x50CA78, 0x510438, 0x513A18, 0x5185F8)
TILE_LENGTHS = (11104, 14784, 13792, 19424, 6560)
MAP_STARTS = (0x519F98, 0x51A40C, 0x51A88C, 0x51AF7C, 0x51B5BC)
MAP_WIDTHS = (15, 18, 37, 16, 18)
DISPLAY_ROWS = (38, 32, 23, 50, 20)
STORED_ROWS = (38, 32, 24, 50, 20)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def checked_path(directory, name):
    path = (directory / name).resolve()
    if not path.is_relative_to(directory.resolve()):
        raise ValueError("BG overlay asset path leaves its export directory")
    return path


def source_layout(rom):
    if digest(rom) != ROM_SHA256:
        raise ValueError("BG overlay source is not the pinned retail ROM")
    tile_starts = [struct.unpack_from("<I", rom, TILE_POINTER_TABLE + 4 * group)[0] - ROM_BASE
                   for group in range(GROUPS)]
    tile_lengths = list(struct.unpack_from("<5H", rom, TILE_LENGTH_TABLE))
    map_starts = [struct.unpack_from("<I", rom, MAP_POINTER_TABLE + 4 * group)[0] - ROM_BASE
                  for group in range(GROUPS)]
    widths = [rom[MAP_DIMENSIONS_TABLE + 4 * group] for group in range(GROUPS)]
    display_rows = [rom[MAP_DIMENSIONS_TABLE + 4 * group + 1]
                    for group in range(GROUPS)]
    if (tile_starts != list(TILE_STARTS) or
            tile_lengths != list(TILE_LENGTHS) or
            map_starts != list(MAP_STARTS) or
            widths != list(MAP_WIDTHS) or
            display_rows != list(DISPLAY_ROWS) or
            struct.unpack_from("<I", rom, 0x11FB08)[0] != ROM_BASE + TILE_POINTER_TABLE or
            struct.unpack_from("<I", rom, 0x11FB0C)[0] != ROM_BASE + TILE_LENGTH_TABLE or
            struct.unpack_from("<I", rom, 0x11FBB4)[0] != ROM_BASE + MAP_POINTER_TABLE or
            struct.unpack_from("<I", rom, 0x11FBB0)[0] != ROM_BASE + MAP_DIMENSIONS_TABLE or
            struct.unpack_from("<I", rom, 0x13FA98)[0] != ROM_BASE + END):
        raise ValueError("BG overlay consumer tables differ from the pinned layout")
    if any(start + length != next_start for start, length, next_start in
           zip(tile_starts, tile_lengths, tile_starts[1:] + [MAP_START])):
        raise ValueError("BG overlay tile banks are not contiguous")
    map_ends = map_starts[1:] + [END]
    if any((end - start) % (width * 2) for start, end, width in
           zip(map_starts, map_ends, widths)):
        raise ValueError("BG overlay grid does not contain whole stored rows")
    if tuple((end - start) // (2 * width) for start, end, width in
             zip(map_starts, map_ends, widths)) != STORED_ROWS:
        raise ValueError("BG overlay stored map rows differ")
    return [{"group": group, "tile_start": tile_starts[group],
             "tile_end": tile_starts[group] + tile_lengths[group],
             "tile_count": tile_lengths[group] // 32,
             "map_start": map_starts[group], "map_end": map_ends[group],
             "width": widths[group], "display_rows": display_rows[group],
             "stored_rows": (map_ends[group] - map_starts[group]) // (2 * widths[group])}
            for group in range(GROUPS)]


def map_entry(value):
    return {"tile_index": value & 0x3FF,
            "horizontal_flip": bool(value & 0x400),
            "vertical_flip": bool(value & 0x800),
            "palette_index": value >> 12}


def encode_map_entry(cell):
    if (type(cell) is not dict or
            type(cell.get("tile_index")) is not int or not 0 <= cell["tile_index"] <= 1023 or
            type(cell.get("horizontal_flip")) is not bool or
            type(cell.get("vertical_flip")) is not bool or
            type(cell.get("palette_index")) is not int or not 0 <= cell["palette_index"] <= 15):
        raise ValueError("BG overlay map cell has invalid bit fields")
    return (cell["tile_index"] | int(cell["horizontal_flip"]) << 10 |
            int(cell["vertical_flip"]) << 11 | cell["palette_index"] << 12)


def source_files(manifest):
    return [page["file"] for group in manifest["groups"] for page in group["pages"]] + [
        group["map_file"] for group in manifest["groups"]]


def encode(manifest, directory, *, verify_retail=False):
    if (manifest.get("reference_sha256") != ROM_SHA256 or
            manifest.get("start") != TILE_START or manifest.get("end") != END or
            len(manifest.get("groups", [])) != GROUPS):
        raise ValueError("BG overlay manifest revision or extent differs")
    output = bytearray()
    for index, group in enumerate(manifest["groups"]):
        if (group["group"] != index or group["tile_start"] != TILE_STARTS[index] or
                group["tile_start"] != TILE_START + len(output) or
                group["tile_end"] - group["tile_start"] != TILE_LENGTHS[index] or
                group["tile_count"] != TILE_LENGTHS[index] // 32 or
                group["map_start"] != MAP_STARTS[index] or
                group["map_end"] != (MAP_STARTS[index + 1] if index < 4 else END) or
                group["width"] != MAP_WIDTHS[index] or
                group["display_rows"] != DISPLAY_ROWS[index] or
                group["stored_rows"] != STORED_ROWS[index]):
            raise ValueError("BG overlay tile bank order differs")
        tile_data = bytearray()
        expected_tile = 0
        for page in group["pages"]:
            count = page["tile_count"]
            if (page["tile_start"] != expected_tile or not 1 <= count <= TILES_PER_PAGE or
                    page["file"] != f"tiles/group-{index}-page-{expected_tile // TILES_PER_PAGE:02d}.png"):
                raise ValueError("BG overlay tile page plan differs")
            width, height, pixels = read_index_png(checked_path(directory, page["file"]))
            rows = (count + 7) // 8
            if (width, height) != (64, rows * 8):
                raise ValueError("BG overlay tile PNG dimensions differ")
            packed = serialize_4bpp_grid(pixels, 8, rows)
            if any(packed[count * 32:]):
                raise ValueError("BG overlay padded PNG tiles must stay zero")
            tile_data.extend(packed[:count * 32])
            expected_tile += count
        if (expected_tile != group["tile_count"] or
                len(tile_data) != group["tile_end"] - group["tile_start"] or
                len(tile_data) % 32):
            raise ValueError("BG overlay tile bank size differs")
        if verify_retail and digest(tile_data) != group["tile_sha256"]:
            raise ValueError("BG overlay tile bank differs from retail")
        output.extend(tile_data)
    for index, group in enumerate(manifest["groups"]):
        if group["map_start"] != TILE_START + len(output):
            raise ValueError("BG overlay map order differs")
        fields = json.loads(checked_path(directory, group["map_file"]).read_text())
        rows = fields["rows"]
        if (group["map_file"] != f"maps/group-{index}.json" or
                type(rows) is not list or len(rows) != group["stored_rows"] or
                group["stored_rows"] < group["display_rows"] or
                any(type(row) is not list or len(row) != group["width"] for row in rows)):
            raise ValueError("BG overlay map dimensions differ")
        packed = b"".join(struct.pack("<H", encode_map_entry(cell))
                          for row in rows for cell in row)
        if len(packed) != group["map_end"] - group["map_start"]:
            raise ValueError("BG overlay map size differs")
        if verify_retail and digest(packed) != group["map_sha256"]:
            raise ValueError("BG overlay map differs from retail")
        output.extend(packed)
    if len(output) != END - TILE_START:
        raise ValueError("BG overlay encoded extent differs")
    return bytes(output)


def export(rom, directory):
    directory = directory.resolve()
    if directory.is_relative_to(Path(__file__).resolve().parents[1]) or directory.exists():
        raise ValueError("BG overlay output must be a new external directory")
    layout = source_layout(rom)
    (directory / "tiles").mkdir(parents=True)
    (directory / "maps").mkdir()
    (directory / "preview").mkdir()
    groups = []
    for group in layout:
        index = group["group"]
        tile_data = rom[group["tile_start"]:group["tile_end"]]
        pages = []
        for first in range(0, group["tile_count"], TILES_PER_PAGE):
            count = min(TILES_PER_PAGE, group["tile_count"] - first)
            rows = (count + 7) // 8
            block = tile_data[first * 32:(first + count) * 32] + bytes((rows * 8 - count) * 32)
            pixels = rasterize_4bpp_grid(block, 8, rows)
            file_name = f"tiles/group-{index}-page-{first // TILES_PER_PAGE:02d}.png"
            write_index_png(directory / file_name, 64, rows * 8, pixels)
            pages.append({"tile_start": first, "tile_count": count, "file": file_name})
        map_data = rom[group["map_start"]:group["map_end"]]
        values = struct.unpack(f"<{len(map_data) // 2}H", map_data)
        width = group["width"]
        rows = [[map_entry(value) for value in values[row * width:(row + 1) * width]]
                for row in range(group["stored_rows"])]
        map_file = f"maps/group-{index}.json"
        (directory / map_file).write_text(json.dumps({"rows": rows}, separators=(",", ":")) + "\n")
        preview = bytearray(width * 8 * group["display_rows"] * 8)
        missing = 0
        for row in range(group["display_rows"]):
            for col, cell in enumerate(rows[row]):
                tile = cell["tile_index"]
                if tile >= group["tile_count"]:
                    missing += 1
                    continue
                for y in range(8):
                    for x in range(8):
                        source_x = 7 - x if cell["horizontal_flip"] else x
                        source_y = 7 - y if cell["vertical_flip"] else y
                        packed = tile_data[tile * 32 + source_y * 4 + source_x // 2]
                        preview[(row * 8 + y) * width * 8 + col * 8 + x] = (
                            packed >> (4 * (source_x & 1))) & 15
        preview_file = f"preview/group-{index}.png"
        write_index_png(directory / preview_file, width * 8,
                        group["display_rows"] * 8, preview)
        groups.append({**group, "pages": pages, "map_file": map_file,
                       "tile_sha256": digest(tile_data), "map_sha256": digest(map_data),
                       "preview_file": preview_file, "missing_tile_cells": missing})
    manifest = {"reference_sha256": ROM_SHA256, "start": TILE_START,
                "end": END, "groups": groups,
                "consumer_thumb": ["0x0811fada", "0x0811fb4c"],
                "scope": "Indexed tile/map source reconstruction; preview uses gray indices, not an observed runtime palette or final screen composition."}
    if encode(manifest, directory, verify_retail=True) != rom[TILE_START:END]:
        raise ValueError("BG overlay export does not reproduce retail")
    path = directory / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"groups": GROUPS, "tile_count": sum(g["tile_count"] for g in groups),
            "source_bytes": END - TILE_START,
            "tile_bytes": MAP_START - TILE_START,
            "map_bytes": END - MAP_START,
            "missing_preview_cells": [g["missing_tile_cells"] for g in groups],
            "manifest_sha256": digest(path.read_bytes())}
