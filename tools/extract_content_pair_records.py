#!/usr/bin/env python3
"""Export pointer-indexed 48-byte entries, byte pairs, and content records."""

import argparse
import hashlib
import json
import struct
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
PAIR_START = 0x54BB30
PAIR_END = 0x54CD7C
ENTRY_START = 0x52A4D0
ENTRY_END = PAIR_START
ENTRY_BYTES = 48
ENTRY_COUNT = 2850
RECORD_BASE = 0x54CD54
RECORD_START = PAIR_END
RECORD_END = 0x55128C
RECORD_COUNT = 442
PAIR_LIST_COUNT = 645
BASE_LITERAL = 0x9F28
POINTER_FIELDS = (("list_a", 16), ("list_b", 28))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def validate_manifest(manifest):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["entry_start"] != ENTRY_START or manifest["entry_end"] != ENTRY_END or
            manifest["entry_count"] != ENTRY_COUNT or
            manifest["pair_start"] != PAIR_START or manifest["pair_end"] != PAIR_END or
            manifest["record_base"] != RECORD_BASE or
            manifest["record_start"] != RECORD_START or
            manifest["record_end"] != RECORD_END or
            manifest["record_count"] != RECORD_COUNT or
            manifest["pair_list_count"] != PAIR_LIST_COUNT):
        raise ValueError("content pair/record revision or boundary differs")


def load_inputs(manifest, source_dir):
    validate_manifest(manifest)
    records = json.loads((source_dir / manifest["records_file"]).read_text())["records"]
    pair_lists = json.loads((source_dir / manifest["pair_lists_file"]).read_text())["pair_lists"]
    if len(records) != RECORD_COUNT or len(pair_lists) != PAIR_LIST_COUNT:
        raise ValueError("content record or pair-list count differs")
    return records, pair_lists


def encode_pairs(manifest, source_dir, verify_hash=True):
    records, pair_lists = load_inputs(manifest, source_dir)
    output = bytearray()
    starts = {}
    last_key = (0, "list_b")
    record_ids = {record["index"] for record in records}
    for entry in pair_lists:
        index, field, pairs = entry["record_index"], entry["field"], entry["pairs"]
        key = (index, field)
        if (type(index) is not int or index not in record_ids or field not in ("list_a", "list_b") or
                key <= last_key or not pairs or any(
                    len(pair) != 2 or any(type(value) is not int or not 0 <= value <= 255
                                       for value in pair) for pair in pairs)):
            raise ValueError("content pair-list order or pair value differs")
        starts[key] = PAIR_START + len(output)
        output += bytes(value for pair in pairs for value in pair)
        last_key = key
    data = bytes(output)
    if len(data) != PAIR_END - PAIR_START or (
            verify_hash and sha256(data) != manifest["pair_sha256"]):
        raise ValueError("content pair bank differs from retail")
    return data, starts


def encode_records(manifest, source_dir, verify_hash=True):
    records, pair_lists = load_inputs(manifest, source_dir)
    _, starts = encode_pairs(manifest, source_dir, verify_hash)
    output = bytearray()
    pair_counts = {(entry["record_index"], entry["field"]): len(entry["pairs"])
                   for entry in pair_lists}
    for expected_index, record in enumerate(records, 1):
        if record["index"] != expected_index:
            raise ValueError("content record index differs")
        first, second, target = (record[key] for key in ("entry_count", "u16_02", "rom_target_04"))
        if (any(type(value) is not int or not 0 <= value <= 0xffff
                for value in (first, second)) or
                not 1 <= first <= 13 or
                type(target) is not int or not 0 <= target < 0x1000000):
            raise ValueError("content record header differs")
        byte_fields = [record[key] for key in ("fields_08_15", "fields_20_27",
                                                  "fields_32_39")]
        if any(len(values) != 8 or any(type(value) is not int or not 0 <= value <= 255
                                       for value in values) for values in byte_fields):
            raise ValueError("content record byte fields differ")
        list_a = starts.get((expected_index, "list_a"))
        list_b = starts.get((expected_index, "list_b"))
        if ((list_b is None) != (byte_fields[0][7] == 0) or
                (list_b is not None and pair_counts[(expected_index, "list_b")] != byte_fields[0][7])):
            raise ValueError("content secondary list count differs")
        output += struct.pack("<HHI8sI8sI8s", first, second, ROM_BASE + target,
                              bytes(byte_fields[0]), ROM_BASE + list_a if list_a is not None else 0,
                              bytes(byte_fields[1]), ROM_BASE + list_b if list_b is not None else 0,
                              bytes(byte_fields[2]))
    data = bytes(output)
    if len(data) != RECORD_END - RECORD_START or (
            verify_hash and sha256(data) != manifest["record_sha256"]):
        raise ValueError("content record bank differs from retail")
    return data


