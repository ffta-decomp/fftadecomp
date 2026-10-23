#!/usr/bin/env python3
"""Extract FFTA map graphics and animation tiles from the retail ROM.

The map table is a ROM-relative table.  Its graphics fields use wrappers
0x20/0x22 around a custom LZSS stream; this is distinct from BIOS LZ77.  The
tool writes only external decoded assets and a manifest, and validates the
pinned retail revision before reading any offsets.
"""

import argparse
import hashlib
import json
from collections import defaultdict
from bisect import bisect_left
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
MAP_TABLE = 0x08569104 - 0x08000000
MAP_STRIDE = 0x58
MAP_COUNT = 162


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def u32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def decode_lzss(data, offset=0, capture_plan=False):
    """Decode one observed FFTA map-LZSS stream and report bytes consumed."""
    if offset < 0 or offset + 4 > len(data):
        raise ValueError("truncated map-LZSS size")
    output_size = int.from_bytes(data[offset:offset + 4], "big")
    cursor = offset + 4
    output = bytearray()
    plan = [] if capture_plan else None

    def require(count, label):
        if cursor + count > len(data):
            raise ValueError(f"truncated map-LZSS {label}")

    def emit(value, count):
        if count < 0 or len(output) + count > output_size:
            raise ValueError("map-LZSS token exceeds declared output")
        output.extend(bytes((value,)) * count)

    def copy(distance, count):
        if distance <= 0 or distance > len(output):
            raise ValueError("map-LZSS back-reference precedes output")
        if len(output) + count > output_size:
            raise ValueError("map-LZSS back-reference exceeds output")
        for _ in range(count):
            output.append(output[-distance])

    while len(output) < output_size:
        require(1, "token")
        token = data[cursor]
        cursor += 1
        if token & 0x80:
            require(1, "short back-reference")
            distance = ((token & 7) << 8) | data[cursor]
            cursor += 1
            count = ((token >> 3) & 0x0f) + 3
            copy(distance + 1, count)
            if capture_plan:
                plan.append({"kind": "short", "length": count,
                             "distance": distance + 1})
        elif token & 0x40:
            count = (token & 0x3f) + 1
            require(count, "literal run")
            if len(output) + count > output_size:
                raise ValueError("map-LZSS literal exceeds output")
            output.extend(data[cursor:cursor + count])
            cursor += count
            if capture_plan:
                plan.append({"kind": "literal", "length": count})
        elif token & 0x20:
            count = (token & 0x1f) + 2
            emit(0, count)
            if capture_plan:
                plan.append({"kind": "zero-short", "length": count})
        elif token & 0x10:
            require(2, "long back-reference")
            first, second = data[cursor], data[cursor + 1]
            cursor += 2
            distance = ((first & 0x3f) << 8) | second
            count = (((first >> 2) & 0x30) | (token & 0x0f)) + 4
            copy(distance + 1, count)
            if capture_plan:
                plan.append({"kind": "long", "length": count,
                             "distance": distance + 1})
        elif token == 0x01:
            require(1, "0xff run")
            count = data[cursor] + 3
            cursor += 1
            emit(0xff, count)
            if capture_plan:
                plan.append({"kind": "ff", "length": count})
        elif token == 0x02:
            require(1, "extended zero run")
            count = data[cursor] + 3
            cursor += 1
            emit(0, count)
            if capture_plan:
                plan.append({"kind": "zero-extended", "length": count})
        else:
            if token != 0:
                raise ValueError(f"unknown map-LZSS token 0x{token:02x}")
            require(3, "extended back-reference")
            count = data[cursor] + 5
            distance = (data[cursor + 1] << 8) | data[cursor + 2]
            cursor += 3
            copy(distance + 1, count)
            if capture_plan:
                plan.append({"kind": "extended", "length": count,
                             "distance": distance + 1})
    if capture_plan:
        return bytes(output), cursor - offset, plan
    return bytes(output), cursor - offset


