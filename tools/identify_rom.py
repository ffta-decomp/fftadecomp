#!/usr/bin/env python3
"""Identify a GBA ROM without modifying it or trusting its filename."""
import argparse
import hashlib
import json
import struct
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("rom", type=Path)
    args = parser.parse_args()
    rom = args.rom.read_bytes()
    if len(rom) < 192:
        raise SystemExit("Input is smaller than the GBA header")
    header = rom[:192]
    entry = struct.unpack_from("<I", header)[0]
    expected = (-sum(header[0xa0:0xbd]) - 0x19) & 0xff
    result = {
        "path": str(args.rom.resolve()),
        "size": len(rom),
        "sha256": hashlib.sha256(rom).hexdigest(),
        "sha1": hashlib.sha1(rom).hexdigest(),
        "title_ascii": header[0xa0:0xac].rstrip(b"\0").decode("ascii", "replace"),
        "game_code_ascii": header[0xac:0xb0].decode("ascii", "replace"),
        "maker_code_ascii": header[0xb0:0xb2].decode("ascii", "replace"),
        "version_byte": header[0xbc],
        "complement_byte": header[0xbd],
        "complement_valid": header[0xbd] == expected,
        "entry_word": f"0x{entry:08x}",
        "first_256_sha256": hashlib.sha256(rom[:256]).hexdigest(),
        "last_non_ff_offset": len(rom.rstrip(b"\xff")) - 1,
    }
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
