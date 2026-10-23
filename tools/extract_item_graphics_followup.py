#!/usr/bin/env python3
"""Export the indexed fields and five A7 archives after item icons."""

import argparse
import json
from pathlib import Path

from indexed_graphics_codec import (archive_token_plan, encode_indexed_archive,
                                    parse_archive,
                                    rasterize_4bpp_grid, serialize_4bpp_grid,
                                    sha256, write_index_png)


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x3d3d14
ARCHIVE_START = 0x3d3d64
END = 0x3e105c
INDEX_LITERAL = 0xcb9dc
FIRST_ARCHIVE_LITERAL = 0xcb9c8
ARCHIVE_LITERAL_SITES = ((0x6eae0, 0xcb9c8), (0x1857c, 0x185b0),
                         (0xcb924,), (0xcb910,), (0xcb900,))
INDEX_RECORDS = 38
ENTRY_COUNTS = (38, 30, 165, 165, 165)
DECODED_SIZES = (128, 192, 96, 96, 96)


def encode_followup(manifest, source_dir):
    if (manifest["start"] != START or manifest["end"] != END or
            len(manifest["archives"]) != len(ENTRY_COUNTS)):
        raise ValueError("item graphics follow-up boundary differs")
    header = manifest["index_header_halfwords"]
    records = manifest["index_record_nibbles"]
    if (len(header) != 2 or len(records) != INDEX_RECORDS or
            any(type(value) is not int or not 0 <= value <= 65535 for value in header) or
            any(len(row) != 4 or any(type(value) is not int or not 0 <= value <= 15
                for value in row) for row in records)):
        raise ValueError("item graphics index shape differs")
    output = bytearray()
    for value in header:
        output.extend(value.to_bytes(2, "little"))
    for low0, high0, low1, high1 in records:
        output.extend((low0 | high0 << 4, low1 | high1 << 4))
    if START + len(output) != ARCHIVE_START:
        raise ValueError("item graphics index length differs")
    for index, item in enumerate(manifest["archives"]):
        if START + len(output) != item["start"]:
            raise ValueError("item graphics archive position differs")
        archive_dir = (source_dir / item["directory"]).resolve()
        if not archive_dir.is_relative_to(source_dir.resolve()):
            raise ValueError("item graphics archive path escapes export")
        archive = json.loads((archive_dir / "manifest.json").read_text())
        if (archive["reference_sha256"] != ROM_SHA256 or
                archive["archive"]["entry_count"] != ENTRY_COUNTS[index] or
                archive["archive"]["decoded_bytes_per_entry"] != DECODED_SIZES[index]):
            raise ValueError("item graphics archive shape differs")
        encoded = encode_indexed_archive(archive, archive_dir)
        if len(encoded) != item["encoded_bytes"] or sha256(encoded) != item["source_sha256"]:
            raise ValueError("item graphics archive differs from retail")
        padding = item["padding_bytes"]
        if type(padding) is not int or not 0 <= padding <= 3:
            raise ValueError("item graphics archive alignment differs")
        output += encoded + bytes(padding)
    if len(output) != END - START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("item graphics follow-up differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("item graphics output must be outside the source tree")
    if (int.from_bytes(rom[INDEX_LITERAL:INDEX_LITERAL + 4], "little") != ROM_BASE + START or
            int.from_bytes(rom[FIRST_ARCHIVE_LITERAL:FIRST_ARCHIVE_LITERAL + 4], "little") != ROM_BASE + ARCHIVE_START):
        raise ValueError("item graphics caller literal differs")
    index_data = rom[START:ARCHIVE_START]
    if len(index_data) != 4 + 2 * INDEX_RECORDS:
        raise ValueError("item graphics index length differs")
    output.mkdir(parents=True, exist_ok=True)
    archives = []
    cursor = ARCHIVE_START
    decoded_bytes = 0
    padding_bytes = 0
    for archive_index, (entry_count, decoded_size) in enumerate(zip(ENTRY_COUNTS, DECODED_SIZES)):
        parsed = parse_archive(rom, cursor)
        for site in ARCHIVE_LITERAL_SITES[archive_index]:
            if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + cursor:
                raise ValueError("item graphics archive caller differs")
        if (len(parsed["entries"]) != entry_count or
                parsed["decoded_bytes_per_entry"] != decoded_size or
                parsed["mode"] != 0 or parsed["bit_width"] != 5):
            raise ValueError("item graphics archive dimensions differ")
        archive_end = parsed["dictionary_used_end"]
        next_cursor = (archive_end + 3) & ~3
        if next_cursor > END or rom[archive_end:next_cursor] != bytes(next_cursor - archive_end):
            raise ValueError("item graphics archive alignment differs")
        archive_dir = output / f"archive-{archive_index:02d}"
        entries_dir = archive_dir / "entries"
        previews_dir = archive_dir / "indexed-previews"
        entries_dir.mkdir(parents=True, exist_ok=True)
        previews_dir.mkdir(exist_ok=True)
        dictionary_start = parsed["table_file_offset"] + parsed["dictionary_base"]
        dictionary = rom[dictionary_start:archive_end]
        (archive_dir / "dictionary.bin").write_bytes(dictionary)
        entries = []
        tile_count = decoded_size // 32
        columns = 2 if tile_count % 2 == 0 else 1
        rows = tile_count // columns
        for entry in parsed["entries"]:
            raw = entry["raw"]
            pixels = rasterize_4bpp_grid(raw, columns, rows)
            if serialize_4bpp_grid(pixels, columns, rows) != raw:
                raise ValueError("item graphics pixel round-trip differs")
            entry_index = entry["entry"]
            (entries_dir / f"entry-{entry_index:03d}.4bpp").write_bytes(raw)
            write_index_png(previews_dir / f"entry-{entry_index:03d}.png",
                            columns * 8, rows * 8, pixels)
            record = {key: value for key, value in entry.items() if key != "raw"}
            record["tokens"] = archive_token_plan(
                rom, entry, parsed["table_file_offset"], parsed["bit_width"],
                parsed["dictionary_base"])
            record["source_sha256"] = sha256(rom[entry["source_offset"]:entry["source_end"]])
            entries.append(record)
        archive_manifest = {
            "reference_sha256": ROM_SHA256,
            "archive": {"entry_count": entry_count, "table_offset": parsed["table_offset"],
                        "offsets": parsed["offsets"], "mode": parsed["mode"],
                        "bit_width": parsed["bit_width"],
                        "decoded_bytes_per_entry": decoded_size,
                        "dictionary_sha256": sha256(dictionary),
                        "source_span_bytes": archive_end - cursor,
                        "source_span_sha256": sha256(rom[cursor:archive_end]),
                        "tile_directory": "entries", "tile_stem": "entry",
                        "tile_index_width": 3},
            "entries": entries,
        }
        (archive_dir / "manifest.json").write_text(json.dumps(archive_manifest, indent=2) + "\n")
        if encode_indexed_archive(archive_manifest, archive_dir) != rom[cursor:archive_end]:
            raise ValueError("item graphics archive does not round-trip")
        archives.append({"start": cursor, "encoded_bytes": archive_end - cursor,
                         "padding_bytes": next_cursor - archive_end,
                         "directory": archive_dir.name,
                         "literal_sites": ARCHIVE_LITERAL_SITES[archive_index],
                         "source_sha256": sha256(rom[cursor:archive_end])})
        decoded_bytes += decoded_size * entry_count
        padding_bytes += next_cursor - archive_end
        cursor = next_cursor
    if cursor != END:
        raise ValueError("item graphics archives do not reach the next bank")
    manifest = {
        "reference_sha256": ROM_SHA256, "start": START, "end": END,
        "index_header_halfwords": [int.from_bytes(index_data[pos:pos + 2], "little")
                                   for pos in (0, 2)],
        "index_record_nibbles": [[index_data[pos] & 15, index_data[pos] >> 4,
                                   index_data[pos + 1] & 15, index_data[pos + 1] >> 4]
                                  for pos in range(4, len(index_data), 2)],
        "index_record_count": INDEX_RECORDS, "archive_count": len(ENTRY_COUNTS),
        "entry_count": sum(ENTRY_COUNTS), "decoded_bytes": decoded_bytes,
        "padding_bytes": padding_bytes, "archives": archives,
        "source_sha256": sha256(rom[START:END]),
        "scope_note": "The indexed records and A7 pixels round-trip. The caller reads one index-record nibble; remaining meanings, palettes, and final placement are unresolved.",
    }
    if encode_followup(manifest, output) != rom[START:END]:
        raise ValueError("item graphics follow-up does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"archives": len(archives), "entries": manifest["entry_count"],
            "source_bytes": END - START, "decoded_bytes": decoded_bytes,
            "padding_bytes": padding_bytes, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
