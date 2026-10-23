#!/usr/bin/env python3
"""Export and rebuild the retail map resource directory from typed fields."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
MAP_TABLE = 0x569104
MAP_COUNT = 162
MAP_STRIDE = 0x58
ROM_SIZE = 16 * 1024 * 1024
SOURCE_FIELDS = ("graphics", "arrangement", "clipping", "palette", "terrain")


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def word(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def export_map_table(rom):
    source = rom[MAP_TABLE:MAP_TABLE + MAP_COUNT * MAP_STRIDE]
    records = []
    for map_id in range(MAP_COUNT):
        record = source[map_id * MAP_STRIDE:(map_id + 1) * MAP_STRIDE]
        sources = {name: word(record, index * 4)
                   for index, name in enumerate(SOURCE_FIELDS)}
        animations = [{"metadata_relative": word(record, 0x14),
                       "tiles_relative": word(record, 0x18),
                       "vram_destination": word(record, 0x1c)}]
        animations += [{"metadata_relative": word(record, 0x20 + index * 4),
                        "tiles_relative": word(record, 0x30 + index * 4),
                        "vram_destination": word(record, 0x40 + index * 4)}
                       for index in range(3)]
        records.append({"map_id": map_id, "sources_relative": sources,
                        "animation_channels": animations,
                        "reserved_words": [word(record, offset)
                                           for offset in (0x2c, 0x3c, 0x4c, 0x50)],
                        "render_modes": [record[0x54], record[0x55]],
                        "shared_palette_index": record[0x56],
                        "reserved_byte": record[0x57]})
    return {"reference_sha256": ROM_SHA256,
            "rom_offset": MAP_TABLE, "record_count": MAP_COUNT,
            "record_bytes": MAP_STRIDE,
            "source_sha256": sha256(source), "records": records,
            "field_status": "Offsets 0x20..0x48 are grouped by pointer shape as tentative extra animation channels; runtime consumers still need confirmation."}


def encode_map_table(manifest, verify_source=True):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["rom_offset"] != MAP_TABLE or
            manifest["record_count"] != MAP_COUNT or
            manifest["record_bytes"] != MAP_STRIDE or
            len(manifest["records"]) != MAP_COUNT):
        raise ValueError("map table revision or boundaries differ")

    def write_word(output, value):
        if type(value) is not int or not 0 <= value <= 0xffffffff:
            raise ValueError("map table word is out of range")
        output.extend(value.to_bytes(4, "little"))

    encoded = bytearray()
    for map_id, record in enumerate(manifest["records"]):
        if record["map_id"] != map_id or len(record["animation_channels"]) != 4:
            raise ValueError("map table record or channel order differs")
        sources = record["sources_relative"]
        if set(sources) != set(SOURCE_FIELDS):
            raise ValueError("map table source fields differ")
        for name in SOURCE_FIELDS:
            if not 0 < sources[name] < ROM_SIZE - MAP_TABLE:
                raise ValueError("map table resource pointer leaves ROM")
            write_word(encoded, sources[name])
        primary = record["animation_channels"][0]
        for name in ("metadata_relative", "tiles_relative", "vram_destination"):
            write_word(encoded, primary[name])
        extras = record["animation_channels"][1:]
        if len(record["reserved_words"]) != 4 or any(record["reserved_words"]):
            raise ValueError("map table reserved words differ from retail")
        for name in ("metadata_relative", "tiles_relative", "vram_destination"):
            for channel in extras:
                write_word(encoded, channel[name])
            # Each three-slot group occupies four words in the retail record.
            write_word(encoded, record["reserved_words"][{
                "metadata_relative": 0, "tiles_relative": 1,
                "vram_destination": 2}[name]])
        write_word(encoded, record["reserved_words"][3])
        bytes_at_end = record["render_modes"] + [record["shared_palette_index"],
                                                  record["reserved_byte"]]
        if len(record["render_modes"]) != 2 or any(
                type(value) is not int or not 0 <= value <= 255
                for value in bytes_at_end):
            raise ValueError("map table final byte fields are invalid")
        encoded.extend(bytes(bytes_at_end))
    if len(encoded) != MAP_COUNT * MAP_STRIDE:
        raise ValueError("map table serialization has the wrong length")
    if verify_source and sha256(encoded) != manifest["source_sha256"]:
        raise ValueError("map table source does not match retail")
    return bytes(encoded)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output.resolve()
    if output.is_relative_to(root):
        raise SystemExit("Map table export must be outside the source tree")
    rom = args.rom.read_bytes()
    if len(rom) != ROM_SIZE or sha256(rom) != ROM_SHA256:
        raise SystemExit("Input is not the pinned US retail ROM")
    manifest = export_map_table(rom)
    if encode_map_table(manifest) != rom[MAP_TABLE:MAP_TABLE + MAP_COUNT * MAP_STRIDE]:
        raise ValueError("map table export does not round-trip")
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"record_count": MAP_COUNT, "source_bytes": MAP_COUNT * MAP_STRIDE,
                      "source_sha256": manifest["source_sha256"]}))


if __name__ == "__main__":
    main()
