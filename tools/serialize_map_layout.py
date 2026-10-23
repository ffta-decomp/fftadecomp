#!/usr/bin/env python3
"""Serialize map layout payloads using only external structured export files.

This reconstructs decoded map payloads, not retail compressed source streams.
The input is the manifest and asset JSON files written by
extract_map_layout.py --export-dir; no ROM is opened by this script.
"""

import argparse
import hashlib
import json
from pathlib import Path


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(value):
    if type(value) is not int or not 0 <= value <= 0xffff:
        raise ValueError("map halfword value is out of range")
    return value.to_bytes(2, "little")


def bytes_from_hex(value):
    if not isinstance(value, str):
        raise ValueError("map byte field is not hex text")
    return bytes.fromhex(value)


def serialize_structure(structure):
    kind = structure["kind"]
    output = bytearray()
    if kind == "arrangement":
        flags = structure["flags"]
        header_byte_2 = structure["header_byte_2"]
        has_ram_binding = "target_ram_base" in structure
        if has_ram_binding and (
                structure["target_ram_base"], structure.get("target_bytes"),
                structure.get("write_unit_bytes"), structure.get("bank_bytes"),
                structure.get("row_bytes")) != (0x020091A0, 0x4000, 4, 0x2000, 0x80):
            raise ValueError("arrangement RAM binding differs from the observed consumer")
        if any(type(value) is not int or not 0 <= value <= 255
               for value in (flags, header_byte_2)):
            raise ValueError("arrangement header byte is out of range")
        output.extend(u16(structure["tile_format_offset"]))
        output.extend((header_byte_2, flags))
        ids_are_u16 = bool(flags & 0x40)
        for run in structure["runs"]:
            tile_ids = run["tile_ids"]
            if len(tile_ids) != run["count"] or len(tile_ids) > 255:
                raise ValueError("arrangement run count differs from its tile IDs")
            destination = run["destination"]
            if has_ram_binding and (
                    destination & 3 or destination + 4 * len(tile_ids) > 0x4000 or
                    destination < 0x2000 < destination + 4 * len(tile_ids) or
                    destination % 0x80 + 4 * len(tile_ids) > 0x80 or
                    run.get("ram_destination") != 0x020091A0 + destination or
                    run.get("bank") != destination // 0x2000 or
                    run.get("row") != (destination % 0x2000) // 0x80 or
                    run.get("word_column") != (destination % 0x80) // 4):
                raise ValueError("arrangement run RAM destination differs")
            output.extend(u16(run["destination"]))
            output.append(len(tile_ids))
            for tile_id in tile_ids:
                if ids_are_u16:
                    output.extend(u16(tile_id))
                elif type(tile_id) is int and 0 <= tile_id <= 255:
                    output.append(tile_id)
                else:
                    raise ValueError("8-bit arrangement tile ID is out of range")
        output.extend(b"\0\0")
        output.extend(bytes_from_hex(structure["tail_hex"]))
    elif kind in ("terrain", "clipping"):
        target = {"terrain": (0x02007CB0, 0x200),
                  "clipping": (0x0200D1A0, 0x2000)}[kind]
        has_ram_binding = "target_ram_base" in structure
        if has_ram_binding and (structure["target_ram_base"],
                                structure.get("target_bytes"),
                                structure.get("write_unit_bytes")) != (*target, 2):
            raise ValueError("sparse RAM binding differs from the observed consumer")
        for run in structure["runs"]:
            data = bytes_from_hex(run["data_hex"])
            if len(data) % 2:
                raise ValueError("terrain or clipping run is not halfword aligned")
            destination = run["destination"]
            if has_ram_binding:
                if (destination & 1 or destination + len(data) > target[1] or
                        run.get("ram_destination") != target[0] + destination):
                    raise ValueError("sparse run RAM destination differs")
                if kind == "clipping" and (
                        run.get("bank") != destination // 0x1000 or
                        run.get("row") != (destination % 0x1000) // 64 or
                        run.get("halfword_column") != (destination % 64) // 2 or
                        destination < 0x1000 < destination + len(data) or
                        destination % 64 + len(data) > 64):
                    raise ValueError("clipping run bank or row differs")
            output.extend(u16(destination))
            output.extend(u16(len(data)))
            output.extend(data)
        output.extend(b"\0\0\0\0")
        output.extend(bytes_from_hex(structure["tail_hex"]))
    elif kind == "palette":
        for bank in structure["banks_bgr555"]:
            if len(bank) != 16:
                raise ValueError("palette bank must contain 16 BGR555 colors")
            for color in bank:
                output.extend(u16(color))
    else:
        raise ValueError(f"unsupported map payload kind {kind}")
    return bytes(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input-dir", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    parser.add_argument("--allow-edits", action="store_true",
                        help="serialize changed fields while retaining payload lengths")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    input_dir = args.input_dir.resolve()
    output_dir = args.output_dir.resolve()
    if input_dir.is_relative_to(root) or output_dir.is_relative_to(root):
        raise SystemExit("Map layout payloads must stay outside the source tree")
    manifest = json.loads((input_dir / "manifest.json").read_text())
    if manifest["map_count"] != 162 or len(manifest["maps"]) != 162:
        raise ValueError("map layout export does not cover 162 maps")
    asset_names = sorted({reference["asset"]
                          for row in manifest["maps"]
                          for field, reference in row.items() if field != "map"})
    if len(asset_names) != manifest["asset_count"]:
        raise ValueError("map layout asset count differs from manifest")
    overlay_names = sorted({record["overlay_asset"]
                            for record in manifest["redirect_wrappers"]
                            if "overlay_asset" in record})
    if len(overlay_names) != manifest.get("overlay_count", 0):
        raise ValueError("map layout overlay count differs from manifest")
    output_dir.mkdir(parents=True, exist_ok=True)
    results = []
    edited_assets = 0
    for name in asset_names + overlay_names:
        asset = json.loads((input_dir / name).read_text())
        payload = serialize_structure(asset["structure"])
        if len(payload) != asset["decoded_bytes"]:
            raise ValueError(f"map payload {name} changed length")
        edited = sha256(payload) != asset["decoded_sha256"]
        if edited and not args.allow_edits:
            raise ValueError(f"map payload {name} differs from the exported retail decode")
        edited_assets += edited
        output_name = name.replace(".json", ".bin")
        (output_dir / output_name).write_bytes(payload)
        results.append({"asset": name, "decoded_bytes": len(payload),
                        "decoded_sha256": sha256(payload),
                        "matches_retail_decode": not edited,
                        "source_sha256": asset["source_sha256"],
                        "retail_source_reencoded": False})
    report = {"reference_sha256": manifest["reference_sha256"],
              "map_count": manifest["map_count"],
              "asset_count": len(results),
              "physical_asset_count": len(asset_names),
              "overlay_count": len(overlay_names),
              "edited_assets": edited_assets,
              "decoded_bytes": sum(item["decoded_bytes"] for item in results),
              "assets": results,
              "caveat": "Decoded payloads reproduce exactly; retail compressed source bytes are not regenerated."}
    (output_dir / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in ("map_count", "asset_count", "decoded_bytes")}))


if __name__ == "__main__":
    main()
