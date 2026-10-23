#!/usr/bin/env python3
"""Export packed attributes preceding two opening tile DMA banks."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
SPECS = (
    (0x985180, 0x985324, 826, 0x140788, "frame-attributes.json"),
    (0x9950e4, 0x9951a0, 367, 0x1404a0, "bg-attributes.json"),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_segment(manifest, source_dir, start, verify_hash=True):
    matches = [entry for entry in manifest["segments"] if entry["start"] == start]
    specs = [spec for spec in SPECS if spec[0] == start]
    if len(matches) != 1 or len(specs) != 1:
        raise ValueError("opening attribute segment is not unique")
    entry, spec = matches[0], specs[0]
    expected_padding = (-(4 + (spec[2] + 1) // 2)) % 4
    if (entry["start"], entry["end"], entry["tile_count"],
            entry["following_tile_start"], entry["file"], entry["padding_bytes"]) != (
            spec[0], spec[1], spec[2], spec[1], spec[4], expected_padding):
        raise ValueError("opening attribute segment boundary differs")
    values = json.loads((source_dir / entry["file"]).read_text())["tile_attributes"]
    if len(values) != spec[2] or any(type(value) is not int or not 0 <= value <= 15 for value in values):
        raise ValueError("opening tile attribute count or value differs")
    output = bytearray((spec[1] - spec[0]).to_bytes(2, "little"))
    output += spec[2].to_bytes(2, "little")
    for index in range(0, len(values), 2):
        output.append(values[index] | ((values[index + 1] if index + 1 < len(values) else 0) << 4))
    output += bytes((-len(output)) % 4)
    data = bytes(output)
    if len(data) != spec[1] - spec[0] or (verify_hash and sha256(data) != entry["source_sha256"]):
        raise ValueError("opening tile attributes differ from retail")
    return data


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("opening attribute export must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    segments = []
    for start, end, tile_count, literal, file_name in SPECS:
        data = rom[start:end]
        size = int.from_bytes(data[:2], "little")
        count = int.from_bytes(data[2:4], "little")
        packed_end = 4 + (tile_count + 1) // 2
        if (size != end - start or count != tile_count or
                len(data) != ((packed_end + 3) & ~3) or
                int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + end or
                any(data[packed_end:]) or
                (tile_count & 1 and data[packed_end - 1] >> 4)):
            raise ValueError("opening attribute header, tile count, or padding differs")
        values = [(data[4 + index // 2] >> (4 * (index & 1))) & 15
                  for index in range(tile_count)]
        (output / file_name).write_text(json.dumps({"tile_attributes": values}, separators=(",", ":")) + "\n")
        segments.append({"start": start, "end": end, "tile_count": tile_count,
                         "following_tile_start": end, "file": file_name,
                         "padding_bytes": len(data) - packed_end,
                         "source_sha256": sha256(data)})
    manifest = {"reference_sha256": ROM_SHA256, "segments": segments,
                "caveat": "Each header length and tile count matches the following DMA bank, and its packed nibbles re-encode exactly. The meaning of an attribute value is not established by the DMA call."}
    for entry in segments:
        if encode_segment(manifest, output, entry["start"]) != rom[entry["start"]:entry["end"]]:
            raise ValueError("opening attribute export does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"segments": len(segments), "tile_attributes": sum(
                entry["tile_count"] for entry in segments),
            "source_bytes": sum(entry["end"] - entry["start"] for entry in segments),
            "padding_bytes": sum(entry["padding_bytes"] for entry in segments),
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
