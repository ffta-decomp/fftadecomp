#!/usr/bin/env python3
"""Extract and classify strict GBA type-0x10 resource candidates.

The extractor keeps the encoded ROM span and decoded payload separate.  It
does not claim that every valid stream is a live game asset; the report is a
repeatable resource inventory for later pointer and runtime validation.
"""

import argparse
import hashlib
import json
import math
import struct
from bisect import bisect_right
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
MAX_DECODED = 0x100000
ROOT = Path(__file__).resolve().parents[1]


def overlaps_selected(start, end, ranges):
    starts = [item[0] for item in ranges]
    index = bisect_right(starts, start) - 1
    if index >= 0 and ranges[index][1] > start:
        return True
    return index + 1 < len(ranges) and ranges[index + 1][0] < end


def digest(data):
    return hashlib.sha256(data).hexdigest()


def decode_lz77(data, start):
    if start + 4 > len(data) or data[start] != 0x10:
        return None
    expected = int.from_bytes(data[start + 1:start + 4], "little")
    if not 32 <= expected <= MAX_DECODED:
        return None
    cursor = start + 4
    output = bytearray()
    while len(output) < expected:
        if cursor >= len(data):
            return None
        flags = data[cursor]
        cursor += 1
        for bit in range(7, -1, -1):
            if len(output) == expected:
                break
            if flags & (1 << bit):
                if cursor + 2 > len(data):
                    return None
                first, second = data[cursor], data[cursor + 1]
                cursor += 2
                length = (first >> 4) + 3
                distance = (((first & 15) << 8) | second) + 1
                if distance > len(output) or len(output) + length > expected:
                    return None
                for _ in range(length):
                    output.append(output[-distance])
            else:
                if cursor >= len(data):
                    return None
                output.append(data[cursor])
                cursor += 1
    return cursor, bytes(output)


def tile_score(payload):
    """Score likely 4bpp tile data without asserting a graphics format."""
    if len(payload) < 32 or len(payload) % 32:
        return {"tile_count": 0, "tile_score": 0.0, "zero_tile_fraction": None}
    tiles = [payload[i:i + 32] for i in range(0, len(payload), 32)]
    nonzero = sum(any(tile) for tile in tiles)
    varied = sum(len(set(tile)) >= 3 for tile in tiles)
    zero = len(tiles) - nonzero
    score = (0.55 * nonzero / len(tiles) + 0.45 * varied / len(tiles))
    return {"tile_count": len(tiles), "tile_score": round(score, 6),
            "zero_tile_fraction": round(zero / len(tiles), 6)}


def byte_entropy(payload):
    if not payload:
        return 0.0
    counts = [0] * 256
    for value in payload:
        counts[value] += 1
    size = len(payload)
    return -sum((count / size) * math.log2(count / size)
                for count in counts if count)