def encode_lzss_plan(raw, plan):
    """Apply observed map-LZSS token choices to exported decoded tiles."""
    encoded = bytearray(len(raw).to_bytes(4, "big"))
    position = 0
    for item in plan:
        kind, length = item["kind"], item["length"]
        if not 0 < length <= len(raw) - position:
            raise ValueError("map-LZSS token leaves decoded tiles")
        if kind == "literal":
            if not 1 <= length <= 64:
                raise ValueError("map-LZSS literal length is invalid")
            encoded.append(0x40 | (length - 1))
            encoded.extend(raw[position:position + length])
        elif kind == "zero-short":
            if not 2 <= length <= 33 or any(raw[position:position + length]):
                raise ValueError("map-LZSS short zero run differs from tiles")
            encoded.append(0x20 | (length - 2))
        elif kind in ("zero-extended", "ff"):
            value = 0 if kind == "zero-extended" else 0xff
            if (not 3 <= length <= 258 or
                    raw[position:position + length] != bytes((value,)) * length):
                raise ValueError("map-LZSS extended run differs from tiles")
            encoded.extend((0x02 if value == 0 else 0x01, length - 3))
        elif kind in ("short", "long", "extended"):
            distance = item["distance"]
            if distance <= 0 or distance > position:
                raise ValueError("map-LZSS back-reference precedes decoded tiles")
            value = distance - 1
            if kind == "short":
                if not 3 <= length <= 18 or distance > 0x800:
                    raise ValueError("map-LZSS short back-reference is invalid")
                encoded.extend((0x80 | ((length - 3) << 3) | (value >> 8),
                                value & 0xff))
            elif kind == "long":
                if not 4 <= length <= 67 or distance > 0x4000:
                    raise ValueError("map-LZSS long back-reference is invalid")
                encoded.extend((0x10 | ((length - 4) & 0x0f),
                                ((length - 4) & 0x30) << 2 | (value >> 8),
                                value & 0xff))
            else:
                if not 5 <= length <= 260 or distance > 0x10000:
                    raise ValueError("map-LZSS extended back-reference is invalid")
                encoded.extend((0, length - 5, value >> 8, value & 0xff))
        else:
            raise ValueError("unknown map-LZSS token kind")
        position += length
    if position != len(raw):
        raise ValueError("map-LZSS token plan does not cover decoded tiles")
    decoded, consumed = decode_lzss(encoded)
    if decoded != raw or consumed != len(encoded):
        raise ValueError("map-LZSS token plan does not round-trip")
    return bytes(encoded)


def decode_graphics(rom, map_id):
    record = MAP_TABLE + map_id * MAP_STRIDE
    wrapper = MAP_TABLE + u32(rom, record)
    kind = rom[wrapper]
    if kind not in (0x20, 0x22):
        raise ValueError(f"map {map_id} graphics wrapper is 0x{kind:02x}")
    stream = wrapper + (8 if kind == 0x22 else 4)
    raw, consumed = decode_lzss(rom, stream)
    if len(raw) % 32:
        raise ValueError(f"map {map_id} graphics is not whole 4bpp tiles")
    declared_size = int.from_bytes(rom[stream - 3:stream], "little")
    if declared_size != len(raw):
        raise ValueError(f"map {map_id} graphics wrapper size differs from tiles")
    return {
        "map": map_id, "wrapper_offset": wrapper, "wrapper_type": kind,
        "wrapper_field_01": int.from_bytes(rom[wrapper + 1:wrapper + 4], "little"),
        "wrapper_decoded_bytes": declared_size,
        "wrapper_sha256": sha256(rom[wrapper:stream]),
        "stream_offset": stream, "compressed_bytes": consumed,
        "decoded_bytes": len(raw), "tile_count": len(raw) // 32,
        "sha256": sha256(raw), "raw": raw,
    }


