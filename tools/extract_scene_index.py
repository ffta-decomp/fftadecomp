#!/usr/bin/env python3
"""Extract the four-byte retail scene index without assigning unknown field meanings."""

import argparse
import hashlib
import json
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0xA19970
END = 0xA19D18
ROW_COUNT = (END - START) // 4
FIELDS = ("raw_byte_0", "raw_byte_1", "relative_table_selector", "raw_byte_3")


def extract(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if (int.from_bytes(rom[0x9A20:0x9A24], "little") != START + 0x08000000 or
            int.from_bytes(rom[0x124E70:0x124E74], "little") != END + 0x08000000):
        raise ValueError("scene index references differ")
    rows = [dict(zip(FIELDS, rom[position:position + 4]))
            for position in range(START, END, 4)]
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "start": START, "end": END, "rows": rows}


def encode(asset):
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("start"), asset.get("end")) != (START, END) or
            len(asset.get("rows", [])) != ROW_COUNT):
        raise ValueError("scene index metadata differs")
    result = bytearray()
    for row in asset["rows"]:
        if not isinstance(row, dict) or set(row) != set(FIELDS):
            raise ValueError("scene index fields differ")
        for field in FIELDS:
            value = row[field]
            if type(value) is not int or not 0 <= value <= 255:
                raise ValueError("scene index field is not a byte")
            result.append(value)
    return bytes(result)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output == root or root in output.parents:
        parser.error("extracted assets must be outside the source tree")
    rom = args.rom.read_bytes()
    asset = extract(rom)
    rebuilt = encode(asset)
    if rebuilt != rom[START:END]:
        raise ValueError("scene index roundtrip differs from retail")
    if (any(asset["rows"][0].values()) or
            any(row["raw_byte_3"] for row in asset["rows"]) or
            any(row["relative_table_selector"] == 0 for row in asset["rows"][1:])):
        raise ValueError("observed retail row pattern differs")
    output.mkdir(parents=True, exist_ok=True)
    (output / "manifest.json").write_text(json.dumps(asset, indent=2) + "\n")
    print(json.dumps({"rows": ROW_COUNT, "bytes": len(rebuilt),
                      "sha256": hashlib.sha256(rebuilt).hexdigest()}))


if __name__ == "__main__":
    main()
