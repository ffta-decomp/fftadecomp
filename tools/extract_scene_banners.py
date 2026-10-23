#!/usr/bin/env python3
"""Extract the observed indexed scene-banner graphics archive.

The scene banner updater calls the retail decoder at 0x08005318 with the
archive at file offset 0x3ab42c.  The archive has a big-endian offset table
and one shared dictionary.  This tool decodes the bounded archive entries and
the frame-to-entry mapping used by the banner updater.  It writes decoded
4bpp tile bytes and machine-readable metadata outside the source tree; it
does not claim that a tile stream is a rendered banner without the retail
sprite/OAM consumer.
"""

import argparse
import json
from pathlib import Path

from indexed_graphics_codec import archive_token_plan, parse_archive, sha256, write_index_png

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
ARCHIVE = 0x083AB42C - ROM_BASE
FRAME_TO_GRAPHIC = 0x08391DE4 - ROM_BASE
FRAME_OFFSETS = 0x08391E02 - ROM_BASE
FRAME_COUNT = FRAME_OFFSETS - FRAME_TO_GRAPHIC
SPRITE_LIST_POINTERS = 0x08391A48 - ROM_BASE
SPRITE_LIST_COUNT = 5


def le16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def parse_frames(rom, archive):
    frames = []
    if FRAME_COUNT != 30:
        raise ValueError("observed scene banner frame table boundary changed")
    for frame in range(FRAME_COUNT):
        graphic = rom[FRAME_TO_GRAPHIC + frame]
        offset_bytes = le16(rom, FRAME_OFFSETS + frame * 2)
        entry = offset_bytes // 2 if offset_bytes % 2 == 0 else None
        count = graphic + 5
        valid = (entry is not None and entry + count <= len(archive["entries"]))
        item = {
            "frame": frame,
            "graphic": graphic,
            "offset_bytes": offset_bytes,
            "entry": entry,
            "entry_count": count,
            "valid_archive_reference": valid,
        }
        if valid:
            selected = archive["entries"][entry:entry + count]
            item["decoded_bytes"] = sum(x["decoded_bytes"] for x in selected)
            item["sha256"] = sha256(b"".join(x["raw"] for x in selected))
            item["source_offset"] = selected[0]["source_offset"]
            item["source_end"] = selected[-1]["source_end"]
        if not valid:
            raise ValueError(f"scene banner frame {frame} exceeds the archive")
        if frame and entry != frames[-1]["entry"] + frames[-1]["entry_count"]:
            raise ValueError(f"scene banner frame {frame} is not contiguous")
        frames.append(item)
    if frames[-1]["entry"] + frames[-1]["entry_count"] != len(archive["entries"]):
        raise ValueError("scene banner frame table does not cover the archive")
    return frames


def parse_sprite_lists(rom):
    dimensions = (
        ((8, 8), (16, 16), (32, 32), (64, 64)),
        ((16, 8), (32, 8), (32, 16), (64, 32)),
        ((8, 16), (8, 32), (16, 32), (32, 64)),
    )
    lists = []
    previous_end = None
    for graphic in range(SPRITE_LIST_COUNT):
        pointer = int.from_bytes(rom[SPRITE_LIST_POINTERS + graphic * 4:
                                     SPRITE_LIST_POINTERS + graphic * 4 + 4], "little")
        offset = pointer - ROM_BASE
        count = le16(rom, offset)
        end = offset + 2 + count * 6
        if count not in (2, 3) or (previous_end is not None and offset != previous_end):
            raise ValueError("scene banner sprite lists are not contiguous")
        if graphic == SPRITE_LIST_COUNT - 1 and end != SPRITE_LIST_POINTERS:
            raise ValueError("scene banner sprite lists do not meet their pointer table")
        sprites = []
        for index in range(count):
            record = offset + 2 + index * 6
            attr0, attr1, attr2 = (le16(rom, record + x) for x in (0, 2, 4))
            shape = (attr0 >> 14) & 3
            size = (attr1 >> 14) & 3
            if shape >= len(dimensions):
                raise ValueError("reserved GBA OBJ shape in banner sprite list")
            width, height = dimensions[shape][size]
            sprites.append({
                "sprite": index, "source_offset": record,
                "attr0": attr0, "attr1": attr1, "attr2": attr2,
                "x": attr1 & 0x1ff, "y": attr0 & 0xff,
                "width": width, "height": height,
                "tile_index": attr2 & 0x3ff,
                "palette_bank": (attr2 >> 12) & 15,
            })
        lists.append({"graphic": graphic, "source_offset": offset,
                      "source_end": end, "sha256": sha256(rom[offset:end]),
                      "sprite_count": count, "sprites": sprites})
        previous_end = end
    return lists