def decode_animations(rom, map_id):
    record = MAP_TABLE + map_id * MAP_STRIDE
    metadata_delta = u32(rom, record + 0x14)
    if metadata_delta == 0:
        return None
    metadata = MAP_TABLE + metadata_delta
    tiles = MAP_TABLE + u32(rom, record + 0x18)
    byte_count = u16(rom, metadata)
    frame_count = u16(rom, metadata + 2)
    if tiles != metadata + 4 + frame_count * 4:
        raise ValueError(f"map {map_id} animation tile pointer is not contiguous")
    if byte_count == 0 or byte_count % 32:
        raise ValueError(f"map {map_id} animation is not whole 4bpp tiles")
    frames = []
    for frame in range(frame_count):
        entry = metadata + 4 + frame * 4
        duration = u16(rom, entry)
        source_tile = u16(rom, entry + 2)
        start = tiles + source_tile * 32
        raw = bytes(rom[start:start + byte_count])
        if len(raw) != byte_count:
            raise ValueError(f"map {map_id} animation frame exceeds ROM")
        frames.append({"frame": frame, "duration": duration,
                       "source_tile": source_tile, "sha256": sha256(raw),
                       "decoded_bytes": len(raw), "raw": raw})
    return {"map": map_id, "metadata_offset": metadata,
            "tiles_offset": tiles, "vram_destination": u32(rom, record + 0x1c),
            "byte_count": byte_count, "frame_count": frame_count,
            "metadata_sha256": sha256(rom[metadata:tiles]),
            "frames": frames}


def encode_lzss(raw):
    """Encode the observed token grammar with a bounded minimum-cost search."""
    size = len(raw)
    history = defaultdict(list)
    matches = [None] * size
    for position in range(size):
        short_len = long_len = extended_len = 0
        short_distance = long_distance = extended_distance = 0
        if position + 3 <= size:
            key = raw[position:position + 3]
            before = bisect_left(history[key], position)
            for prior in reversed(history[key][max(0, before - 512):before]):
                distance = position - prior
                if distance > 0x10000:
                    break
                length = 3
                limit = min(260, size - position)
                while length < limit and raw[prior + length] == raw[position + length]:
                    length += 1
                if distance <= 0x800 and min(length, 18) > short_len:
                    short_len, short_distance = min(length, 18), distance
                if distance <= 0x4000 and min(length, 67) > long_len:
                    long_len, long_distance = min(length, 67), distance
                if length > extended_len:
                    extended_len, extended_distance = length, distance
                if short_len == 18 and long_len == 67 and extended_len == 260:
                    break
            history[key].append(position)
        zero_run = ff_run = 0
        if raw[position] == 0:
            while position + zero_run < size and zero_run < 258 and raw[position + zero_run] == 0:
                zero_run += 1
        elif raw[position] == 0xff:
            while position + ff_run < size and ff_run < 258 and raw[position + ff_run] == 0xff:
                ff_run += 1
        matches[position] = (short_len, short_distance, long_len, long_distance,
                             extended_len, extended_distance, zero_run, ff_run)

    costs = [10 ** 9] * (size + 1)
    choices = [None] * size
    costs[size] = 0
    for position in range(size - 1, -1, -1):
        short_len, short_distance, long_len, long_distance, extended_len, \
            extended_distance, zero_run, ff_run = matches[position]
        options = [("literal", 1, min(64, size - position), 0, 1, 0),
                   ("zero-short", 2, min(zero_run, 33), 0, 1, 0),
                   ("zero-extended", 3, zero_run, 0, 2, 0),
                   ("ff", 3, ff_run, 0, 2, 0),
                   ("short", 3, short_len, short_distance, 2, 0),
                   ("long", 4, long_len, long_distance, 3, 0),
                   ("extended", 5, extended_len, extended_distance, 4, 0)]
        for kind, first, last, distance, overhead, _ in options:
            for length in range(first, last + 1):
                extra = length if kind == "literal" else 0
                total = overhead + extra + costs[position + length]
                if total < costs[position]:
                    costs[position] = total
                    choices[position] = (kind, length, distance)

    encoded = bytearray(size.to_bytes(4, "big"))
    position = 0
    while position < size:
        kind, length, distance = choices[position]
        if kind == "literal":
            encoded.append(0x40 + length - 1)
            encoded.extend(raw[position:position + length])
        elif kind == "zero-short":
            encoded.append(0x20 + length - 2)
        elif kind == "zero-extended":
            encoded.extend((0x02, length - 3))
        elif kind == "ff":
            encoded.extend((0x01, length - 3))
        elif kind == "short":
            value = distance - 1
            encoded.extend((0x80 | ((length - 3) << 3) | ((value >> 8) & 7),
                            value & 0xff))
        elif kind == "long":
            value = distance - 1
            encoded.extend((0x10 | ((length - 4) & 0x0f),
                            ((value >> 8) & 0x3f) | (((length - 4) & 0x30) << 2),
                            value & 0xff))
        else:
            value = distance - 1
            encoded.extend((0, length - 5, (value >> 8) & 0xff, value & 0xff))
        position += length
    return bytes(encoded)