def encode_entries(manifest, source_dir, verify_hash=True):
    records, _ = load_inputs(manifest, source_dir)
    groups = json.loads((source_dir / manifest["entries_file"]).read_text())["groups"]
    if len(groups) != RECORD_COUNT or len(manifest["entry_groups"]) != RECORD_COUNT:
        raise ValueError("content entry group count differs")
    output = bytearray()
    for record, group, reference in zip(records, groups, manifest["entry_groups"]):
        index = record["index"]
        start = ENTRY_START + len(output)
        entries = group["entries"]
        if (group["record_index"] != index or reference["record_index"] != index or
                reference["start"] != start or len(entries) != record["entry_count"] or
                reference["entry_count"] != len(entries) or
                record["rom_target_04"] != start):
            raise ValueError("content entry pointer, count, or boundary differs")
        encoded_group = bytearray()
        for entry in entries:
            fields = (("fields_00_18", 19, 0), ("fields_20_37", 18, 20),
                      ("fields_40_41", 2, 40), ("fields_43_45", 3, 43))
            encoded = bytearray(ENTRY_BYTES)
            for key, count, position in fields:
                values = entry[key]
                if len(values) != count or any(type(value) is not int or not 0 <= value <= 255
                                                   for value in values):
                    raise ValueError("content entry field width or value differs")
                encoded[position:position + count] = bytes(values)
            encoded_group += encoded
        if (len(encoded_group) != reference["size"] or
                (verify_hash and sha256(encoded_group) != reference["sha256"])):
            raise ValueError("content entry group differs from retail")
        output += encoded_group
    data = bytes(output)
    if len(data) != ENTRY_END - ENTRY_START or (
            verify_hash and sha256(data) != manifest["entry_sha256"]):
        raise ValueError("content entry bank differs from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("content pair export must be outside the source tree")
    if (struct.unpack_from("<I", rom, BASE_LITERAL)[0] != ROM_BASE + RECORD_BASE or
            RECORD_START != RECORD_BASE + 40 or
            RECORD_END - RECORD_START != RECORD_COUNT * 40 or
            ENTRY_END - ENTRY_START != ENTRY_COUNT * ENTRY_BYTES):
        raise ValueError("content record code literal or stride differs")
    output.mkdir(parents=True, exist_ok=True)
    records = []
    pointer_order = []
    for index in range(1, RECORD_COUNT + 1):
        offset = RECORD_BASE + index * 40
        first, second, target, fields_a, list_a, fields_b, list_b, fields_c = struct.unpack_from(
            "<HHI8sI8sI8s", rom, offset)
        if not ROM_BASE <= target < ROM_BASE + len(rom):
            raise ValueError("content record target leaves ROM")
        for field, pointer in (("list_a", list_a), ("list_b", list_b)):
            if pointer:
                start = pointer - ROM_BASE
                if not PAIR_START <= start < PAIR_END:
                    raise ValueError("content pair pointer leaves the bounded bank")
                pointer_order.append((index, field, start))
        if not 1 <= first <= 13:
            raise ValueError("content entry count leaves observed range")
        records.append({"index": index, "entry_count": first, "u16_02": second,
                        "rom_target_04": target - ROM_BASE,
                        "fields_08_15": list(fields_a), "fields_20_27": list(fields_b),
                        "fields_32_39": list(fields_c)})
    starts = [start for _, _, start in pointer_order]
    if (len(starts) != PAIR_LIST_COUNT or starts != sorted(set(starts)) or
            starts[0] != PAIR_START):
        raise ValueError("content pair pointers do not cover a unique ordered bank")
    pair_lists = []
    for position, (index, field, start) in enumerate(pointer_order):
        end = starts[position + 1] if position + 1 < len(starts) else PAIR_END
        if end <= start or (end - start) & 1:
            raise ValueError("content pair-list boundary differs")
        data = rom[start:end]
        pair_lists.append({"record_index": index, "field": field,
                           "pairs": [list(data[pos:pos + 2]) for pos in range(0, len(data), 2)]})
        if field == "list_b" and len(data) // 2 != records[index - 1]["fields_08_15"][7]:
            raise ValueError("content secondary list count differs")
    records_file = "records.json"
    pair_lists_file = "pair-lists.json"
    entries_file = "entries.json"
    entry_groups = []
    groups = []
    entry_cursor = ENTRY_START
    for record in records:
        count = record["entry_count"]
        size = count * ENTRY_BYTES
        if record["rom_target_04"] != entry_cursor:
            raise ValueError("content entry pointers do not cover a contiguous 48-byte bank")
        source = rom[entry_cursor:entry_cursor + size]
        entries = []
        for offset in range(0, size, ENTRY_BYTES):
            data = source[offset:offset + ENTRY_BYTES]
            if any(data[position] for position in (19, 38, 39, 42, 46, 47)):
                raise ValueError("content entry reserved fields are nonzero")
            entries.append({"fields_00_18": list(data[:19]),
                            "fields_20_37": list(data[20:38]),
                            "fields_40_41": list(data[40:42]),
                            "fields_43_45": list(data[43:46])})
        groups.append({"record_index": record["index"], "entries": entries})
        entry_groups.append({"record_index": record["index"], "start": entry_cursor,
                             "size": size, "entry_count": count, "sha256": sha256(source)})
        entry_cursor += size
    if entry_cursor != ENTRY_END or sum(group["entry_count"] for group in entry_groups) != ENTRY_COUNT:
        raise ValueError("content entry bank count or end differs")
    (output / records_file).write_text(json.dumps({"records": records}, separators=(",", ":")) + "\n")
    (output / pair_lists_file).write_text(json.dumps({"pair_lists": pair_lists},
                                                     separators=(",", ":")) + "\n")
    (output / entries_file).write_text(json.dumps({"groups": groups}, separators=(",", ":")) + "\n")
    manifest = {"reference_sha256": ROM_SHA256, "entry_start": ENTRY_START,
                "entry_end": ENTRY_END, "entry_count": ENTRY_COUNT,
                "entry_groups": entry_groups, "entries_file": entries_file,
                "entry_sha256": sha256(rom[ENTRY_START:ENTRY_END]),
                "pair_start": PAIR_START,
                "pair_end": PAIR_END, "record_base": RECORD_BASE,
                "record_start": RECORD_START, "record_end": RECORD_END,
                "record_count": RECORD_COUNT, "pair_list_count": PAIR_LIST_COUNT,
                "base_literal": BASE_LITERAL, "records_file": records_file,
                "pair_lists_file": pair_lists_file,
                "pair_sha256": sha256(rom[PAIR_START:PAIR_END]),
                "record_sha256": sha256(rom[RECORD_START:RECORD_END]),
                "caveat": "The ordered pointer pairs, 40-byte record stride, and 48-byte entry counts are established. Entry field meanings and pair meanings remain unknown. Record index zero overlaps the final 40 bytes of the pair bank and is not counted as a record."}
    if (encode_entries(manifest, output) != rom[ENTRY_START:ENTRY_END] or
            encode_pairs(manifest, output)[0] != rom[PAIR_START:PAIR_END] or
            encode_records(manifest, output) != rom[RECORD_START:RECORD_END]):
        raise ValueError("content pair and record export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": RECORD_COUNT, "pair_lists": PAIR_LIST_COUNT,
            "entries": ENTRY_COUNT,
            "source_bytes": ENTRY_END - ENTRY_START + PAIR_END - PAIR_START + RECORD_END - RECORD_START,
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
