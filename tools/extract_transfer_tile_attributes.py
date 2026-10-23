#!/usr/bin/env python3
"""Extract the packed attribute candidate adjacent to the transfer tile bank."""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0xA1B90C
END = 0xA1BEDC
ENTRY_COUNT = 2962
PACKED_LENGTH = (ENTRY_COUNT + 1) // 2


def extract(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    span = rom[START:END]
    byte_length, count = struct.unpack_from("<HH", span)
    if (byte_length, count) != (END - START, ENTRY_COUNT):
        raise ValueError("packed attribute header differs")
    packed = span[4:4 + PACKED_LENGTH]
    if span[4 + PACKED_LENGTH:] != b"\0" * 3:
        raise ValueError("packed attribute trailing bytes differ")
    values = [((packed[index // 2] >> (4 * (index % 2))) & 15)
              for index in range(count)]
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "start": START, "end": END, "entry_count": count,
            "attributes": values}


def encode(asset):
    values = asset.get("attributes")
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("start"), asset.get("end")) != (START, END) or
            asset.get("entry_count") != ENTRY_COUNT or
            not isinstance(values, list) or len(values) != ENTRY_COUNT or
            any(type(value) is not int or not 0 <= value <= 15 for value in values)):
        raise ValueError("packed attribute metadata differs")
    packed = bytearray(PACKED_LENGTH)
    for index, value in enumerate(values):
        packed[index // 2] |= value << (4 * (index % 2))
    result = struct.pack("<HH", END - START, ENTRY_COUNT) + packed + b"\0" * 3
    if len(result) != END - START:
        raise ValueError("packed attribute size differs")
    return result


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
        raise ValueError("packed attribute roundtrip differs from retail")
    output.mkdir(parents=True, exist_ok=True)
    (output / "manifest.json").write_text(json.dumps(asset, indent=2) + "\n")
    print(json.dumps({"entries": ENTRY_COUNT, "bytes": len(rebuilt),
                      "sha256": hashlib.sha256(rebuilt).hexdigest()}))


if __name__ == "__main__":
    main()
