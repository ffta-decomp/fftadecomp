#!/usr/bin/env python3
"""Export a self-sized packed attribute block beside a world-map display source."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x960dd8
END = 0x960ec0
ENTRY_COUNT = 454
NEXT_SOURCE_LITERAL = 0x135e40


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_block(manifest, source_dir, verify_hash=True):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["start"] != START or manifest["end"] != END or
            manifest["entry_count"] != ENTRY_COUNT or
            manifest["padding_bytes"] != 1):
        raise ValueError("world-map packed block revision or boundary differs")
    values = json.loads((source_dir / manifest["file"]).read_text())["attributes"]
    if len(values) != ENTRY_COUNT or any(type(value) is not int or not 0 <= value <= 15
                                        for value in values):
        raise ValueError("world-map packed attribute count or value differs")
    output = bytearray((END - START).to_bytes(2, "little"))
    output += ENTRY_COUNT.to_bytes(2, "little")
    for index in range(0, ENTRY_COUNT, 2):
        output.append(values[index] | values[index + 1] << 4)
    output.append(0)
    data = bytes(output)
    if len(data) != END - START or (verify_hash and sha256(data) != manifest["source_sha256"]):
        raise ValueError("world-map packed attributes differ from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("world-map packed export must be outside the source tree")
    data = rom[START:END]
    if (int.from_bytes(data[:2], "little") != END - START or
            int.from_bytes(data[2:4], "little") != ENTRY_COUNT or
            4 + ENTRY_COUNT // 2 + 1 != len(data) or data[-1] != 0 or
            int.from_bytes(rom[NEXT_SOURCE_LITERAL:NEXT_SOURCE_LITERAL + 4], "little") != ROM_BASE + END):
        raise ValueError("world-map packed header or adjacent source differs")
    values = [(data[4 + index // 2] >> (4 * (index & 1))) & 15
              for index in range(ENTRY_COUNT)]
    output.mkdir(parents=True, exist_ok=True)
    file_name = "attributes.json"
    (output / file_name).write_text(json.dumps({"attributes": values}, separators=(",", ":")) + "\n")
    manifest = {"reference_sha256": ROM_SHA256, "start": START, "end": END,
                "entry_count": ENTRY_COUNT, "padding_bytes": 1,
                "file": file_name, "source_sha256": sha256(data),
                "next_source_literal": NEXT_SOURCE_LITERAL,
                "caveat": "The block's own size, count, packed nibbles, and alignment are verified. The following display source is referenced by code; whether this block supplies per-tile attributes to that source is not established."}
    if encode_block(manifest, output) != data:
        raise ValueError("world-map packed block does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"entries": ENTRY_COUNT, "source_bytes": len(data),
            "padding_bytes": 1, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
