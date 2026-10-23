#!/usr/bin/env python3
"""Export retail-bounded object animation placement rows.

The first bank is bounded by its pointer/count tables and callback consumer.
Other runs remain conservative shape-and-anchor candidates; their individual
runtime reachability is unproven.
"""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0x3954B8
END = 0x3A832C
ROW_BYTES = 24
EXPECTED_RUNS = 144
EXPECTED_ROWS = 619
EXPECTED_BYTES = EXPECTED_ROWS * ROW_BYTES
EXTENDED_RUNS = 203
EXTENDED_ROWS = 678
EXTENDED_BYTES = EXTENDED_ROWS * ROW_BYTES
COUNTED_BANK_START = 0x3958B4
COUNTED_POINTER_TABLE = 0x395A4C
COUNTED_COUNT_TABLE = 0x395AA8
COUNTED_SLOT_COUNT = 23
COUNTED_CONSUMER = 0x080E125E
COUNTED_CALLBACK = 0x080D4DED


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def roots_from_catalog():
    catalog = json.loads((ROOT / "config/unclassified-object-assets.json").read_text())
    if (catalog.get("reference_sha256") != ROM_SHA256 or
            catalog.get("resource_count") != 199):
        raise ValueError("object animation root catalog differs")
    return {row["rom_start"] for row in catalog["resources"]}


def row_shape(rom, offset, roots):
    root, field_04, _, _, field_10, _ = struct.unpack_from("<6I", rom, offset)
    return (root - 0x08000000 in roots and field_04 >> 16 == 1 and
            (field_10 & 0xFFFF) in (6, 7, 8, 9) and
            field_10 >> 16 in (0, 32, 0x8000, 0x1000, 0x40))


def counted_bank(rom):
    """Resolve the first bank from every pointer/count slot that owns rows."""
    base_pointer = struct.unpack_from("<I", rom, COUNTED_POINTER_TABLE)[0]
    if base_pointer != 0x08000000 + COUNTED_BANK_START:
        raise ValueError("counted placement table base differs")

    covered = set()
    pointers = []
    for slot in range(COUNTED_SLOT_COUNT):
        pointer = struct.unpack_from("<I", rom,
                                     COUNTED_POINTER_TABLE + slot * 4)[0]
        count = rom[COUNTED_COUNT_TABLE + slot]
        if pointer == 0:
            if count != 0:
                raise ValueError("null placement pointer has a nonzero count")
            pointers.append((slot, pointer, count, None))
            continue
        row_offset = pointer - 0x08000000
        if (row_offset < COUNTED_BANK_START or
                row_offset >= COUNTED_POINTER_TABLE or
                (row_offset - COUNTED_BANK_START) % ROW_BYTES or count == 0):
            raise ValueError("counted placement pointer is outside its row bank")
        first = (row_offset - COUNTED_BANK_START) // ROW_BYTES
        end = first + count
        if end * ROW_BYTES + COUNTED_BANK_START > COUNTED_POINTER_TABLE:
            raise ValueError("placement pointer/count exceeds its bank")
        covered.update(range(first, end))
        pointers.append((slot, pointer, count, first))

    row_count = (COUNTED_POINTER_TABLE - COUNTED_BANK_START) // ROW_BYTES
    if ((COUNTED_POINTER_TABLE - COUNTED_BANK_START) % ROW_BYTES or
            covered != set(range(row_count)) or row_count != 17):
        raise ValueError("pointer/count slots do not cover the 17-row bank")
    if ((pointers[21][1], pointers[21][2], pointers[21][3]) !=
            (0x08000000 + 0x3959EC, 2, 13) or
            (pointers[22][1], pointers[22][2], pointers[22][3]) !=
            (0x08000000 + 0x395A1C, 2, 15)):
        raise ValueError("terminal placement pointer/count slots differ")

    roots = roots_from_catalog()
    addresses = list(range(COUNTED_BANK_START, COUNTED_POINTER_TABLE, ROW_BYTES))
    if any(struct.unpack_from("<I", rom, offset)[0] - 0x08000000 not in roots
           for offset in addresses):
        raise ValueError("counted placement row references an unknown animation root")
    return addresses


def select_runs(rom):
    roots = roots_from_catalog()
    counted_addresses = counted_bank(rom)
    counted_start = counted_addresses[0]
    counted_end = counted_addresses[-1] + ROW_BYTES
    candidates = [offset for offset in range(START, END - ROW_BYTES + 1, 4)
                  if not counted_start <= offset < counted_end
                  if row_shape(rom, offset, roots)]
    runs = []
    current = []
    for offset in candidates:
        if current and offset != current[-1] + ROW_BYTES:
            runs.append(current)
            current = []
        current.append(offset)
    if current:
        runs.append(current)
    selected = [(counted_addresses, [COUNTED_POINTER_TABLE])]
    for run in runs:
        if len(run) < 2:
            continue
        needle = struct.pack("<I", 0x08000000 + run[0])
        anchors = []
        position = 0
        while (position := rom.find(needle, position)) != -1:
            if not run[0] <= position < run[-1] + ROW_BYTES:
                anchors.append(position)
            position += 1
        if not anchors:
            continue
        selected.append((run, anchors))
    selected.sort(key=lambda row: row[0][0])
    if (len(selected) != EXPECTED_RUNS or
            sum(len(run) for run, _ in selected) != EXPECTED_ROWS or
            any(first[-1] + ROW_BYTES > second[0]
                for (first, _), (second, _) in zip(selected, selected[1:]))):
        raise ValueError("placement run selection differs from pinned retail")
    return selected


