#!/usr/bin/env python3
"""Extract the retail sprite pixel bank through its resource, frame, and OAM tables.

The resource resolver at 0x08021004 indexes the 248-word table. The frame
consumer adds offsets to pixel bank 0x0869b89c and OAM bank 0x08852e7c.
The base export remains indexed 4bpp; verified palette overrides are separate.
Static OAM composition does not establish runtime screen placement or timing.
"""

import argparse
import json
from pathlib import Path

from indexed_graphics_codec import (rasterize_4bpp_grid, serialize_4bpp_grid,
                                    read_index_png, sha256, write_index_png)
from rgba_palette_codec import read_rgba_png, rgba_to_indices

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
TABLE = 0x390E44
TABLE_COUNT = 248
PIXEL_BASE = 0x69B89C
OAM_BASE = 0x852E7C
DESCRIPTOR_BASE = 0x8540FC
DESCRIPTOR_END = 0x8E9C08
PIXEL_BYTES = OAM_BASE - PIXEL_BASE
ITEM_TABLE = 0x51D180
ITEM_COUNT = 376

SIZES = (
    ((8, 8), (16, 16), (32, 32), (64, 64)),
    ((16, 8), (32, 8), (32, 16), (64, 32)),
    ((8, 16), (8, 32), (16, 32), (32, 64)),
)


def u16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def u32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def file_pointer(data, offset):
    pointer = u32(data, offset)
    if not ROM_BASE <= pointer < ROM_BASE + len(data):
        raise ValueError(f"invalid ROM pointer at {offset:#x}: {pointer:#x}")
    return pointer - ROM_BASE


def parse_oam_list(rom, relative_offset):
    start = OAM_BASE + relative_offset
    if not OAM_BASE <= start < DESCRIPTOR_BASE:
        raise ValueError("OAM pointer leaves the bounded OAM bank")
    count = u16(rom, start)
    if not 1 <= count <= 9 or start + 2 + count * 6 > DESCRIPTOR_BASE:
        raise ValueError("OAM entry count or end is invalid")
    objects = []
    for index in range(count):
        position = start + 2 + index * 6
        attr0, attr1, attr2 = (u16(rom, position + field) for field in (0, 2, 4))
        shape, size = (attr0 >> 14) & 3, (attr1 >> 14) & 3
        if shape == 3 or attr0 & 0x3f00 or attr1 & 0x3e00 or attr2 & 0xfc00:
            raise ValueError(f"unsupported OAM mode at {position:#x}")
        width, height = SIZES[shape][size]
        objects.append({
            "attr0": attr0, "attr1": attr1, "attr2": attr2,
            "tile_index": attr2 & 0x3ff,
            "tile_count": width * height // 64,
            "width": width, "height": height,
        })
    tile_indices = sorted(tile for obj in objects for tile in
                          range(obj["tile_index"], obj["tile_index"] + obj["tile_count"]))
    if tile_indices != list(range(len(tile_indices))):
        raise ValueError(f"OAM list {relative_offset:#x} is not packed from tile zero")
    return {
        "relative_offset": relative_offset,
        "source_start": start,
        "source_end": start + 2 + count * 6,
        "source_sha256": sha256(rom[start:start + 2 + count * 6]),
        "tile_count": len(tile_indices),
        "objects": objects,
    }