def map_graphics_entry(manifest, stream_offset):
    matches = [item for item in manifest["graphics_unique"]
               if item["stream_offset"] == stream_offset]
    if len(matches) != 1:
        raise ValueError(f"map graphics stream {stream_offset:#x} is not unique")
    return matches[0]


def map_graphics_wrapper_entry(manifest, wrapper_offset):
    matches = [item for item in manifest["graphics_unique"]
               if item["wrapper_offset"] == wrapper_offset]
    if len(matches) != 1:
        raise ValueError(f"map graphics wrapper {wrapper_offset:#x} is not unique")
    return matches[0]


def reconstruct_map_graphics_wrapper(manifest, wrapper_offset):
    """Rebuild one type/size wrapper without copying its original bytes."""
    item = map_graphics_wrapper_entry(manifest, wrapper_offset)
    kind = item["wrapper_type"]
    if kind not in (0x20, 0x22) or item["wrapper_decoded_bytes"] != item["decoded_bytes"]:
        raise ValueError("map graphics wrapper type or decoded size differs")
    field = item["wrapper_field_01"]
    if not 0 <= field < 1 << 24 or not 0 <= item["decoded_bytes"] < 1 << 24:
        raise ValueError("map graphics wrapper field exceeds 24 bits")
    encoded = bytes((kind,)) + field.to_bytes(3, "little")
    if kind == 0x22:
        encoded += bytes((0x20,)) + item["decoded_bytes"].to_bytes(3, "little")
    elif field != item["decoded_bytes"]:
        raise ValueError("type-0x20 wrapper size differs from decoded tiles")
    if (wrapper_offset + len(encoded) != item["stream_offset"] or
            sha256(encoded) != item["wrapper_sha256"]):
        raise ValueError("map graphics wrapper does not match retail")
    return encoded


def map_animation_entry(manifest, metadata_offset):
    matches = [item for item in manifest["animations"]
               if item and item["metadata_offset"] == metadata_offset]
    if not matches:
        raise ValueError(f"map animation metadata {metadata_offset:#x} is absent")
    fields = ("tiles_offset", "byte_count", "frame_count", "metadata_sha256")
    if any(any(item[field] != matches[0][field] for field in fields)
           for item in matches[1:]):
        raise ValueError("shared map animation metadata is inconsistent")
    frame_fields = ("frame", "duration", "source_tile", "sha256", "decoded_bytes")
    if any([[frame[field] for field in frame_fields] for frame in item["frames"]] !=
           [[frame[field] for field in frame_fields] for frame in matches[0]["frames"]]
           for item in matches[1:]):
        raise ValueError("shared map animation frames are inconsistent")
    return matches[0]


def reconstruct_map_animation_metadata(manifest, metadata_offset):
    """Rebuild a map animation frame table from its decoded fields."""
    item = map_animation_entry(manifest, metadata_offset)
    frames = item["frames"]
    if (len(frames) != item["frame_count"] or
            item["tiles_offset"] != metadata_offset + 4 + 4 * len(frames) or
            not 0 < item["byte_count"] <= 0xffff or item["byte_count"] % 32):
        raise ValueError("map animation metadata boundaries differ")
    encoded = bytearray(item["byte_count"].to_bytes(2, "little"))
    encoded.extend(len(frames).to_bytes(2, "little"))
    for index, frame in enumerate(frames):
        if (frame["frame"] != index or not 0 <= frame["duration"] <= 0xffff or
                not 0 <= frame["source_tile"] <= 0xffff):
            raise ValueError("map animation frame metadata differs")
        encoded.extend(frame["duration"].to_bytes(2, "little"))
        encoded.extend(frame["source_tile"].to_bytes(2, "little"))
    if sha256(encoded) != item["metadata_sha256"]:
        raise ValueError("map animation metadata does not match retail")
    return bytes(encoded)


