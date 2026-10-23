#!/usr/bin/env python3
"""Extract the sparse secondary map-animation channels as reversible 4bpp banks."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
MAP_TABLE = 0x569104
MAP_COUNT = 162
MAP_STRIDE = 0x58


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def u32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def extract_banks(rom, output):
    frame_dir = output / "frames"
    frame_dir.mkdir(parents=True, exist_ok=True)
    banks = []
    for map_id in range(MAP_COUNT):
        record = MAP_TABLE + map_id * MAP_STRIDE
        channels = []
        for channel_index in range(3):
            metadata_relative = u32(rom, record + 0x20 + channel_index * 4)
            tiles_relative = u32(rom, record + 0x30 + channel_index * 4)
            destination = u32(rom, record + 0x40 + channel_index * 4)
            if not metadata_relative:
                if tiles_relative or destination:
                    raise ValueError("secondary animation channel has no metadata")
                continue
            if not tiles_relative or not destination:
                raise ValueError("secondary animation channel is incomplete")
            metadata = MAP_TABLE + metadata_relative
            tiles = MAP_TABLE + tiles_relative
            byte_count = u16(rom, metadata)
            frame_count = u16(rom, metadata + 2)
            if not byte_count or byte_count % 32 or not frame_count:
                raise ValueError("secondary animation is not whole 4bpp frames")
            frames = [{"frame": frame, "duration": u16(rom, metadata + 4 + frame * 4),
                       "source_tile": u16(rom, metadata + 6 + frame * 4)}
                      for frame in range(frame_count)]
            channels.append({"index": channel_index, "metadata_offset": metadata,
                             "tiles_offset": tiles, "vram_destination": destination,
                             "byte_count": byte_count, "frames": frames})
        if not channels:
            continue
        tile_offsets = {channel["tiles_offset"] for channel in channels}
        if len(tile_offsets) != 1:
            raise ValueError("secondary animation channels do not share tiles")
        tiles = tile_offsets.pop()
        if channels[0]["metadata_offset"] >= tiles:
            raise ValueError("secondary animation metadata is not before tiles")
        for index, channel in enumerate(channels):
            following = channels[index + 1]["metadata_offset"] if index + 1 < len(channels) else tiles
            metadata_end = channel["metadata_offset"] + 4 + 4 * len(channel["frames"])
            gap = following - metadata_end
            if gap not in (0, 4):
                raise ValueError("secondary animation metadata gap is not a word")
            channel["separator_word"] = u32(rom, metadata_end) if gap else None
        bank_bytes = max(frame["source_tile"] * 32 + channel["byte_count"]
                         for channel in channels for frame in channel["frames"])
        frame_files = {}
        for channel in channels:
            for frame in channel["frames"]:
                offset = frame["source_tile"] * 32
                key = (offset, channel["byte_count"])
                if key not in frame_files:
                    name = f"secondary-0x{channels[0]['metadata_offset']:06x}-tile-{offset:05x}-{channel['byte_count']:04x}.4bpp"
                    raw = rom[tiles + offset:tiles + offset + channel["byte_count"]]
                    if len(raw) != channel["byte_count"]:
                        raise ValueError("secondary animation frame exceeds ROM")
                    (frame_dir / name).write_bytes(raw)
                    frame_files[key] = {"tile_byte_offset": offset,
                                        "byte_count": len(raw), "file": name,
                                        "sha256": sha256(raw)}
        end = tiles + bank_bytes
        banks.append({"map_id": map_id, "start": channels[0]["metadata_offset"],
                      "end": end, "tiles_offset": tiles, "tile_bank_bytes": bank_bytes,
                      "tile_bank_sha256": sha256(rom[tiles:end]),
                      "source_sha256": sha256(rom[channels[0]["metadata_offset"]:end]),
                      "channels": channels, "unique_frames": list(frame_files.values())})
    return {"reference_sha256": ROM_SHA256, "map_count": MAP_COUNT,
            "bank_count": len(banks), "banks": banks,
            "caveat": "The three secondary channel slots are grouped by table shape. Their runtime roles remain tentative; exported data are indexed 4bpp frames."}


def bank_entry(manifest, start):
    matches = [bank for bank in manifest["banks"] if bank["start"] == start]
    if len(matches) != 1:
        raise ValueError(f"secondary animation bank 0x{start:08x} is not unique")
    return matches[0]


def reconstruct_bank(manifest, source_dir, start):
    bank = bank_entry(manifest, start)
    output = bytearray(bank["end"] - start)
    tiles = bank["tiles_offset"]
    if not start < tiles < bank["end"] or bank["end"] - tiles != bank["tile_bank_bytes"]:
        raise ValueError("secondary animation bank boundaries differ")
    for index, channel in enumerate(bank["channels"]):
        following = (bank["channels"][index + 1]["metadata_offset"]
                     if index + 1 < len(bank["channels"]) else tiles)
        metadata = channel["metadata_offset"]
        frames = channel["frames"]
        data = bytearray(channel["byte_count"].to_bytes(2, "little"))
        data.extend(len(frames).to_bytes(2, "little"))
        for frame_index, frame in enumerate(frames):
            if frame["frame"] != frame_index:
                raise ValueError("secondary animation frame order differs")
            data.extend(frame["duration"].to_bytes(2, "little"))
            data.extend(frame["source_tile"].to_bytes(2, "little"))
        if channel["separator_word"] is not None:
            data.extend(channel["separator_word"].to_bytes(4, "little"))
        if metadata + len(data) != following:
            raise ValueError("secondary animation metadata boundary differs")
        output[metadata - start:following - start] = data
    coverage = bytearray(bank["tile_bank_bytes"])
    for frame in bank["unique_frames"]:
        offset = frame["tile_byte_offset"]
        raw = (source_dir / "frames" / frame["file"]).read_bytes()
        if len(raw) != frame["byte_count"] or sha256(raw) != frame["sha256"]:
            raise ValueError("secondary animation frame differs from export")
        if offset < 0 or offset + len(raw) > len(coverage):
            raise ValueError("secondary animation frame leaves tile bank")
        for byte_index, value in enumerate(raw):
            position = offset + byte_index
            if coverage[position] and output[tiles - start + position] != value:
                raise ValueError("secondary animation overlapping frames differ")
            output[tiles - start + position] = value
            coverage[position] = 1
    if not all(coverage) or sha256(output[tiles - start:]) != bank["tile_bank_sha256"]:
        raise ValueError("secondary animation tile bank has gaps or differs")
    if sha256(output) != bank["source_sha256"]:
        raise ValueError(f"secondary animation source differs at 0x{start:08x}")
    return bytes(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output.is_relative_to(root):
        raise SystemExit("Secondary animation output must be outside the source tree")
    rom = args.rom.read_bytes()
    if sha256(rom) != ROM_SHA256:
        raise SystemExit("Input is not the pinned US retail ROM")
    manifest = extract_banks(rom, output)
    for bank in manifest["banks"]:
        rebuilt = reconstruct_bank(manifest, output, bank["start"])
        if rebuilt != rom[bank["start"]:bank["end"]]:
            raise ValueError("secondary animation bank does not round-trip")
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"bank_count": manifest["bank_count"],
                      "source_bytes": sum(bank["end"] - bank["start"]
                                          for bank in manifest["banks"]),
                      "unique_frames": sum(len(bank["unique_frames"])
                                           for bank in manifest["banks"])}))


if __name__ == "__main__":
    main()