def parse_sprite_bank(rom):
    block_starts = sorted({file_pointer(rom, TABLE + 4 * index)
                           for index in range(TABLE_COUNT)})
    if len(block_starts) != 245 or block_starts[0] != 0x36DAA4:
        raise ValueError("retail sprite pointer blocks differ from the observed layout")
    block_end_by_start = dict(zip(block_starts, block_starts[1:] + [TABLE]))
    descriptor_offsets = set()
    pointer_groups = 0
    nonzero_slots = 0
    pointer_slots = []
    for start, end in block_end_by_start.items():
        if not start < end <= TABLE or (end - start) % 24:
            raise ValueError("sprite pointer block has an invalid six-slot group")
        pointer_groups += (end - start) // 24
        for position in range(start, end, 4):
            pointer = u32(rom, position)
            if pointer:
                descriptor_offset = file_pointer(rom, position)
                descriptor_offsets.add(descriptor_offset)
                pointer_slots.append(descriptor_offset)
                nonzero_slots += 1
            else:
                pointer_slots.append(0)
    if min(descriptor_offsets) != DESCRIPTOR_BASE:
        raise ValueError("sprite descriptor region starts unexpectedly")

    descriptors = []
    frame_references = []
    oam_offsets = set()
    control_frames = 0
    for start in sorted(descriptor_offsets):
        frame_count = u32(rom, start)
        end = start + 4 + frame_count * 20
        if not 1 <= frame_count <= 64 or end > len(rom):
            raise ValueError(f"descriptor at {start:#x} has an invalid frame count")
        records = []
        for index in range(frame_count):
            position = start + 4 + index * 20
            pixel_offset = u32(rom, position)
            oam_offset = u32(rom, position + 4)
            kind = rom[position + 9]
            records.append({
                "pixel_offset": pixel_offset,
                "oam_offset": oam_offset,
                "field_08": rom[position + 8],
                "kind_09": kind,
                "field_0a": u16(rom, position + 10),
                "field_0c": u16(rom, position + 12),
                "field_0e": u16(rom, position + 14),
                "field_10": u16(rom, position + 16),
                "field_12": u16(rom, position + 18),
            })
            if pixel_offset in (0xffff, 0xffffffff) or oam_offset == 0xffffffff:
                control_frames += 1
                continue
            if pixel_offset >= PIXEL_BYTES:
                raise ValueError(f"frame at {position:#x} leaves pixel bank")
            oam_offsets.add(oam_offset)
            frame_references.append({"record_offset": position,
                                     "pixel_offset": pixel_offset,
                                     "oam_offset": oam_offset, "kind": kind})
        descriptors.append({"source_start": start, "source_end": end,
                            "frame_count": frame_count, "records": records,
                            "source_sha256": sha256(rom[start:end])})
    for earlier, later in zip(descriptors, descriptors[1:]):
        if earlier["source_end"] > later["source_start"]:
            raise ValueError("sprite descriptors overlap")
    if descriptors[-1]["source_end"] != DESCRIPTOR_END:
        raise ValueError("sprite descriptor region ends unexpectedly")
    cursor = DESCRIPTOR_BASE
    alignment_bytes = 0
    for descriptor in descriptors:
        gap = rom[cursor:descriptor["source_start"]]
        if any(gap):
            raise ValueError("sprite descriptor gap is not zero padding")
        alignment_bytes += len(gap)
        cursor = descriptor["source_end"]
    if alignment_bytes != 37036:
        raise ValueError("sprite descriptor padding count differs from retail")
    oam_lists = {offset: parse_oam_list(rom, offset) for offset in sorted(oam_offsets)}
    frames = {}
    coverage = bytearray(PIXEL_BYTES)
    for reference in frame_references:
        offset = reference["pixel_offset"]
        oam = oam_lists[reference["oam_offset"]]
        byte_count = oam["tile_count"] * 32
        if offset + byte_count > PIXEL_BYTES:
            raise ValueError("frame pixels exceed sprite bank")
        key = (offset, reference["oam_offset"])
        frames[key] = {"pixel_offset": offset, "oam_offset": key[1],
                       "byte_count": byte_count,
                       "source_sha256": sha256(rom[PIXEL_BASE + offset:
                                                    PIXEL_BASE + offset + byte_count])}
        coverage[offset:offset + byte_count] = b"\1" * byte_count
    if not all(coverage):
        raise ValueError(f"sprite pixel bank has {coverage.count(0)} uncovered bytes")
    return {
        "resource_entries": [file_pointer(rom, TABLE + 4 * index)
                             for index in range(TABLE_COUNT)],
        "block_starts": block_starts,
        "pointer_groups": pointer_groups,
        "pointer_slots": pointer_slots,
        "nonzero_pointer_slots": nonzero_slots,
        "descriptors": descriptors,
        "descriptor_bank": {"start": DESCRIPTOR_BASE, "end": DESCRIPTOR_END,
                            "record_bytes": sum(d["source_end"] - d["source_start"]
                                                for d in descriptors),
                            "alignment_bytes": alignment_bytes,
                            "source_sha256": sha256(rom[DESCRIPTOR_BASE:DESCRIPTOR_END])},
        "frame_references": frame_references,
        "control_frames": control_frames,
        "oam_lists": oam_lists,
        "frames": [frames[key] for key in sorted(frames)],
    }