def reconstruct_map_animation_tiles(manifest, source_dir, tiles_offset):
    """Assemble one contiguous animation tile bank from exported 4bpp frames."""
    matches = [item for item in manifest["animations"]
               if item and item["tiles_offset"] == tiles_offset]
    if not matches:
        raise ValueError(f"map animation tiles {tiles_offset:#x} are absent")
    item = map_animation_entry(manifest, matches[0]["metadata_offset"])
    frames = item["frames"]
    end = max(frame["source_tile"] * 32 + item["byte_count"] for frame in frames)
    output = bytearray(end)
    covered = bytearray(end)
    for frame in frames:
        file_name = frame.get("file")
        if file_name != f"animation-0x{item['metadata_offset']:06x}-frame-{frame['frame']:02d}.4bpp":
            raise ValueError("map animation frame filename differs from metadata")
        raw = (source_dir / "animations" / file_name).read_bytes()
        if len(raw) != item["byte_count"] or sha256(raw) != frame["sha256"]:
            raise ValueError("map animation frame differs from exported tiles")
        start = frame["source_tile"] * 32
        if any(covered[start:start + len(raw)]):
            raise ValueError("map animation frames overlap")
        output[start:start + len(raw)] = raw
        covered[start:start + len(raw)] = b"\x01" * len(raw)
    if not all(covered) or len(output) != item["tile_bank_bytes"] or \
            sha256(output) != item["tile_bank_sha256"]:
        raise ValueError("map animation tile bank has gaps or differs from retail")
    return bytes(output)


def reconstruct_map_graphics_stream(manifest, source_dir, stream_offset):
    """Rebuild one retail compressed stream from exported tiles and token plan."""
    item = map_graphics_entry(manifest, stream_offset)
    file_name = item["file"]
    if file_name != f"graphics-0x{stream_offset:06x}.4bpp":
        raise ValueError("map graphics filename differs from stream offset")
    raw = (source_dir / "graphics" / file_name).read_bytes()
    if len(raw) != item["decoded_bytes"] or sha256(raw) != item["sha256"]:
        raise ValueError(f"map graphics decoded tiles differ at {stream_offset:#x}")
    encoded = encode_lzss_plan(raw, item["token_plan"])
    if (len(encoded) != item["compressed_bytes"] or
            sha256(encoded) != item["retail_stream_sha256"]):
        raise ValueError(f"map graphics stream differs from retail at {stream_offset:#x}")
    return encoded


