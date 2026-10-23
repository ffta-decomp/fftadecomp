#!/usr/bin/env python3
"""Export the offset-indexed graphics containers before the LZ77 records."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_pointer_lz77_records import POINTER_START, POINTER_END, ROM_BASE, ROM_SHA256

BANK_START = 0x8ec8e0
BANK_END = 0x8f4674
ROOT_COUNT = 44


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_u16(values):
    if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("graphics container halfword differs")
    return b"".join(value.to_bytes(2, "little") for value in values)


def encode_root(root, source_dir):
    fields = json.loads((source_dir / "records" / root["file"]).read_text())
    containers = fields["containers"]
    if len(containers) != root["container_count"]:
        raise ValueError("graphics container count differs")
    output = bytearray()
    padding_bytes = 0
    subrecord_count = 0
    timeline_values = 0
    for container in containers:
        flags = container["flags"]
        subrecords = container["subrecords"]
        timeline = container["timeline"]
        if type(flags) is not int or flags not in (12, 14) or not 1 <= len(subrecords) <= 128:
            raise ValueError("graphics container flags or subrecord count differ")
        encoded_subrecords = [encode_u16(values) for values in subrecords]
        if any(not data for data in encoded_subrecords):
            raise ValueError("graphics container has an empty subrecord")
        offsets = []
        cursor = 2 * len(subrecords)
        for data in encoded_subrecords:
            offsets.append(cursor)
            cursor += len(data)
        relative_end = 4 + cursor
        body = encode_u16(offsets) + b"".join(encoded_subrecords)
        if len(body) != cursor or relative_end > 0xffff:
            raise ValueError("graphics container offset table differs")
        encoded = encode_u16([flags, relative_end]) + body
        encoded += encode_u16([len(timeline)] + timeline)
        padding = (-len(encoded)) % 4
        encoded += bytes(padding)
        output += encoded
        padding_bytes += padding
        subrecord_count += len(subrecords)
        timeline_values += len(timeline)
    if (len(output) != root["end"] - root["start"] or
            padding_bytes != root["padding_bytes"] or
            subrecord_count != root["subrecord_count"] or
            timeline_values != root["timeline_values"] or
            sha256(output) != root["source_sha256"]):
        raise ValueError(f"graphics container root differs at 0x{root['start']:08x}")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    record_dir = output / "records"
    record_dir.mkdir(exist_ok=True)
    pointers = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if BANK_START <= target < BANK_END:
            pointers.setdefault(target, []).append(site)
    starts = sorted(pointers)
    if len(starts) != ROOT_COUNT or starts[0] != BANK_START:
        raise ValueError("graphics container root pointers differ")
    roots = []
    for index, start in enumerate(starts):
        end = starts[index + 1] if index + 1 < len(starts) else BANK_END
        cursor = start
        containers = []
        padding_bytes = 0
        subrecord_count = 0
        timeline_values = 0
        while cursor < end:
            if cursor % 4 or cursor + 8 > end:
                raise ValueError("graphics container boundary is not word-aligned")
            flags = int.from_bytes(rom[cursor:cursor + 2], "little")
            relative_end = int.from_bytes(rom[cursor + 2:cursor + 4], "little")
            body_start = cursor + 4
            body_end = cursor + relative_end
            if flags not in (12, 14) or not 8 <= relative_end <= end - cursor - 2:
                raise ValueError("graphics container header differs")
            first_offset = int.from_bytes(rom[body_start:body_start + 2], "little")
            if first_offset % 2 or not 1 <= first_offset // 2 <= 128 or body_start + first_offset > body_end:
                raise ValueError("graphics container offset-table count differs")
            count = first_offset // 2
            offsets = [int.from_bytes(rom[pos:pos + 2], "little")
                       for pos in range(body_start, body_start + first_offset, 2)]
            bounds = offsets + [body_end - body_start]
            if (offsets[0] != first_offset or offsets != sorted(offsets) or
                    any(value % 2 or value >= body_end - body_start for value in offsets) or
                    any(bounds[j + 1] <= bounds[j] or (bounds[j + 1] - bounds[j]) % 2
                        for j in range(count))):
                raise ValueError("graphics container subrecord boundaries differ")
            subrecords = []
            for first, last in zip(bounds, bounds[1:]):
                subrecords.append([int.from_bytes(rom[pos:pos + 2], "little")
                                   for pos in range(body_start + first, body_start + last, 2)])
            timeline_count = int.from_bytes(rom[body_end:body_end + 2], "little")
            timeline_end = body_end + 2 + 2 * timeline_count
            next_cursor = (timeline_end + 3) & ~3
            if next_cursor > end or rom[timeline_end:next_cursor] != bytes(next_cursor - timeline_end):
                raise ValueError("graphics container timeline or alignment differs")
            timeline = [int.from_bytes(rom[pos:pos + 2], "little")
                        for pos in range(body_end + 2, timeline_end, 2)]
            containers.append({"flags": flags, "subrecords": subrecords, "timeline": timeline})
            padding_bytes += next_cursor - timeline_end
            subrecord_count += count
            timeline_values += timeline_count
            cursor = next_cursor
        if cursor != end:
            raise ValueError("graphics container does not end at the next pointer")
        file_name = f"containers-0x{start:06x}.json"
        (record_dir / file_name).write_text(json.dumps({"containers": containers}, indent=2) + "\n")
        root = {"start": start, "end": end, "pointer_sites": pointers[start],
                "container_count": len(containers), "subrecord_count": subrecord_count,
                "timeline_values": timeline_values, "padding_bytes": padding_bytes,
                "file": file_name, "source_sha256": sha256(rom[start:end])}
        if encode_root(root, output) != rom[start:end]:
            raise ValueError("graphics container root does not round-trip")
        roots.append(root)
    manifest = {"reference_sha256": ROM_SHA256,
                "pointer_table_window": [POINTER_START, POINTER_END],
                "constructor": 0x080d4b64, "roots": roots,
                "root_count": len(roots),
                "container_count": sum(root["container_count"] for root in roots),
                "subrecord_count": sum(root["subrecord_count"] for root in roots),
                "timeline_values": sum(root["timeline_values"] for root in roots),
                "source_bytes": sum(root["end"] - root["start"] for root in roots),
                "padding_bytes": sum(root["padding_bytes"] for root in roots),
                "scope_note": "The offset index and halfword boundaries rebuild exactly. The inner subrecord fields and rendered sprite arrangement are not yet assigned semantics."}
    if (manifest["container_count"], manifest["subrecord_count"],
            manifest["timeline_values"], manifest["source_bytes"],
            manifest["padding_bytes"]) != (94, 520, 590, 32148, 68):
        raise ValueError("graphics container coverage differs")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"root_count": len(roots), "container_count": manifest["container_count"],
            "subrecord_count": manifest["subrecord_count"],
            "timeline_values": manifest["timeline_values"],
            "source_bytes": manifest["source_bytes"], "padding_bytes": manifest["padding_bytes"],
            "manifest_sha256": sha256(path.read_bytes())}


def root_entry(manifest, offset):
    matches = [root for root in manifest["roots"] if root["start"] == offset]
    if len(matches) != 1:
        raise ValueError("graphics container root is not unique")
    return matches[0]


def root_source_file(manifest, offset, source_dir):
    return source_dir / "records" / root_entry(manifest, offset)["file"]


def reconstruct_root(manifest, source_dir, offset):
    return encode_root(root_entry(manifest, offset), source_dir)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("graphics container export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