def compose_indexed_frame(raw, oam):
    """Apply the observed one-dimensional OBJ tile indices and static positions."""
    positioned = []
    for obj in oam["objects"]:
        x = obj["attr1"] & 0x1ff
        y = obj["attr0"] & 0xff
        if x >= 256:
            x -= 512
        if y >= 128:
            y -= 256
        positioned.append((x, y, obj))
    min_x = min(x for x, _, _ in positioned)
    min_y = min(y for _, y, _ in positioned)
    width = max(x + obj["width"] for x, _, obj in positioned) - min_x
    height = max(y + obj["height"] for _, y, obj in positioned) - min_y
    if not 0 < width <= 64 or not 0 < height <= 64:
        raise ValueError("composed sprite dimensions are outside observed bounds")
    canvas = bytearray(width * height)
    # Lower OAM indices have display priority over later objects.
    for x, y, obj in reversed(positioned):
        start = obj["tile_index"] * 32
        end = start + obj["tile_count"] * 32
        tile_data = raw[start:end]
        tile_width = obj["width"] // 8
        tile_height = obj["height"] // 8
        pixels = rasterize_4bpp_grid(tile_data, tile_width, tile_height)
        if serialize_4bpp_grid(pixels, tile_width, tile_height) != tile_data:
            raise ValueError("composed object tiles failed 4bpp round trip")
        for row in range(obj["height"]):
            for column in range(obj["width"]):
                value = pixels[row * obj["width"] + column]
                if value:
                    canvas[(y - min_y + row) * width + x - min_x + column] = value
    return width, height, bytes(canvas)