def decode_row(rom, offset):
    words = struct.unpack_from("<I10H", rom, offset)
    return {"animation_root_rom_offset": words[0] - 0x08000000,
            "fields_u16_04_to_16": list(words[1:])}


def encode_run(manifest, run, verify_retail=True):
    if (manifest.get("reference_sha256") != ROM_SHA256 or
            manifest.get("schema_version") != 1 or
            run["end"] - run["start"] != len(run["rows"]) * ROW_BYTES):
        raise ValueError("placement run boundary differs")
    roots = roots_from_catalog()
    output = bytearray()
    for row in run["rows"]:
        root = row["animation_root_rom_offset"]
        fields = row["fields_u16_04_to_16"]
        if (type(root) is not int or root not in roots or
                not isinstance(fields, list) or len(fields) != 10 or
                any(type(value) is not int or not 0 <= value <= 0xFFFF
                    for value in fields)):
            raise ValueError("placement row fields differ")
        output += struct.pack("<I10H", 0x08000000 + root, *fields)
    if (len(output) != run["end"] - run["start"] or
            (verify_retail and sha256(output) != run["source_sha256"])):
        raise ValueError("placement run differs from retail")
    return bytes(output)


def validate_counted_additions(rom, owner_manifest):
    """Validate normalized consumer owners and return their one-row runs."""
    if (owner_manifest.get("schema_version") != 1 or
            owner_manifest.get("reference_sha256") != ROM_SHA256 or
            len(owner_manifest.get("runs", [])) != EXTENDED_RUNS - EXPECTED_RUNS or
            sum(row.get("end", -1) - row.get("start", -1)
                for row in owner_manifest.get("runs", [])) !=
            EXTENDED_BYTES - EXPECTED_BYTES):
        raise ValueError("counted placement ownership manifest layout differs")

    additions = []
    for source_run in owner_manifest["runs"]:
        start, end = source_run.get("start"), source_run.get("end")
        rows, owners = source_run.get("rows"), source_run.get("counted_owners")
        if (type(start) is not int or type(end) is not int or
                start < START or end > END or (start - START) % 4 or
                end - start != ROW_BYTES or not isinstance(rows, list) or
                len(rows) != 1 or not isinstance(owners, list) or not owners):
            raise ValueError("counted placement run boundary or owner differs")
        normalized_owners = []
        for owner in owners:
            array_start = owner.get("array_start")
            row_index = owner.get("row_index")
            count = owner.get("count")
            call_site = owner.get("call_site")
            source_hash = owner.get("source_sha256")
            if (type(array_start) is not int or type(row_index) is not int or
                    type(count) is not int or type(call_site) is not int or
                    count <= 0 or not 0 <= row_index < count or
                    array_start + row_index * ROW_BYTES != start or
                    array_start < START or array_start + count * ROW_BYTES > END or
                    "source" in owner or
                    not isinstance(source_hash, str) or len(source_hash) != 64):
                raise ValueError("counted placement owner relation differs")
            normalized_owners.append({
                "call_site": call_site, "array_start": array_start,
                "count": count, "row_index": row_index,
                "source_sha256": source_hash,
            })
        run = {
            "start": start, "end": end,
            "source_sha256": source_run.get("source_sha256"),
            "rows": rows,
            "selection_basis": "consumer-counted placement row owner",
            "counted_owners": normalized_owners,
        }
        if encode_run(owner_manifest, run) != rom[start:end]:
            raise ValueError("counted placement run differs from retail")
        additions.append(run)

    additions.sort(key=lambda row: row["start"])
    if (len(additions) != EXTENDED_RUNS - EXPECTED_RUNS or
            sum(row["end"] - row["start"] for row in additions) !=
            EXTENDED_BYTES - EXPECTED_BYTES or
            any(left["end"] > right["start"]
                for left, right in zip(additions, additions[1:]))):
        raise ValueError("counted placement additions overlap or have wrong size")
    return additions


def read_counted_additions(rom, ownership_manifest, expected_sha256):
    """Validate a pinned, path-free owner list and return its one-row runs."""
    if ownership_manifest is None:
        raise ValueError("counted placement ownership manifest is required")
    ownership_bytes = Path(ownership_manifest).resolve().read_bytes()
    if sha256(ownership_bytes) != expected_sha256:
        raise ValueError("counted placement ownership manifest hash differs")
    return validate_counted_additions(rom, json.loads(ownership_bytes))