def export(rom, output):
    output = output.resolve()
    root = Path(__file__).resolve().parents[1]
    if output.is_relative_to(root):
        raise ValueError("map graphics output must be outside the source tree")
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    graphics_dir = output / "graphics"
    animation_dir = output / "animations"
    graphics_dir.mkdir(parents=True, exist_ok=True)
    animation_dir.mkdir(parents=True, exist_ok=True)

    graphics = [decode_graphics(rom, map_id) for map_id in range(MAP_COUNT)]
    unique_graphics = {}
    for item in graphics:
        unique_graphics.setdefault(item["stream_offset"], item)
    for item in unique_graphics.values():
        item["file"] = f"graphics-0x{item['stream_offset']:06x}.4bpp"
        (graphics_dir / item["file"]).write_bytes(item["raw"])
        decoded, consumed, token_plan = decode_lzss(
            rom, item["stream_offset"], capture_plan=True)
        if decoded != item["raw"] or consumed != item["compressed_bytes"]:
            raise ValueError("map graphics token plan differs from decoded tiles")
        item["token_plan"] = token_plan
        item["exact_plan_match"] = (encode_lzss_plan(item["raw"], token_plan) ==
                                     rom[item["stream_offset"]:
                                         item["stream_offset"] + item["compressed_bytes"]])
        if not item["exact_plan_match"]:
            raise ValueError("map graphics token plan does not rebuild retail bytes")
        rebuilt = encode_lzss(item["raw"])
        item["retail_stream_sha256"] = sha256(rom[item["stream_offset"]:
                                                    item["stream_offset"] + item["compressed_bytes"]])
        item["reencoded_bytes"] = len(rebuilt)
        item["reencoded_sha256"] = sha256(rebuilt)
        item["exact_encoded_match"] = rebuilt == rom[item["stream_offset"]:
                                                     item["stream_offset"] + item["compressed_bytes"]]
        item["fits_retail_allocation"] = len(rebuilt) <= item["compressed_bytes"]

    animations = [decode_animations(rom, map_id) for map_id in range(MAP_COUNT)]
    unique_animations = {}
    for item in animations:
        if item is not None:
            unique_animations.setdefault(item["metadata_offset"], item)
    for item in unique_animations.values():
        bank_end = max(frame["source_tile"] * 32 + item["byte_count"]
                       for frame in item["frames"])
        item["tile_bank_bytes"] = bank_end
        item["tile_bank_sha256"] = sha256(rom[item["tiles_offset"]:
                                              item["tiles_offset"] + bank_end])
    for item in animations:
        if item is not None:
            original = unique_animations[item["metadata_offset"]]
            item["tile_bank_bytes"] = original["tile_bank_bytes"]
            item["tile_bank_sha256"] = original["tile_bank_sha256"]
    unique_animation_frames = {}
    for item in animations:
        if item is None:
            continue
        for frame in item["frames"]:
            key = (item["metadata_offset"], frame["frame"])
            unique_animation_frames.setdefault(key, (item, frame))
    for (metadata, frame_no), (item, frame) in unique_animation_frames.items():
        frame["file"] = f"animation-0x{metadata:06x}-frame-{frame_no:02d}.4bpp"
        (animation_dir / frame["file"]).write_bytes(frame["raw"])

    report = {
        "reference_sha256": ROM_SHA256,
        "map_table_rom_offset": MAP_TABLE,
        "map_stride": MAP_STRIDE, "map_count": MAP_COUNT,
        "graphics_map_count": len(graphics),
        "graphics_unique_streams": len(unique_graphics),
        "graphics_wrapper_types": {
            f"0x{kind:02x}": sum(item["wrapper_type"] == kind for item in graphics)
            for kind in (0x20, 0x22)},
        "graphics_decoded_bytes": sum(item["decoded_bytes"] for item in unique_graphics.values()),
        "graphics_exact_encoded_matches": sum(item["exact_encoded_match"] for item in unique_graphics.values()),
        "graphics_exact_plan_matches": sum(item["exact_plan_match"] for item in unique_graphics.values()),
        "graphics_reencoded_fits": sum(item["fits_retail_allocation"] for item in unique_graphics.values()),
        "graphics_streams": [{k: v for k, v in item.items() if k != "raw"}
                             for item in graphics],
        "graphics_unique": [{k: v for k, v in item.items() if k != "raw"}
                            for item in unique_graphics.values()],
        "animation_map_count": sum(item is not None for item in animations),
        "animation_unique_frame_files": len(unique_animation_frames),
        "animations": [{**{k: v for k, v in item.items() if k != "frames"},
                        "frames": [{k: v for k, v in frame.items() if k != "raw"}
                                   for frame in item["frames"]]} if item else None
                       for item in animations],
        "animation_frames": [{k: v for k, v in frame.items() if k != "raw"}
                             for _, frame in unique_animation_frames.values()],
        "caveat": "Decoded graphics and animation frames are indexed 4bpp tile streams. They are not reconstructed bitmaps; rendering still requires map arrangement, palette, tilemap, VRAM, and OAM consumers.",
    }
    (output / "manifest.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    report = export(args.rom.read_bytes(), args.output_dir)
    print(json.dumps({key: report[key] for key in (
        "graphics_map_count", "graphics_unique_streams", "graphics_decoded_bytes",
        "animation_map_count", "animation_unique_frame_files")}))


if __name__ == "__main__":
    main()