def decompose_indexed_frame(pixels, width, height, oam):
    """Invert a composed frame when its OBJ rectangles do not overlap."""
    positioned = []
    for obj in oam["objects"]:
        x, y = obj["attr1"] & 0x1ff, obj["attr0"] & 0xff
        positioned.append((x - 512 if x >= 256 else x,
                           y - 256 if y >= 128 else y, obj))
    left = min(x for x, _, _ in positioned)
    top = min(y for _, y, _ in positioned)
    if (width, height) != (
            max(x + obj["width"] for x, _, obj in positioned) - left,
            max(y + obj["height"] for _, y, obj in positioned) - top):
        raise ValueError("composed sprite dimensions differ from OAM")
    if len(pixels) != width * height:
        raise ValueError("composed sprite pixel count differs")
    raw = bytearray(oam["tile_count"] * 32)
    covered = bytearray(len(pixels))
    for x, y, obj in positioned:
        object_pixels = bytearray()
        for row in range(obj["height"]):
            start = (y - top + row) * width + x - left
            for column in range(obj["width"]):
                site = start + column
                if covered[site]:
                    raise ValueError("overlapping OAM objects need separate layer PNGs")
                covered[site] = 1
                object_pixels.append(pixels[site])
        object_raw = serialize_4bpp_grid(
            object_pixels, obj["width"] // 8, obj["height"] // 8)
        start = obj["tile_index"] * 32
        raw[start:start + len(object_raw)] = object_raw
    if any(value and not covered[index] for index, value in enumerate(pixels)):
        raise ValueError("composed sprite has pixels outside OAM objects")
    return bytes(raw)


def export(rom, result, output):
    frame_dir = output / "frames"
    composed_dir = output / "composed-indexed-frames"
    layer_dir = output / "object-layers"
    preview_dir = output / "item-indexed-previews"
    frame_dir.mkdir(parents=True, exist_ok=True)
    composed_dir.mkdir(parents=True, exist_ok=True)
    layer_dir.mkdir(parents=True, exist_ok=True)
    preview_dir.mkdir(parents=True, exist_ok=True)
    for frame in result["frames"]:
        start = PIXEL_BASE + frame["pixel_offset"]
        raw = rom[start:start + frame["byte_count"]]
        (frame_dir / f"{frame['pixel_offset']:06x}-{frame['oam_offset']:04x}.4bpp").write_bytes(raw)
        # The packed tile sequence is an exact reversible representation.
        pixels = rasterize_4bpp_grid(raw, frame["byte_count"] // 32, 1)
        if serialize_4bpp_grid(pixels, frame["byte_count"] // 32, 1) != raw:
            raise ValueError("sprite frame failed 4bpp round trip")
        oam = result["oam_lists"][frame["oam_offset"]]
        width, height, composed = compose_indexed_frame(raw, oam)
        stem = f"{frame['pixel_offset']:06x}-{frame['oam_offset']:04x}"
        composed_file = composed_dir / f"{stem}.png"
        write_index_png(composed_file, width, height, composed)
        if read_index_png(composed_file) != (width, height, composed):
            raise ValueError("composed sprite PNG differs from its OAM pixels")
        try:
            if decompose_indexed_frame(composed, width, height, oam) != raw:
                raise ValueError("composed sprite does not recover its source tiles")
        except ValueError as error:
            if "overlapping OAM objects" not in str(error):
                raise
            frame["input_kind"] = "object-layers-png"
            frame["layers"] = []
            for object_index, obj in enumerate(oam["objects"]):
                first = obj["tile_index"] * 32
                object_raw = raw[first:first + obj["tile_count"] * 32]
                object_pixels = rasterize_4bpp_grid(
                    object_raw, obj["width"] // 8, obj["height"] // 8)
                layer_file = layer_dir / stem / f"object-{object_index:02d}.png"
                layer_file.parent.mkdir(parents=True, exist_ok=True)
                write_index_png(layer_file, obj["width"], obj["height"], object_pixels)
                if read_index_png(layer_file) != (obj["width"], obj["height"], object_pixels):
                    raise ValueError("sprite object layer PNG differs")
                frame["layers"].append({"object_index": object_index,
                                        "file": str(layer_file.relative_to(output)),
                                        "source_sha256": sha256(layer_file.read_bytes())})
        frame["composed_width"] = width
        frame["composed_height"] = height
        frame["composed_indexed_sha256"] = sha256(composed)

    item_resource_ids = sorted({u16(rom, ITEM_TABLE + index * 32 + 14)
                                for index in range(1, ITEM_COUNT)})
    item_previews = []
    for resource_id in item_resource_ids:
        block = result["resource_entries"][resource_id]
        descriptor = u32(rom, block) - ROM_BASE
        count = u32(rom, descriptor)
        for index in range(count):
            position = descriptor + 4 + index * 20
            offset, oam_offset = u32(rom, position), u32(rom, position + 4)
            if offset in (0xffff, 0xffffffff) or oam_offset == 0xffffffff:
                continue
            oam = result["oam_lists"][oam_offset]
            if len(oam["objects"]) != 1 or oam["tile_count"] != 4:
                continue
            raw = rom[PIXEL_BASE + offset:PIXEL_BASE + offset + 128]
            pixels = rasterize_4bpp_grid(raw, 2, 2)
            write_index_png(preview_dir / f"item-resource-{resource_id:03d}.png", 16, 16, pixels)
            item_previews.append({"resource_id": resource_id, "frame_record_offset": position,
                                  "pixel_offset": offset, "oam_offset": oam_offset})
            break

    manifest = {
        "reference_sha256": ROM_SHA256,
        "resource_table": {"start": TABLE, "end": TABLE + 4 * TABLE_COUNT,
                           "entries": result["resource_entries"],
                           "source_sha256": sha256(rom[TABLE:TABLE + 4 * TABLE_COUNT])},
        "pointer_block_region": {"start": result["block_starts"][0], "end": TABLE,
                                 "block_count": len(result["block_starts"]),
                                 "pointer_groups": result["pointer_groups"],
                                 "nonzero_slots": result["nonzero_pointer_slots"],
                                 "slots": result["pointer_slots"],
                                 "source_sha256": sha256(rom[result["block_starts"][0]:TABLE])},
        "pixel_bank": {"start": PIXEL_BASE, "end": OAM_BASE,
                       "bytes": PIXEL_BYTES,
                       "source_sha256": sha256(rom[PIXEL_BASE:OAM_BASE])},
        "oam_bank": {"start": OAM_BASE, "end": DESCRIPTOR_BASE,
                     "source_sha256": sha256(rom[OAM_BASE:DESCRIPTOR_BASE])},
        "descriptor_bank": result["descriptor_bank"],
        "descriptors": result["descriptors"],
        "oam_lists": list(result["oam_lists"].values()),
        "frame_references": result["frame_references"],
        "unique_frames": result["frames"],
        "frame_input_format": "composed-indexed-png",
        "composed_indexed_previews": len(result["frames"]),
        "control_frame_count": result["control_frames"],
        "item_resource_ids": item_resource_ids,
        "item_previews": item_previews,
        "caveat": "Indexed 4bpp and static OAM only; palette colors and animation timing are unresolved.",
    }
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def frame_source_files(manifest, input_dir):
    source_format = manifest.get("frame_input_format")
    if source_format not in (None, "indexed-tile-grid-png", "composed-indexed-png"):
        raise ValueError("unsupported sprite frame input format")
    for frame in manifest["unique_frames"]:
        stem = f"{frame['pixel_offset']:06x}-{frame['oam_offset']:04x}"
        if frame.get("input_kind") == "rgba-composed-png":
            yield input_dir / frame["image_file"]
        elif frame.get("input_kind") == "object-layers-png":
            yield input_dir / frame["layers"][0]["file"]
        elif frame.get("input_kind") is not None:
            raise ValueError("unsupported sprite frame override")
        elif source_format == "composed-indexed-png":
            yield input_dir / "composed-indexed-frames" / f"{stem}.png"
        elif source_format == "indexed-tile-grid-png":
            yield input_dir / "indexed-tile-grids" / f"{stem}.png"
        else:
            yield input_dir / "frames" / f"{stem}.4bpp"


def frame_palette_source_files(manifest, input_dir):
    for frame in manifest["unique_frames"]:
        if frame.get("input_kind") == "rgba-composed-png":
            yield input_dir / frame["palette_file"]


def frame_index_source_files(manifest, input_dir):
    for frame in manifest["unique_frames"]:
        if frame.get("input_kind") == "rgba-composed-png":
            stem = f"{frame['pixel_offset']:06x}-{frame['oam_offset']:04x}"
            yield input_dir / "composed-indexed-frames" / f"{stem}.png"


def frame_preview_files(manifest, input_dir):
    for frame in manifest["unique_frames"]:
        if frame.get("input_kind") == "object-layers-png":
            stem = f"{frame['pixel_offset']:06x}-{frame['oam_offset']:04x}"
            yield input_dir / "composed-indexed-frames" / f"{stem}.png"


def frame_layer_source_files(manifest, input_dir):
    for frame in manifest["unique_frames"]:
        if frame.get("input_kind") == "object-layers-png":
            for layer in frame["layers"]:
                yield input_dir / layer["file"]


def reconstruct_pointer_table(manifest):
    """Re-encode the contiguous pointer blocks and their resource index."""
    region = manifest["pointer_block_region"]
    table = manifest["resource_table"]
    if (region["start"], region["end"], table["start"], table["end"]) != (
            0x36DAA4, TABLE, TABLE, TABLE + 4 * TABLE_COUNT):
        raise ValueError("sprite pointer boundaries differ from retail")
    slots = region["slots"]
    if (len(slots) != region["pointer_groups"] * 6 or
            len(slots) * 4 != region["end"] - region["start"] or
            sum(bool(slot) for slot in slots) != region["nonzero_slots"] or
            len(table["entries"]) != TABLE_COUNT):
        raise ValueError("sprite pointer counts differ from retail")
    valid_starts = set(range(region["start"], region["end"], 24))
    if any(entry not in valid_starts for entry in table["entries"]):
        raise ValueError("sprite resource entry does not select a pointer group")
    if any(slot and not DESCRIPTOR_BASE <= slot < 0x1000000 for slot in slots):
        raise ValueError("sprite pointer slot leaves the descriptor region")
    blocks = b"".join((ROM_BASE + slot if slot else 0).to_bytes(4, "little")
                      for slot in slots)
    entries = b"".join((ROM_BASE + entry).to_bytes(4, "little")
                       for entry in table["entries"])
    if (sha256(blocks) != region["source_sha256"] or
            sha256(entries) != table["source_sha256"]):
        raise ValueError("sprite pointer table does not match retail")
    return blocks + entries


def reconstruct_oam_lists(manifest):
    """Re-encode the contiguous static sprite-object lists from OBJ attributes."""
    bank = manifest["oam_bank"]
    if (bank["start"], bank["end"]) != (OAM_BASE, DESCRIPTOR_BASE):
        raise ValueError("sprite OAM boundaries differ from retail")
    encoded = bytearray()
    for entry in manifest["oam_lists"]:
        if entry["source_start"] != OAM_BASE + len(encoded) or \
                entry["relative_offset"] != len(encoded):
            raise ValueError("sprite OAM lists are not contiguous")
        objects = entry["objects"]
        data = len(objects).to_bytes(2, "little")
        for obj in objects:
            for field in ("attr0", "attr1", "attr2"):
                value = obj[field]
                if not 0 <= value <= 0xffff:
                    raise ValueError("sprite OAM attribute is not a halfword")
                data += value.to_bytes(2, "little")
        if (entry["source_end"] != entry["source_start"] + len(data) or
                sha256(data) != entry["source_sha256"]):
            raise ValueError("sprite OAM list does not match retail")
        encoded.extend(data)
    if len(encoded) != DESCRIPTOR_BASE - OAM_BASE - 4 or \
            sha256(encoded + bytes(4)) != bank["source_sha256"]:
        raise ValueError("sprite OAM bank does not match retail")
    return bytes(encoded)


def reconstruct_descriptor_bank(manifest):
    """Re-encode frame records while retaining their observed zero alignment."""
    bank = manifest["descriptor_bank"]
    if (bank["start"], bank["end"], bank["alignment_bytes"]) != (
            DESCRIPTOR_BASE, DESCRIPTOR_END, 37036):
        raise ValueError("sprite descriptor boundaries or padding differ from retail")
    output = bytearray(DESCRIPTOR_END - DESCRIPTOR_BASE)
    cursor = DESCRIPTOR_BASE
    record_bytes = 0
    alignment_bytes = 0
    for descriptor in manifest["descriptors"]:
        start = descriptor["source_start"]
        records = descriptor["records"]
        if start < cursor or len(records) != descriptor["frame_count"]:
            raise ValueError("sprite descriptor order or frame count is invalid")
        alignment_bytes += start - cursor
        data = len(records).to_bytes(4, "little")
        for record in records:
            for field in ("pixel_offset", "oam_offset"):
                value = record[field]
                if not 0 <= value <= 0xffffffff:
                    raise ValueError("sprite descriptor offset is not a word")
                data += value.to_bytes(4, "little")
            for field in ("field_08", "kind_09"):
                value = record[field]
                if not 0 <= value <= 0xff:
                    raise ValueError("sprite descriptor field is not a byte")
                data += value.to_bytes(1, "little")
            for field in ("field_0a", "field_0c", "field_0e", "field_10", "field_12"):
                value = record[field]
                if not 0 <= value <= 0xffff:
                    raise ValueError("sprite descriptor field is not a halfword")
                data += value.to_bytes(2, "little")
        if (descriptor["source_end"] != start + len(data) or
                sha256(data) != descriptor["source_sha256"]):
            raise ValueError("sprite descriptor does not match retail")
        output[start - DESCRIPTOR_BASE:start - DESCRIPTOR_BASE + len(data)] = data
        record_bytes += len(data)
        cursor = descriptor["source_end"]
    if (cursor != DESCRIPTOR_END or record_bytes != bank["record_bytes"] or
            alignment_bytes != bank["alignment_bytes"] or
            sha256(output) != bank["source_sha256"]):
        raise ValueError("sprite descriptor bank does not match retail")
    return bytes(output)


def reconstruct_pixel_bank(manifest, input_dir, verify_retail=True):
    """Encode sprite images; optionally require every byte to match retail evidence."""
    pixel_bank = manifest["pixel_bank"]
    if (pixel_bank["start"], pixel_bank["end"], pixel_bank["bytes"]) != (
            PIXEL_BASE, OAM_BASE, PIXEL_BYTES):
        raise ValueError("exported sprite bank boundaries do not match retail")
    if manifest.get("frame_input_format") not in (
            None, "indexed-tile-grid-png", "composed-indexed-png"):
        raise ValueError("unsupported sprite frame input format")
    bank = bytearray(manifest["pixel_bank"]["bytes"])
    covered = bytearray(len(bank))
    oam_by_offset = {entry["relative_offset"]: entry for entry in manifest["oam_lists"]}
    for frame, source in zip(manifest["unique_frames"], frame_source_files(manifest, input_dir)):
        offset, length = frame["pixel_offset"], frame["byte_count"]
        oam = oam_by_offset[frame["oam_offset"]]
        if not source.resolve().is_relative_to(input_dir.resolve()):
            raise ValueError("sprite image path escapes asset directory")
        if frame.get("input_kind") == "rgba-composed-png":
            palette_path = (input_dir / frame["palette_file"]).resolve()
            if not palette_path.is_relative_to(input_dir.resolve()):
                raise ValueError("sprite palette path escapes asset directory")
            palette = palette_path.read_bytes()
            if sha256(palette) != frame["palette_source_sha256"]:
                raise ValueError(f"frame {offset:#x} selected palette differs")
            if verify_retail and sha256(source.read_bytes()) != frame["rgba_source_sha256"]:
                raise ValueError(f"frame {offset:#x} colored PNG differs")
            width, height, rgba = read_rgba_png(source)
            hint_path = (input_dir / "composed-indexed-frames" /
                         f"{offset:06x}-{frame['oam_offset']:04x}.png").resolve()
            if not hint_path.is_relative_to(input_dir.resolve()):
                raise ValueError("sprite index plane escapes asset directory")
            hint_width, hint_height, hint = read_index_png(hint_path)
            if (hint_width, hint_height) != (width, height):
                raise ValueError("sprite index plane dimensions differ")
            pixels = rgba_to_indices(rgba, palette, hint)
            raw = decompose_indexed_frame(pixels, width, height, oam)
        elif frame.get("input_kind") == "object-layers-png":
            if len(frame["layers"]) != len(oam["objects"]):
                raise ValueError("sprite object layer count differs")
            raw_buffer = bytearray(length)
            for object_index, obj in enumerate(oam["objects"]):
                layer = frame["layers"][object_index]
                if layer["object_index"] != object_index:
                    raise ValueError("sprite object layer order differs")
                layer_path = (input_dir / layer["file"]).resolve()
                if not layer_path.is_relative_to(input_dir.resolve()):
                    raise ValueError("sprite object layer escapes asset directory")
                if verify_retail and sha256(layer_path.read_bytes()) != layer["source_sha256"]:
                    raise ValueError("sprite object layer source differs")
                object_width, object_height, object_pixels = read_index_png(layer_path)
                if (object_width, object_height) != (obj["width"], obj["height"]):
                    raise ValueError("sprite object layer dimensions differ")
                object_raw = serialize_4bpp_grid(
                    object_pixels, obj["width"] // 8, obj["height"] // 8)
                first = obj["tile_index"] * 32
                raw_buffer[first:first + len(object_raw)] = object_raw
            raw = bytes(raw_buffer)
            # The composed PNG is derived; edit mode uses layers alone.
            if verify_retail:
                preview = (input_dir / "composed-indexed-frames" /
                           f"{offset:06x}-{frame['oam_offset']:04x}.png").resolve()
                if not preview.is_relative_to(input_dir.resolve()):
                    raise ValueError("sprite preview escapes asset directory")
                if compose_indexed_frame(raw, oam) != read_index_png(preview):
                    raise ValueError("sprite object layers differ from derived preview")
        elif manifest.get("frame_input_format") == "composed-indexed-png":
            width, height, pixels = read_index_png(source)
            raw = decompose_indexed_frame(pixels, width, height, oam)
        elif manifest.get("frame_input_format") == "indexed-tile-grid-png":
            columns, rows = frame["grid_tiles_x"], frame["grid_tiles_y"]
            width, height, pixels = read_index_png(source)
            if (width, height) != (columns * 8, rows * 8):
                raise ValueError(f"frame {offset:#x} indexed PNG dimensions differ")
            raw = serialize_4bpp_grid(pixels, columns, rows)
        else:
            raw = source.read_bytes()
        if len(raw) != length or (verify_retail and sha256(raw) != frame["source_sha256"]):
            raise ValueError(f"frame {offset:#x} changed or has the wrong length")
        width, height, pixels = compose_indexed_frame(raw, oam)
        if (width, height) != (
                frame["composed_width"], frame["composed_height"]):
            raise ValueError(f"composed frame {offset:#x} dimensions differ")
        if verify_retail and (width, height, sha256(pixels)) != (
                frame["composed_width"], frame["composed_height"],
                frame["composed_indexed_sha256"]):
            raise ValueError(f"composed frame {offset:#x} differs from its exported pixels")
        for position, value in enumerate(raw, offset):
            if covered[position] and bank[position] != value:
                raise ValueError(f"overlapping frames disagree at bank offset {position:#x}")
            bank[position] = value
            covered[position] = 1
    if not all(covered) or (verify_retail and
                            sha256(bank) != manifest["pixel_bank"]["source_sha256"]):
        raise ValueError("exported frames do not reconstruct the retail sprite bank")
    return bytes(bank)


def verify_export(manifest, input_dir, output):
    bank = reconstruct_pixel_bank(manifest, input_dir)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(bank)
    return {"rebuilt_bytes": len(bank), "sha256": sha256(bank),
            "unique_frames": len(manifest["unique_frames"]),
            "covered_bytes": len(bank)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--output-dir", type=Path)
    parser.add_argument("--verify-dir", type=Path)
    parser.add_argument("--rebuilt-bank", type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    if args.verify_dir:
        if args.rom or args.output_dir or not args.rebuilt_bank:
            parser.error("--verify-dir requires --rebuilt-bank and excludes --rom/--output-dir")
        output = args.rebuilt_bank.resolve()
        if output.is_relative_to(root):
            raise SystemExit("Rebuilt sprite bank must be outside the source tree")
        manifest = json.loads((args.verify_dir / "manifest.json").read_text())
        print(json.dumps(verify_export(manifest, args.verify_dir, output)))
        return
    if not args.rom or not args.output_dir or args.rebuilt_bank:
        parser.error("extraction requires --rom and --output-dir")
    output = args.output_dir.resolve()
    if output.is_relative_to(root):
        raise SystemExit("Sprite extraction output must be outside the source tree")
    rom = args.rom.read_bytes()
    if sha256(rom) != ROM_SHA256:
        raise SystemExit("Input is not the pinned US retail ROM")
    result = parse_sprite_bank(rom)
    manifest = export(rom, result, output)
    print(json.dumps({"pointer_groups": result["pointer_groups"],
                      "descriptors": len(result["descriptors"]),
                      "draw_frame_references": len(result["frame_references"]),
                      "unique_frames": len(result["frames"]),
                      "pixel_bank_bytes": PIXEL_BYTES,
                      "item_previews": len(manifest["item_previews"])}))


if __name__ == "__main__":
    main()