def write_tile_preview(payload, path):
    """Write a neutral 4bpp, 16-tiles-wide PGM contact sheet."""
    if len(payload) < 32 or len(payload) % 32:
        return False
    tile_count = len(payload) // 32
    columns = 16
    rows = (tile_count + columns - 1) // columns
    width, height = columns * 8, rows * 8
    pixels = bytearray(width * height)
    for tile_index in range(tile_count):
        tile = payload[tile_index * 32:(tile_index + 1) * 32]
        tile_x, tile_y = (tile_index % columns) * 8, (tile_index // columns) * 8
        for y in range(8):
            for x in range(8):
                packed = tile[y * 4 + x // 2]
                value = (packed >> (4 * (x & 1))) & 0xf
                pixels[(tile_y + y) * width + tile_x + x] = value * 17
    path.write_bytes(f"P5\n{width} {height}\n255\n".encode() + pixels)
    return True


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    parser.add_argument("--config", default=ROOT / "config/retail-us.json", type=Path)
    parser.add_argument("--scan-step", type=int, default=4,
                        help="ROM scan alignment; type-0x10 pointers are normally 4-byte aligned")
    args = parser.parse_args()
    if args.output_dir.resolve().is_relative_to(ROOT):
        raise SystemExit("Resource output must be outside the source tree")
    if args.scan_step < 1:
        raise SystemExit("--scan-step must be positive")
    rom = args.rom.read_bytes()
    if digest(rom) != ROM_SHA256:
        raise SystemExit("Input is not the pinned US retail ROM")
    config = json.loads(args.config.read_text())
    ranges = sorted((module["offset"], module["offset"] + module["size"])
                    for module in config["modules"] if module.get("enabled", True))
    pointer_sites = {}
    for site in range(0, len(rom) - 3, 4):
        value = struct.unpack_from("<I", rom, site)[0]
        if 0x08000000 <= value < 0x08000000 + len(rom):
            pointer_sites.setdefault(value - 0x08000000, []).append(site)
    output = args.output_dir
    payload_dir = output / "payload"
    encoded_dir = output / "encoded"
    preview_dir = output / "tile-previews"
    payload_dir.mkdir(parents=True, exist_ok=True)
    encoded_dir.mkdir(parents=True, exist_ok=True)
    preview_dir.mkdir(parents=True, exist_ok=True)

    streams = []
    cursor = 0
    while cursor + 4 <= len(rom):
        decoded = decode_lz77(rom, cursor)
        if decoded is None:
            cursor += args.scan_step
            continue
        end, payload = decoded
        if overlaps_selected(cursor, end, ranges):
            cursor += args.scan_step
            continue
        if streams and cursor < streams[-1]["end_exclusive"]:
            cursor += args.scan_step
            continue
        index = len(streams)
        stem = f"stream-{index:04d}-0x{cursor:06x}"
        encoded = rom[cursor:end]
        (encoded_dir / f"{stem}.lz77").write_bytes(encoded)
        (payload_dir / f"{stem}.bin").write_bytes(payload)
        preview = tile_score(payload)
        preview_file = None
        if preview["tile_score"] >= 0.35 and len(payload) <= 0x20000:
            preview_file = f"tile-previews/{stem}.pgm"
            write_tile_preview(payload, output / preview_file)
        direct_sites = [site for site in pointer_sites.get(cursor, ())
                        if not cursor <= site < end]
        streams.append({
            "index": index,
            "rom_offset": cursor,
            "end_exclusive": end,
            "encoded_bytes": len(encoded),
            "decoded_bytes": len(payload),
            "encoded_sha256": digest(encoded),
            "decoded_sha256": digest(payload),
            "direct_pointer_sites": direct_sites,
            "entropy_bits_per_byte": round(byte_entropy(payload), 6),
            **preview,
            "preview_file": preview_file,
            "encoded_file": f"encoded/{stem}.lz77",
            "payload_file": f"payload/{stem}.bin",
        })
        # Keep scanning on the requested alignment.  Adjacent streams may
        # begin at a non-four-byte offset relative to the previous end.
        cursor += args.scan_step

    groups = []
    for stream in streams:
        if not groups or stream["rom_offset"] - groups[-1]["end_exclusive"] > 16:
            groups.append({"first_index": stream["index"],
                           "last_index": stream["index"],
                           "start": stream["rom_offset"],
                           "end_exclusive": stream["end_exclusive"],
                           "stream_count": 1})
        else:
            group = groups[-1]
            group["last_index"] = stream["index"]
            group["end_exclusive"] = stream["end_exclusive"]
            group["stream_count"] += 1
    for group in groups:
        group["encoded_bytes"] = sum(s["encoded_bytes"] for s in streams[
            group["first_index"]:group["last_index"] + 1])
        group["decoded_bytes"] = sum(s["decoded_bytes"] for s in streams[
            group["first_index"]:group["last_index"] + 1])

    report = {
        "reference_sha256": ROM_SHA256,
        "rom_bytes": len(rom),
        "scan_step": args.scan_step,
        "stream_count": len(streams),
        "encoded_bytes": sum(s["encoded_bytes"] for s in streams),
        "decoded_bytes": sum(s["decoded_bytes"] for s in streams),
        "tile_preview_count": sum(s["preview_file"] is not None for s in streams),
        "groups": groups,
        "streams": streams,
        "caveat": "A valid type-0x10 stream is only a resource candidate until a pointer or runtime copy proves its game role. Encoded files preserve the exact retail span; payload files are decoded bytes.",
    }
    (output / "manifest.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in (
        "stream_count", "encoded_bytes", "decoded_bytes", "tile_preview_count")}))


if __name__ == "__main__":
    main()
