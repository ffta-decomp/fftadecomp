#!/usr/bin/env python3
"""Export five pointer-backed A7 archives preceding the roster art."""

import argparse
import json
import math
from pathlib import Path

from indexed_graphics_codec import (archive_token_plan, encode_indexed_archive,
                                    parse_archive, rasterize_4bpp_grid,
                                    serialize_4bpp_grid, sha256, write_index_png)


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
ARCHIVES = (
    (0x3a93ac, 0x3a94cc, 4, 64, (0x22b00, 0x31498, 0x4dd28, 0x87470, 0x137ffc)),
    (0x3a94cc, 0x3a9ca4, 41, 64, (0x22b08, 0x31490, 0x4dd30, 0x87450, 0x137fdc)),
    (0x3a9ca4, 0x3aa184, 33, 64, (0x22b10, 0x231a0, 0x277f8, 0x27844,
                                     0x4f2e4, 0x65760)),
    (0x3aa184, 0x3ab42c, 90, 64, (0x314b0,)),
    (0x3acd68, 0x3ad154, 30, 64, (0x35dd0, 0x57c80)),
)


def bank_entry(manifest, start):
    matches = [item for item in manifest["archives"] if item["start"] == start]
    if len(matches) != 1:
        raise ValueError("pointer-backed A7 archive is not unique")
    return matches[0]


def encode_bank(manifest, source_dir, start):
    item = bank_entry(manifest, start)
    if (start, item["end"], item["entry_count"], item["decoded_bytes_per_entry"],
            tuple(item["literal_sites"])) not in ARCHIVES:
        raise ValueError("pointer-backed A7 archive shape differs")
    archive_dir = (source_dir / item["directory"]).resolve()
    if not archive_dir.is_relative_to(source_dir.resolve()):
        raise ValueError("pointer-backed A7 archive path escapes export")
    archive = json.loads((archive_dir / "manifest.json").read_text())
    if (archive["reference_sha256"] != manifest["reference_sha256"] or
            archive["archive"]["entry_count"] != item["entry_count"] or
            archive["archive"]["decoded_bytes_per_entry"] != item["decoded_bytes_per_entry"]):
        raise ValueError("pointer-backed A7 archive revision differs")
    encoded = encode_indexed_archive(archive, archive_dir)
    padding = item["padding_bytes"]
    if type(padding) is not int or not 0 <= padding <= 3:
        raise ValueError("pointer-backed A7 archive padding differs")
    result = encoded + bytes(padding)
    if len(result) != item["end"] - start or sha256(result) != item["source_sha256"]:
        raise ValueError("pointer-backed A7 archive differs from retail")
    return result


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("pointer-backed A7 output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    items = []
    for index, (start, end, entry_count, decoded_size, literal_sites) in enumerate(ARCHIVES):
        for site in literal_sites:
            if int.from_bytes(rom[site:site + 4], "little") != ROM_BASE + start:
                raise ValueError("pointer-backed A7 caller literal differs")
        parsed = parse_archive(rom, start)
        if (len(parsed["entries"]) != entry_count or
                parsed["decoded_bytes_per_entry"] != decoded_size or
                parsed["mode"] != 0 or parsed["bit_width"] != 5):
            raise ValueError("pointer-backed A7 dimensions differ")
        archive_end = parsed["dictionary_used_end"]
        if ((archive_end + 3) & ~3) != end or rom[archive_end:end] != bytes(end - archive_end):
            raise ValueError("pointer-backed A7 boundary or alignment differs")
        archive_dir = output / f"archive-{index:02d}"
        entries_dir = archive_dir / "entries"
        previews_dir = archive_dir / "indexed-previews"
        entries_dir.mkdir(parents=True, exist_ok=True)
        previews_dir.mkdir(exist_ok=True)
        dictionary_start = parsed["table_file_offset"] + parsed["dictionary_base"]
        dictionary = rom[dictionary_start:archive_end]
        (archive_dir / "dictionary.bin").write_bytes(dictionary)
        entries = []
        tile_count = decoded_size // 32
        columns = math.gcd(tile_count, 16)
        rows = tile_count // columns
        for entry in parsed["entries"]:
            raw = entry["raw"]
            pixels = rasterize_4bpp_grid(raw, columns, rows)
            if serialize_4bpp_grid(pixels, columns, rows) != raw:
                raise ValueError("pointer-backed A7 pixels differ")
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
                        "source_span_bytes": archive_end - start,
                        "source_span_sha256": sha256(rom[start:archive_end]),
                        "tile_directory": "entries", "tile_stem": "entry",
                        "tile_index_width": 3},
            "entries": entries,
        }
        (archive_dir / "manifest.json").write_text(json.dumps(archive_manifest, indent=2) + "\n")
        if encode_indexed_archive(archive_manifest, archive_dir) != rom[start:archive_end]:
            raise ValueError("pointer-backed A7 archive does not round-trip")
        items.append({"start": start, "end": end, "entry_count": entry_count,
                      "decoded_bytes_per_entry": decoded_size,
                      "literal_sites": literal_sites,
                      "padding_bytes": end - archive_end,
                      "directory": archive_dir.name,
                      "source_sha256": sha256(rom[start:end])})
    manifest = {"reference_sha256": ROM_SHA256, "archives": items,
                "archive_count": len(items),
                "entry_count": sum(item["entry_count"] for item in items),
                "source_bytes": sum(item["end"] - item["start"] for item in items),
                "padding_bytes": sum(item["padding_bytes"] for item in items),
                "scope_note": "Five pointer-backed A7 spans are selected. Intervening ROM bytes and palette/placement semantics remain unresolved."}
    if (manifest["source_bytes"], manifest["padding_bytes"]) != (9324, 7):
        raise ValueError("pointer-backed A7 total differs")
    for item in items:
        if encode_bank(manifest, output, item["start"]) != rom[item["start"]:item["end"]]:
            raise ValueError("pointer-backed A7 source does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"archives": len(items), "entries": manifest["entry_count"],
            "source_bytes": manifest["source_bytes"],
            "decoded_bytes": sum(item["entry_count"] * item["decoded_bytes_per_entry"]
                                 for item in items),
            "padding_bytes": manifest["padding_bytes"],
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
