#!/usr/bin/env python3
"""Export the retail graphics object dispatch descriptors as editable fields."""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
ROM_SIZE = 0x1000000
TABLES = (("primary", 0x3947D8, 341, 1), ("extension", 0x395280, 71, 342))
END = 0x3954B8
CALLER_LITERALS = ((0x0D355C, 0x3947D8), (0x0D35BC, 0x395280),
                   (0x0D3BC4, 0x3947D8))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def validate_manifest(manifest):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["start"] != TABLES[0][1] or manifest["end"] != END or
            len(manifest["tables"]) != len(TABLES)):
        raise ValueError("graphics dispatch revision or boundary differs")


def encode(manifest, verify_hash=True):
    validate_manifest(manifest)
    result = bytearray()
    for table, (label, start, count, first_id) in zip(manifest["tables"], TABLES):
        if (table["label"] != label or table["start"] != start or
                table["end"] != start + 8 * count or
                table["first_id"] != first_id or len(table["records"]) != count):
            raise ValueError(f"{label}: descriptor table shape differs")
        encoded = bytearray()
        for index, record in enumerate(table["records"]):
            callback = record["callback_thumb_address"]
            size_field = record["size_field"]
            auxiliary_field = record["auxiliary_field"]
            if (record["id"] != first_id + index or
                    type(callback) is not int or
                    (callback != 0 and not ROM_BASE <= callback < ROM_BASE + ROM_SIZE)
                    or (callback != 0 and not callback & 1) or
                    type(size_field) is not int or not 0 <= size_field <= 0xFFFF or
                    type(auxiliary_field) is not int or not 0 <= auxiliary_field <= 0xFFFF):
                raise ValueError(f"{label}: invalid descriptor {index}")
            encoded += struct.pack("<IHH", callback, size_field, auxiliary_field)
        if verify_hash and sha256(encoded) != table["source_sha256"]:
            raise ValueError(f"{label}: descriptors differ from retail")
        result += encoded
    if (len(result) != END - TABLES[0][1] or
            (verify_hash and sha256(result) != manifest["source_sha256"])):
        raise ValueError("graphics object dispatch bank differs from retail")
    return bytes(result)


def export(rom, output_dir):
    if len(rom) != ROM_SIZE or sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output_dir = output_dir.resolve()
    if output_dir.is_relative_to(ROOT):
        raise ValueError("graphics dispatch output must be outside the source tree")
    for site, target in CALLER_LITERALS:
        if struct.unpack_from("<I", rom, site)[0] != ROM_BASE + target:
            raise ValueError(f"caller literal at 0x{site:x} differs")
    if TABLES[0][1] + TABLES[0][2] * 8 != TABLES[1][1] or TABLES[1][1] + TABLES[1][2] * 8 != END:
        raise ValueError("graphics dispatch tables do not partition the bank")
    tables = []
    for label, start, count, first_id in TABLES:
        source = rom[start:start + 8 * count]
        records = []
        for index, (callback, size_field, auxiliary_field) in enumerate(
                struct.iter_unpack("<IHH", source)):
            if callback and (not ROM_BASE <= callback < ROM_BASE + ROM_SIZE or not callback & 1):
                raise ValueError(f"{label}: callback {index} is not a Thumb ROM pointer")
            records.append({"id": first_id + index,
                            "callback_thumb_address": callback,
                            "size_field": size_field,
                            "auxiliary_field": auxiliary_field})
        tables.append({"label": label, "start": start, "end": start + len(source),
                       "first_id": first_id, "source_sha256": sha256(source),
                       "records": records})
    manifest = {"reference_sha256": ROM_SHA256,
                "start": TABLES[0][1], "end": END,
                "source_sha256": sha256(rom[TABLES[0][1]:END]),
                "caller_literal_sites": [site for site, _ in CALLER_LITERALS],
                "tables": tables,
                "scope_note": "Retail dispatches by ID and reads callback, +4, and +6. Field roles and reachability are incomplete."}
    if encode(manifest) != rom[TABLES[0][1]:END]:
        raise ValueError("graphics dispatch descriptors do not round-trip")
    output_dir.mkdir(parents=True, exist_ok=True)
    path = output_dir / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"records": sum(len(table["records"]) for table in tables),
            "source_bytes": END - TABLES[0][1],
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