def normalize_counted_owner_manifest(rom, ownership_manifest,
                                     expected_input_sha256):
    """Strip machine-local source paths while retaining a pinned source digest."""
    if ownership_manifest is None:
        raise ValueError("counted placement ownership manifest is required")
    source_bytes = Path(ownership_manifest).resolve().read_bytes()
    if sha256(source_bytes) != expected_input_sha256:
        raise ValueError("counted placement source manifest hash differs")
    owner_manifest = json.loads(source_bytes)
    normalized = json.loads(json.dumps(owner_manifest))
    for run in normalized.get("runs", []):
        for owner in run.get("counted_owners", []):
            owner.pop("source", None)
    validate_counted_additions(rom, normalized)
    normalized_bytes = (json.dumps(normalized, indent=2) + "\n").encode()
    return normalized, normalized_bytes, sha256(normalized_bytes)


def export(rom, output_dir, ownership_manifest=None,
           expected_ownership_sha256=None,
           expected_normalized_ownership_sha256=None):
    if len(rom) != 0x1000000 or sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output_dir = output_dir.resolve()
    if output_dir == ROOT or ROOT in output_dir.parents:
        raise ValueError("placement assets must be outside the source tree")
    runs = []
    for addresses, anchors in select_runs(rom):
        start = addresses[0]
        end = addresses[-1] + ROW_BYTES
        source = rom[start:end]
        record = {"start": start, "end": end,
                  "source_sha256": sha256(source), "anchor_offsets": anchors,
                  "rows": [decode_row(rom, offset) for offset in addresses]}
        if start == COUNTED_BANK_START:
            record.update({
                "selection_basis": "consumer-counted pointer/count table",
                "consumer_thumb": f"0x{COUNTED_CONSUMER:08x}",
                "callback_thumb": f"0x{COUNTED_CALLBACK:08x}",
                "pointer_table_offset": COUNTED_POINTER_TABLE,
                "count_table_offset": COUNTED_COUNT_TABLE,
                "covered_row_count": len(addresses),
                "terminal_slots": [
                    {"slot": 21, "row_index": 13, "count": 2},
                    {"slot": 22, "row_index": 15, "count": 2},
                ],
            })
        else:
            record["selection_basis"] = "shape with external pointer anchor"
        runs.append(record)
    ownership_sha256 = None
    if expected_ownership_sha256 is not None:
        owner_manifest, owner_bytes, owner_sha256 = normalize_counted_owner_manifest(
            rom, ownership_manifest, expected_ownership_sha256)
        if (expected_normalized_ownership_sha256 is not None and
                owner_sha256 != expected_normalized_ownership_sha256):
            raise ValueError("normalized counted placement manifest hash differs")
        runs.extend(validate_counted_additions(rom, owner_manifest))
        ownership_sha256 = expected_ownership_sha256
        normalized_ownership_sha256 = owner_sha256
        runs.sort(key=lambda row: row["start"])
        if any(left["end"] > right["start"]
               for left, right in zip(runs, runs[1:])):
            raise ValueError("placement runs overlap")
    selected_rows = sum(len(run["rows"]) for run in runs)
    selected_bytes = sum(run["end"] - run["start"] for run in runs)
    expected = ((EXTENDED_RUNS, EXTENDED_ROWS, EXTENDED_BYTES)
                if ownership_sha256 is not None else
                (EXPECTED_RUNS, EXPECTED_ROWS, EXPECTED_BYTES))
    if (len(runs), selected_rows, selected_bytes) != expected:
        raise ValueError("placement family totals differ")
    manifest = {"schema_version": 1, "reference_sha256": ROM_SHA256,
                "source_range": [START, END], "row_bytes": ROW_BYTES,
                "selected_runs": len(runs), "selected_rows": selected_rows,
                "selected_bytes": selected_bytes, "runs": runs,
                "scope": "The first 17-row bank is bounded by its retail pointer/count tables. Existing shape-and-anchor runs retain their prior selection basis. Additional one-row runs are admitted only through the SHA-pinned counted-owner manifest; natural execution is not claimed and fields beyond the root remain neutral."}
    if ownership_sha256 is not None:
        manifest["counted_owner_input_sha256"] = ownership_sha256
        manifest["counted_owner_manifest_sha256"] = normalized_ownership_sha256
    for run in runs:
        if encode_run(manifest, run) != rom[run["start"]:run["end"]]:
            raise ValueError("placement run does not round-trip")
    output_dir.mkdir(parents=True, exist_ok=True)
    if ownership_sha256 is not None:
        (output_dir / "counted-owners.json").write_bytes(owner_bytes)
    path = output_dir / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"runs": len(runs), "rows": selected_rows,
            "selected_bytes": selected_bytes,
            "counted_owner_input_sha256": ownership_sha256,
            "counted_owner_manifest_sha256": (
                normalized_ownership_sha256 if ownership_sha256 is not None else None),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
