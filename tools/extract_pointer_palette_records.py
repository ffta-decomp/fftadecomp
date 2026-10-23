#!/usr/bin/env python3
"""Export the pointer-backed counted BGR555 palette records."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_pointer_lz77_records import POINTER_START, POINTER_END, ROM_BASE, ROM_SHA256

BANK_START = 0x8e9c0c
BANK_END = 0x8ec8e0
RECORD_COUNT = 223


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_record(record, source_dir):
    fields = json.loads((source_dir / "records" / record["file"]).read_text())
    groups = fields["groups"]
    if len(groups) != record["group_count"] or any(
            len(group) != record["colors_per_group"] for group in groups):
        raise ValueError("counted palette dimensions differ")
    encoded = bytearray((len(groups), record["colors_per_group"]))
    for group in groups:
        for color in group:
            channels = [color[channel] for channel in ("red", "green", "blue")]
            if any(type(value) is not int or not 0 <= value <= 31 for value in channels):
                raise ValueError("counted palette color channel differs")
            value = channels[0] | channels[1] << 5 | channels[2] << 10
            encoded += value.to_bytes(2, "little")
    encoded += bytes(record["padding_bytes"])
    if len(encoded) != record["selected_bytes"] or sha256(encoded) != record["source_sha256"]:
        raise ValueError(f"counted palette differs at 0x{record['start']:08x}")
    return bytes(encoded)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if rom[BANK_START - 4:BANK_START] != b"\0\0\0\0":
        raise ValueError("counted palette leading alignment differs")
    output.mkdir(parents=True, exist_ok=True)
    record_dir = output / "records"
    record_dir.mkdir(exist_ok=True)
    pointers = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if BANK_START <= target < BANK_END:
            pointers.setdefault(target, []).append(site)
    starts = sorted(pointers)
    if len(starts) != RECORD_COUNT or starts[0] != BANK_START:
        raise ValueError("counted palette pointer directory differs")
    records = []
    for index, start in enumerate(starts):
        next_start = starts[index + 1] if index + 1 < len(starts) else BANK_END
        group_count, colors_per_group = rom[start:start + 2]
        if not 1 <= group_count <= 16 or not 1 <= colors_per_group <= 15:
            raise ValueError("counted palette dimensions leave observed bounds")
        source_bytes = 2 + 2 * group_count * colors_per_group
        if start + source_bytes > next_start:
            raise ValueError("counted palette leaves its pointer-bounded record")
        colors = [int.from_bytes(rom[pos:pos + 2], "little")
                  for pos in range(start + 2, start + source_bytes, 2)]
        if any(color & 0x8000 for color in colors):
            raise ValueError("counted palette uses the BGR555 reserved bit")
        gap = next_start - start - source_bytes
        padding = gap if gap <= 3 and rom[start + source_bytes:next_start] == bytes(gap) else 0
        selected = source_bytes + padding
        fields = {"groups": [[{"red": color & 31, "green": color >> 5 & 31,
                                "blue": color >> 10 & 31}
                               for color in colors[group * colors_per_group:(group + 1) * colors_per_group]]
                              for group in range(group_count)]}
        file_name = f"palette-0x{start:06x}.json"
        (record_dir / file_name).write_text(json.dumps(fields, indent=2) + "\n")
        record = {"start": start, "next_start": next_start,
                  "selected_bytes": selected, "padding_bytes": padding,
                  "opaque_tail_bytes": gap - padding,
                  "group_count": group_count, "colors_per_group": colors_per_group,
                  "pointer_sites": pointers[start], "file": file_name,
                  "source_sha256": sha256(rom[start:start + selected])}
        if encode_record(record, output) != rom[start:start + selected]:
            raise ValueError("counted palette record does not round-trip")
        records.append(record)
    groups = []
    for record in records:
        start = record["start"]
        end = start + record["selected_bytes"]
        if groups and start == groups[-1]["end"]:
            groups[-1]["end"] = end
            groups[-1]["record_starts"].append(start)
            groups[-1]["padding_bytes"] += record["padding_bytes"]
        else:
            groups.append({"start": start, "end": end, "record_starts": [start],
                           "padding_bytes": record["padding_bytes"]})
    for group in groups:
        group["source_sha256"] = sha256(rom[group["start"]:group["end"]])
    manifest = {"reference_sha256": ROM_SHA256,
                "pointer_table_window": [POINTER_START, POINTER_END],
                "records": records, "build_groups": groups,
                "record_count": len(records), "group_count": len(groups),
                "selected_bytes": sum(record["selected_bytes"] for record in records),
                "padding_bytes": sum(record["padding_bytes"] for record in records),
                "opaque_tail_bytes": sum(record["opaque_tail_bytes"] for record in records),
                "scope_note": "Only counted BGR555 values and proven zero alignment rebuild. Pointer-bounded tails with other content remain unclassified."}
    if (manifest["group_count"] != 43 or manifest["selected_bytes"] != 8018 or
            manifest["padding_bytes"] != 148 or manifest["opaque_tail_bytes"] != 3458):
        raise ValueError("counted palette coverage differs")
    for group in groups:
        if reconstruct_group(manifest, output, group["start"]) != rom[group["start"]:group["end"]]:
            raise ValueError("counted palette build group does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"record_count": len(records), "build_groups": len(groups),
            "selected_bytes": manifest["selected_bytes"],
            "padding_bytes": manifest["padding_bytes"],
            "opaque_tail_bytes": manifest["opaque_tail_bytes"],
            "manifest_sha256": sha256(path.read_bytes())}


def group_entry(manifest, offset):
    matches = [group for group in manifest["build_groups"] if group["start"] == offset]
    if len(matches) != 1:
        raise ValueError("counted palette build group is not unique")
    return matches[0]


def group_source_files(manifest, offset, source_dir):
    starts = set(group_entry(manifest, offset)["record_starts"])
    return [source_dir / "records" / record["file"]
            for record in manifest["records"] if record["start"] in starts]


def reconstruct_group(manifest, source_dir, offset):
    group = group_entry(manifest, offset)
    records = {record["start"]: record for record in manifest["records"]}
    encoded = bytearray()
    for start in group["record_starts"]:
        if group["start"] + len(encoded) != start:
            raise ValueError("counted palette record order differs")
        encoded += encode_record(records[start], source_dir)
    if (len(encoded) != group["end"] - group["start"] or
            sha256(encoded) != group["source_sha256"] or
            sum(records[start]["padding_bytes"] for start in group["record_starts"])
            != group["padding_bytes"]):
        raise ValueError("counted palette build group differs")
    return bytes(encoded)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("counted palette export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
