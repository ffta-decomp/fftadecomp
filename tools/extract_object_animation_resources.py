#!/usr/bin/env python3
"""Rebuild literal-anchored object animation tables from typed halfword records."""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
FLAGS = 0x000C


def load_catalog(path):
    catalog = json.loads(path.read_text())
    roots = catalog.get("roots")
    if (catalog.get("schema_version") != 1 or
            catalog.get("reference_sha256") != ROM_SHA256 or
            not isinstance(roots, list) or len(roots) != 71):
        raise ValueError("object animation catalog differs")
    previous_end = -1
    for root in roots:
        start, end = root["start"], root["end"]
        first_end = root["first_table_end"]
        second_start = root["secondary_table_start"]
        if (start < previous_end or end <= start + 4 or
                first_end < start + 6 or second_start < first_end or
                second_start - first_end not in (0, 2) or
                second_start % 4 or end <= second_start or
                not root.get("literal_offsets")):
            raise ValueError("object animation catalog boundaries differ")
        previous_end = end
    return catalog


def _decode_table(span, base, end, width, expected_count):
    if base + 2 > end:
        raise ValueError("object animation table is empty")
    first_offset = struct.unpack_from("<H", span, base)[0]
    if first_offset != 2 * expected_count or base + first_offset > end:
        raise ValueError("object animation offset array differs")
    offsets = struct.unpack_from("<" + "H" * expected_count, span, base)
    if not offsets or tuple(sorted(set(offsets))) != offsets:
        raise ValueError("object animation offsets are not increasing")
    records = []
    cursor = first_offset
    for index, offset in enumerate(offsets):
        if offset != cursor or base + offset + 2 > end:
            raise ValueError("object animation records are not contiguous")
        count = struct.unpack_from("<H", span, base + offset)[0]
        record_end = base + offset + 2 + count * width
        if record_end > end:
            raise ValueError("object animation record exceeds table")
        values = struct.unpack_from("<" + "H" * (count * (width // 2)),
                                    span, base + offset + 2)
        if width == 6:
            records.append([list(values[i:i + 3]) for i in range(0, len(values), 3)])
        else:
            records.append(list(values))
        cursor = record_end - base
    if base + cursor != end:
        raise ValueError("object animation table has unclassified bytes")
    return records


def decode_resource(rom, root):
    start, end = root["start"], root["end"]
    span = rom[start:end]
    flags, secondary_offset = struct.unpack_from("<HH", span)
    if flags != FLAGS or secondary_offset != root["secondary_table_start"] - start:
        raise ValueError("object animation header differs")
    for literal in root["literal_offsets"]:
        if struct.unpack_from("<I", rom, literal)[0] != 0x08000000 + start:
            raise ValueError("object animation pointer anchor differs")
    first_end = root["first_table_end"] - start
    second_start = root["secondary_table_start"] - start
    if span[first_end:second_start] != bytes(second_start - first_end):
        raise ValueError("object animation table alignment differs")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "start": start, "end": end,
            "first_records": _decode_table(span, 4, first_end, 6,
                                           root["first_entry_count"]),
            "secondary_records": _decode_table(span, second_start, len(span), 2,
                                               root["secondary_entry_count"])}


def _encode_table(output, base, end, records, width, expected_count):
    if not isinstance(records, list) or len(records) != expected_count:
        raise ValueError("object animation record count differs")
    cursor = base + 2 * len(records)
    for index, record in enumerate(records):
        if not isinstance(record, list) or len(record) > 0xFFFF:
            raise ValueError("invalid object animation record")
        offset = cursor - base
        if offset > 0xFFFF or cursor + 2 + len(record) * width > end:
            raise ValueError("object animation record exceeds table")
        struct.pack_into("<H", output, base + 2 * index, offset)
        struct.pack_into("<H", output, cursor, len(record))
        cursor += 2
        for item in record:
            if width == 6 and (not isinstance(item, list) or len(item) != 3):
                raise ValueError("object animation sprite entry is not three halfwords")
            values = item if width == 6 else (item,)
            if (len(values) != width // 2 or
                    any(type(value) is not int or not 0 <= value <= 0xFFFF
                        for value in values)):
                raise ValueError("object animation halfword is invalid")
            struct.pack_into("<" + "H" * len(values), output, cursor, *values)
            cursor += width
    if cursor != end:
        raise ValueError("object animation table changed its physical extent")


def encode_resource(asset, root):
    start, end = root["start"], root["end"]
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("start"), asset.get("end")) != (start, end)):
        raise ValueError("object animation metadata differs")
    output = bytearray(end - start)
    second_start = root["secondary_table_start"] - start
    struct.pack_into("<HH", output, 0, FLAGS, second_start)
    _encode_table(output, 4, root["first_table_end"] - start,
                  asset.get("first_records"), 6, root["first_entry_count"])
    _encode_table(output, second_start, len(output),
                  asset.get("secondary_records"), 2,
                  root["secondary_entry_count"])
    return bytes(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--catalog", type=Path,
                        default=Path(__file__).resolve().parents[1] /
                        "config/object-animation-roots.json")
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    root_dir = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output == root_dir or root_dir in output.parents:
        parser.error("extracted assets must be outside the source tree")
    rom = args.rom.read_bytes()
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    catalog = load_catalog(args.catalog)
    output.mkdir(parents=True, exist_ok=True)
    rows = []
    for root in catalog["roots"]:
        asset = decode_resource(rom, root)
        rebuilt = encode_resource(asset, root)
        if rebuilt != rom[root["start"]:root["end"]]:
            raise ValueError("object animation roundtrip differs from retail")
        name = f"{root['start']:08x}.json"
        (output / name).write_text(json.dumps(asset, indent=2) + "\n")
        rows.append({"start": root["start"], "end": root["end"],
                     "file": name, "sha256": hashlib.sha256(rebuilt).hexdigest()})
    (output / "manifest.json").write_text(json.dumps({
        "schema_version": 1, "reference_sha256": ROM_SHA256,
        "roots": rows}, indent=2) + "\n")
    print(json.dumps({"roots": len(rows), "bytes": sum(
        row["end"] - row["start"] for row in rows),
        "literal_anchors": sum(len(root["literal_offsets"])
                               for root in catalog["roots"])}))


if __name__ == "__main__":
    main()
