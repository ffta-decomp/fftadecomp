#!/usr/bin/env python3
"""Export sixteen consecutive eight-entry A7 graphics archives."""

import argparse
import json
from pathlib import Path

from indexed_graphics_codec import (archive_token_plan, encode_indexed_archive,
                                    parse_archive, rasterize_4bpp_grid,
                                    serialize_4bpp_grid, sha256, write_index_png)


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0x422c04
END = 0x425104
ARCHIVE_COUNT = 16
ENTRIES_PER_ARCHIVE = 8
DECODED_BYTES_PER_ENTRY = 128


def encode_batch(manifest, source_dir):
    if (manifest["start"] != START or manifest["end"] != END or
            len(manifest["archives"]) != ARCHIVE_COUNT):
        raise ValueError("A7 graphics batch boundary differs")
    output = bytearray()
    for item in manifest["archives"]:
        if START + len(output) != item["start"]:
            raise ValueError("A7 graphics archive position differs")
        archive_dir = (source_dir / item["directory"]).resolve()
        if not archive_dir.is_relative_to(source_dir.resolve()):
            raise ValueError("A7 graphics archive path escapes export")
        archive = json.loads((archive_dir / "manifest.json").read_text())
        if archive["reference_sha256"] != manifest["reference_sha256"]:
            raise ValueError("A7 graphics archive revision differs")
        encoded = encode_indexed_archive(archive, archive_dir)
        if (len(encoded) != item["encoded_bytes"] or
                sha256(encoded) != item["source_sha256"]):
            raise ValueError("A7 graphics archive differs from retail")
        output += encoded
        padding = item["padding_bytes"]
        if type(padding) is not int or not 0 <= padding <= 3:
            raise ValueError("A7 graphics archive alignment differs")
        output += bytes(padding)
    if len(output) != END - START or sha256(output) != manifest["source_sha256"]:
        raise ValueError("A7 graphics batch differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("A7 graphics batch output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    items = []
    cursor = START
    decoded_bytes = 0
    padding_bytes = 0
    for archive_index in range(ARCHIVE_COUNT):
        parsed = parse_archive(rom, cursor)
        if (len(parsed["entries"]) != ENTRIES_PER_ARCHIVE or
                parsed["decoded_bytes_per_entry"] != DECODED_BYTES_PER_ENTRY or
                parsed["mode"] != 0 or parsed["bit_width"] != 5):
            raise ValueError("A7 graphics archive dimensions differ")
        archive_end = parsed["dictionary_used_end"]
        next_cursor = (archive_end + 3) & ~3
        if next_cursor > END or rom[archive_end:next_cursor] != bytes(next_cursor - archive_end):
            raise ValueError("A7 graphics archive zero alignment differs")
        archive_dir = output / f"archive-{archive_index:02d}"
        tiles_dir = archive_dir / "entries"
        preview_dir = archive_dir / "indexed-previews"
        tiles_dir.mkdir(parents=True, exist_ok=True)
        preview_dir.mkdir(exist_ok=True)
        dictionary_start = parsed["table_file_offset"] + parsed["dictionary_base"]
        dictionary = rom[dictionary_start:archive_end]
        (archive_dir / "dictionary.bin").write_bytes(dictionary)
        entries = []
        for entry in parsed["entries"]:
            raw = entry["raw"]
            pixels = rasterize_4bpp_grid(raw, 2, 2)
            if serialize_4bpp_grid(pixels, 2, 2) != raw:
                raise ValueError("A7 graphics entry pixel round-trip differs")
            index = entry["entry"]
            (tiles_dir / f"entry-{index:02d}.4bpp").write_bytes(raw)
            write_index_png(preview_dir / f"entry-{index:02d}.png", 16, 16, pixels)
            item = {key: value for key, value in entry.items() if key != "raw"}
            item["tokens"] = archive_token_plan(
                rom, entry, parsed["table_file_offset"], parsed["bit_width"],
                parsed["dictionary_base"])
            item["source_sha256"] = sha256(rom[entry["source_offset"]:entry["source_end"]])
            entries.append(item)
            decoded_bytes += len(raw)
        archive_manifest = {
            "reference_sha256": ROM_SHA256,
            "archive": {"entry_count": ENTRIES_PER_ARCHIVE,
                        "table_offset": parsed["table_offset"],
                        "offsets": parsed["offsets"], "mode": parsed["mode"],
                        "bit_width": parsed["bit_width"],
                        "decoded_bytes_per_entry": DECODED_BYTES_PER_ENTRY,
                        "dictionary_sha256": sha256(dictionary),
                        "source_span_bytes": archive_end - cursor,
                        "source_span_sha256": sha256(rom[cursor:archive_end]),
                        "tile_directory": "entries", "tile_stem": "entry",
                        "tile_index_width": 2},
            "entries": entries,
        }
        (archive_dir / "manifest.json").write_text(json.dumps(archive_manifest, indent=2) + "\n")
        if encode_indexed_archive(archive_manifest, archive_dir) != rom[cursor:archive_end]:
            raise ValueError("A7 graphics archive does not round-trip")
        items.append({"start": cursor, "encoded_bytes": archive_end - cursor,
                      "padding_bytes": next_cursor - archive_end,
                      "directory": archive_dir.name,
                      "source_sha256": sha256(rom[cursor:archive_end])})
        padding_bytes += next_cursor - archive_end
        cursor = next_cursor
    if cursor != END:
        raise ValueError("A7 graphics batch does not reach its next bank")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "archive_count": ARCHIVE_COUNT, "entry_count": ARCHIVE_COUNT * ENTRIES_PER_ARCHIVE,
                "decoded_bytes": decoded_bytes, "padding_bytes": padding_bytes,
                "source_sha256": sha256(rom[START:END]), "archives": items,
                "scope_note": "A7 archives and grayscale indexed previews round-trip; retail palette assignment and final layout remain unresolved."}
    if encode_batch(manifest, output) != rom[START:END]:
        raise ValueError("A7 graphics batch does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"archives": ARCHIVE_COUNT, "entries": manifest["entry_count"],
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