def rasterize_frame(raw, sprites):
    """Arrange observed 4bpp tiles through 1D OBJ mapping; retain indices."""
    base_tile = min(sprite["tile_index"] for sprite in sprites)
    x0 = min(sprite["x"] for sprite in sprites)
    y0 = min(sprite["y"] for sprite in sprites)
    width = max(sprite["x"] + sprite["width"] for sprite in sprites) - x0
    height = max(sprite["y"] + sprite["height"] for sprite in sprites) - y0
    pixels = bytearray(width * height)
    for sprite in sprites:
        tiles_x = sprite["width"] // 8
        tiles_y = sprite["height"] // 8
        first_tile = sprite["tile_index"] - base_tile
        for ty in range(tiles_y):
            for tx in range(tiles_x):
                tile = first_tile + ty * tiles_x + tx
                start = tile * 32
                if start + 32 > len(raw):
                    raise ValueError("banner sprite references a tile outside its decoded frame")
                for py in range(8):
                    for px in range(8):
                        packed = raw[start + py * 4 + px // 2]
                        color = (packed >> (4 * (px & 1))) & 15
                        x = sprite["x"] - x0 + tx * 8 + px
                        y = sprite["y"] - y0 + ty * 8 + py
                        pixels[y * width + x] = color
    return width, height, bytes(pixels)


def encode_sprite_table(manifest):
    """Re-encode the five contiguous OBJ lists and their ROM pointer words."""
    table = manifest["sprite_table"]
    lists = manifest["sprite_lists"]
    if (len(lists) != SPRITE_LIST_COUNT or table["end"] !=
            SPRITE_LIST_POINTERS + SPRITE_LIST_COUNT * 4):
        raise ValueError("scene banner sprite-table boundaries differ from retail")
    encoded = bytearray()
    for graphic, entry in enumerate(lists):
        if entry["graphic"] != graphic or entry["source_offset"] != table["start"] + len(encoded):
            raise ValueError("scene banner OBJ lists are not contiguous")
        sprites = entry["sprites"]
        if len(sprites) != entry["sprite_count"] or len(sprites) not in (2, 3):
            raise ValueError("scene banner OBJ list count differs from retail")
        data = len(sprites).to_bytes(2, "little")
        for sprite in sprites:
            for field in ("attr0", "attr1", "attr2"):
                value = sprite[field]
                if not 0 <= value <= 0xffff:
                    raise ValueError("scene banner OBJ attribute is not a halfword")
                data += value.to_bytes(2, "little")
        if entry["source_end"] != entry["source_offset"] + len(data) or \
                sha256(data) != entry["sha256"]:
            raise ValueError(f"scene banner OBJ list {graphic} differs from retail")
        encoded.extend(data)
    if table["start"] + len(encoded) != SPRITE_LIST_POINTERS:
        raise ValueError("scene banner OBJ lists do not reach their pointer table")
    encoded.extend(b"".join((ROM_BASE + entry["source_offset"]).to_bytes(4, "little")
                            for entry in lists))
    if len(encoded) != table["end"] - table["start"] or \
            sha256(encoded) != table["source_sha256"]:
        raise ValueError("scene banner sprite table differs from retail")
    return bytes(encoded)


def encode_frame_table(manifest):
    """Re-encode frame-to-graphic bytes and little-endian archive offsets."""
    table = manifest["frame_table"]
    frames = manifest["frames"]
    if (table["start"] != FRAME_TO_GRAPHIC or
            table["end"] != FRAME_OFFSETS + FRAME_COUNT * 2 or
            len(frames) != FRAME_COUNT):
        raise ValueError("scene banner frame-table boundaries differ from retail")
    graphics = bytearray()
    offsets = bytearray()
    for index, frame in enumerate(frames):
        graphic, offset = frame["graphic"], frame["offset_bytes"]
        if (frame["frame"] != index or not 0 <= graphic < SPRITE_LIST_COUNT or
                not 0 <= offset <= 0xffff):
            raise ValueError("scene banner frame-table value is invalid")
        graphics.append(graphic)
        offsets.extend(offset.to_bytes(2, "little"))
    encoded = bytes(graphics + offsets)
    if len(encoded) != table["end"] - table["start"] or \
            sha256(encoded) != table["source_sha256"]:
        raise ValueError("scene banner frame table differs from retail")
    return encoded


def export(rom, output):
    root = Path(__file__).resolve().parents[1]
    output = output.resolve()
    if output.is_relative_to(root):
        raise ValueError("banner output must be outside the source tree")
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")

    archive = parse_archive(rom, ARCHIVE)
    frames = parse_frames(rom, archive)
    sprite_lists = parse_sprite_lists(rom)
    dictionary_start = archive["table_file_offset"] + archive["dictionary_base"]
    dictionary = rom[dictionary_start:archive["dictionary_used_end"]]
    output.mkdir(parents=True, exist_ok=True)
    (output / "dictionary.bin").write_bytes(dictionary)
    entries_dir = output / "entries"
    frames_dir = output / "frames"
    previews_dir = output / "indexed-previews"
    entries_dir.mkdir(parents=True, exist_ok=True)
    frames_dir.mkdir(parents=True, exist_ok=True)
    previews_dir.mkdir(parents=True, exist_ok=True)
    entries = []
    for entry in archive["entries"]:
        (entries_dir / f"entry-{entry['entry']:03d}.4bpp").write_bytes(entry["raw"])
        item = {key: value for key, value in entry.items() if key != "raw"}
        item["tokens"] = archive_token_plan(
            rom, entry, archive["table_file_offset"], archive["bit_width"],
            archive["dictionary_base"])
        item["source_sha256"] = sha256(rom[entry["source_offset"]:entry["source_end"]])
        entries.append(item)
    for frame in frames:
        if not frame["valid_archive_reference"]:
            continue
        data = b"".join(archive["entries"][i]["raw"]
                        for i in range(frame["entry"], frame["entry"] + frame["entry_count"]))
        (frames_dir / f"frame-{frame['frame']:03d}.4bpp").write_bytes(data)
        width, height, pixels = rasterize_frame(data, sprite_lists[frame["graphic"]]["sprites"])
        frame["indexed_width"] = width
        frame["indexed_height"] = height
        frame["indexed_sha256"] = sha256(pixels)
        write_index_png(previews_dir / f"frame-{frame['frame']:03d}.png", width, height, pixels)
    report = {
        "reference_sha256": ROM_SHA256,
        "archive_file_offset": ARCHIVE,
        "archive_header_bytes": rom[ARCHIVE:ARCHIVE + 8].hex(),
        "decoder_entry_thumb": "0x08005318",
        "decoder_block_thumb": "0x080051c4",
        "frame_to_graphic_file_offset": FRAME_TO_GRAPHIC,
        "frame_offsets_file_offset": FRAME_OFFSETS,
        "frame_count": FRAME_COUNT,
        "sprite_list_pointer_table_file_offset": SPRITE_LIST_POINTERS,
        "sprite_lists": sprite_lists,
        "archive": {
            "entry_count": len(entries),
            "table_offset": archive["table_offset"],
            "offsets": archive["offsets"],
            "mode": archive["mode"],
            "bit_width": archive["bit_width"],
            "decoded_bytes_per_entry": archive["decoded_bytes_per_entry"],
            "dictionary_sha256": sha256(dictionary),
            "source_span_bytes": archive["dictionary_used_end"] - ARCHIVE,
            "source_span_sha256": sha256(rom[ARCHIVE:archive["dictionary_used_end"]]),
            "tile_directory": "entries",
            "tile_stem": "entry",
            "tile_index_width": 3,
        },
        "sprite_table": {
            "start": sprite_lists[0]["source_offset"],
            "end": SPRITE_LIST_POINTERS + SPRITE_LIST_COUNT * 4,
            "source_sha256": sha256(rom[sprite_lists[0]["source_offset"]:
                                        SPRITE_LIST_POINTERS + SPRITE_LIST_COUNT * 4]),
        },
        "frame_table": {
            "start": FRAME_TO_GRAPHIC,
            "end": FRAME_OFFSETS + FRAME_COUNT * 2,
            "source_sha256": sha256(rom[FRAME_TO_GRAPHIC:FRAME_OFFSETS + FRAME_COUNT * 2]),
        },
        "entry_count": len(archive["entries"]),
        "entries": entries,
        "frames": frames,
        "valid_frame_count": sum(frame["valid_archive_reference"] for frame in frames),
        "invalid_frame_count": sum(not frame["valid_archive_reference"] for frame in frames),
        "caveat": (
            "Indexed PNG previews apply the observed banner OBJ lists and 1D tile order "
            "to the decoded 4bpp bytes. Their grayscale values are palette indices, not "
            "retail colors or final scene placement. The observed frames contain "
            "location-name lettering; this archive is not counted as character art."
        ),
    }
    (output / "manifest.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    report = export(args.rom.read_bytes(), args.output_dir)
    print(json.dumps({
        "entry_count": report["entry_count"],
        "decoded_bytes": sum(x["decoded_bytes"] for x in report["entries"]),
        "valid_frame_count": report["valid_frame_count"],
        "invalid_frame_count": report["invalid_frame_count"],
    }))


if __name__ == "__main__":
    main()
