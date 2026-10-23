"""Typed codec for pointer-rooted nested counted BGR555 palettes."""

import hashlib
import json
import struct
from pathlib import Path

from extract_pointer_lz77_records import ROM_BASE, ROM_SHA256

START = 0x8E9C0C
END = 0x8EC8E0
POINTER_START = 0x390000
POINTER_END = 0x3B0000


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode_record(data, start, limit):
    if start + 2 > limit:
        raise ValueError("palette header leaves pointer root")
    group_count, color_count = data[start:start + 2]
    if not 1 <= group_count <= 16 or not 1 <= color_count <= 15:
        raise ValueError("counted palette dimensions differ")
    payload_end = start + 2 + 2 * group_count * color_count
    aligned_end = (payload_end + 3) & ~3
    if aligned_end > limit or any(data[payload_end:aligned_end]):
        raise ValueError("counted palette payload or alignment leaves pointer root")
    words = struct.unpack_from("<" + "H" * (group_count * color_count), data,
                               start + 2)
    groups = []
    for group in range(group_count):
        row = []
        for word in words[group * color_count:(group + 1) * color_count]:
            row.append({"red": word & 31, "green": (word >> 5) & 31,
                        "blue": (word >> 10) & 31, "high_bit": word >> 15})
        groups.append(row)
    return {"groups": groups, "padding_bytes": aligned_end - payload_end}, aligned_end


def encode_record(fields):
    groups = fields.get("groups")
    if not isinstance(groups, list) or not 1 <= len(groups) <= 16:
        raise ValueError("counted palette group count differs")
    color_count = len(groups[0]) if groups and isinstance(groups[0], list) else 0
    if not 1 <= color_count <= 15 or any(not isinstance(row, list) or
                                         len(row) != color_count for row in groups):
        raise ValueError("counted palette color count differs")
    output = bytearray((len(groups), color_count))
    for group in groups:
        for color in group:
            if (not isinstance(color, dict) or
                    set(color) != {"red", "green", "blue", "high_bit"} or
                    any(type(color[key]) is not int for key in color)):
                raise ValueError("counted palette color schema differs")
            if (any(not 0 <= color[channel] <= 31
                    for channel in ("red", "green", "blue")) or
                    color["high_bit"] not in (0, 1)):
                raise ValueError("counted palette color channel differs")
            word = (color["red"] | color["green"] << 5 |
                    color["blue"] << 10 | color["high_bit"] << 15)
            output.extend(struct.pack("<H", word))
    padding = fields.get("padding_bytes")
    if type(padding) is not int or padding != (-len(output)) % 4:
        raise ValueError("counted palette alignment differs")
    output.extend(bytes(padding))
    return bytes(output)


def encode_bank(manifest, directory):
    if (manifest.get("schema_version") != 1 or
            manifest.get("reference_sha256") != ROM_SHA256 or
            (manifest.get("start"), manifest.get("end_exclusive")) != (START, END) or
            manifest.get("record_count") != 278 or manifest.get("root_count") != 223 or
            len(manifest.get("roots", [])) != 223 or
            len(manifest.get("records", [])) != 278):
        raise ValueError("nested palette bank descriptor differs")
    output = bytearray()
    expected = START
    records_by_start = {row["start"]: row for row in manifest["records"]}
    if len(records_by_start) != len(manifest["records"]):
        raise ValueError("duplicate nested palette record")
    for root in manifest["roots"]:
        if root.get("start") != expected or root.get("end_exclusive", 0) <= expected:
            raise ValueError("nested palette root boundaries are not contiguous")
        cursor = root["start"]
        for record_start in root.get("record_starts", []):
            record = records_by_start.get(record_start)
            if record is None or record.get("root") != root["start"] or record_start != cursor:
                raise ValueError("nested palette record ownership differs")
            path = (directory / record["file"]).resolve()
            if not path.is_relative_to(directory.resolve()) or not path.is_file():
                raise ValueError("nested palette record source is missing")
            encoded = encode_record(json.loads(path.read_text()))
            if (len(encoded) != record["end_exclusive"] - record_start or
                    sha256(encoded) != record.get("source_sha256")):
                raise ValueError("nested palette record hash or span differs")
            output.extend(encoded)
            cursor += len(encoded)
        if cursor != root["end_exclusive"]:
            raise ValueError("nested palette root is not fully typed")
        expected = cursor
    if (expected != END or len(output) != END - START or
            sum(row["padding_bytes"] for row in manifest["records"]) != 228):
        raise ValueError("nested palette bank extent differs")
    return bytes(output)


def export(rom, output):
    if len(rom) != 0x1000000 or sha256(rom) != ROM_SHA256:
        raise ValueError("expected pinned US retail ROM")
    output = Path(output)
    output.mkdir(parents=True, exist_ok=True)
    pointers = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = struct.unpack_from("<I", rom, site)[0] - ROM_BASE
        if START <= target < END:
            pointers.setdefault(target, []).append(site)
    roots = sorted(pointers)
    if len(roots) != 223:
        raise ValueError("nested palette pointer-root count differs")
    records, root_rows, padding, high_bits = [], [], 0, 0
    for root, root_end in zip(roots, roots[1:] + [END]):
        cursor = root
        record_starts = []
        while cursor < root_end:
            fields, next_record = decode_record(rom, cursor, root_end)
            encoded = encode_record(fields)
            if encoded != rom[cursor:next_record]:
                raise ValueError("nested palette record does not round-trip")
            name = f"palette-{cursor:08x}.json"
            (output / name).write_text(json.dumps(fields, indent=2, sort_keys=True) + "\n")
            records.append({"start": cursor, "end_exclusive": next_record,
                            "root": root, "file": name,
                            "source_sha256": sha256(encoded),
                            "padding_bytes": fields["padding_bytes"]})
            record_starts.append(cursor)
            padding += fields["padding_bytes"]
            high_bits += sum(color["high_bit"] for row in fields["groups"]
                             for color in row)
            cursor = next_record
        if cursor != root_end:
            raise ValueError("nested palette root leaves residual bytes")
        root_rows.append({"start": root, "end_exclusive": root_end,
                          "pointer_sites": pointers[root],
                          "record_starts": record_starts})
    manifest = {"schema_version": 1, "reference_sha256": ROM_SHA256,
                "start": START, "end_exclusive": END,
                "pointer_window": [POINTER_START, POINTER_END],
                "roots": root_rows, "records": records,
                "root_count": len(root_rows), "record_count": len(records),
                "padding_bytes": padding, "high_bit_words": high_bits}
    if padding != 228 or high_bits != 40 or encode_bank(manifest, output) != rom[START:END]:
        raise ValueError("nested palette bank coverage differs")
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n")
    return manifest
