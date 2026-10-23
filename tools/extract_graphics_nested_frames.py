#!/usr/bin/env python3
"""Export complete frame sequences nested in two pointer-bounded records."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_graphics_frame_resources import encode_u16
from extract_pointer_lz77_records import ROM_SHA256


ROOTS = {0x94d67c: (0x94d854, 29), 0x94d898: (0x94def4, 91)}
SELECTED_BYTES = sum(end - start for start, (end, _) in ROOTS.items())


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_root(entry, source_dir):
    source = json.loads((source_dir / entry["file"]).read_text())
    sequences = source["sequences"]
    if len(sequences) != entry["sequence_count"]:
        raise ValueError("nested frame sequence count differs")
    output = bytearray()
    for fields in sequences:
        output += _encode_fields(fields)
    if len(output) != entry["end"] - entry["start"] or sha256(output) != entry["source_sha256"]:
        raise ValueError("nested frame root differs from retail")
    return bytes(output)


def _encode_fields(fields):
    frames = fields["frames"]
    encoded = bytearray(encode_u16([fields["attribute0"], fields["attribute1"], len(frames)]))
    for frame in frames:
        primary, secondary = frame["primary_index"], frame["secondary_index"]
        if (type(primary) is not int or not 0 <= primary <= 255 or
                type(secondary) is not int or not 0 <= secondary <= 255):
            raise ValueError("nested frame index differs")
        encoded += encode_u16([frame["duration"]]) + bytes((primary, secondary))
    return bytes(encoded + b"\0\0")


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    entries = []
    for start, (end, expected_count) in ROOTS.items():
        cursor = start
        sequences = []
        while cursor < end:
            if cursor + 12 > end:
                raise ValueError("nested frame header is truncated")
            count = int.from_bytes(rom[cursor + 4:cursor + 6], "little")
            size = 8 + 4 * count
            if not 1 <= count <= 64 or cursor + size > end or rom[cursor + size - 2:cursor + size] != b"\0\0":
                raise ValueError("nested frame boundary differs")
            frames = []
            for index in range(count):
                at = cursor + 6 + 4 * index
                frames.append({"duration": int.from_bytes(rom[at:at + 2], "little"),
                               "primary_index": rom[at + 2], "secondary_index": rom[at + 3]})
            sequences.append({"attribute0": int.from_bytes(rom[cursor:cursor + 2], "little"),
                              "attribute1": int.from_bytes(rom[cursor + 2:cursor + 4], "little"),
                              "frames": frames})
            cursor += size
        if cursor != end or len(sequences) != expected_count:
            raise ValueError("nested frame root coverage differs")
        name = f"nested-0x{start:06x}.json"
        (output / name).write_text(json.dumps({"sequences": sequences}, indent=2) + "\n")
        entry = {"start": start, "end": end, "sequence_count": len(sequences),
                 "file": name, "source_sha256": sha256(rom[start:end])}
        entries.append(entry)
        if encode_root(entry, output) != rom[start:end]:
            raise ValueError("nested frame root does not round-trip")
    if sum(entry["end"] - entry["start"] for entry in entries) != SELECTED_BYTES:
        raise ValueError("nested frame coverage differs")
    manifest = {"reference_sha256": ROM_SHA256, "entries": entries,
                "selected_bytes": SELECTED_BYTES,
                "sequence_count": sum(entry["sequence_count"] for entry in entries),
                "scope_note": "Two pointer-bounded frame roots are entirely covered; other tails remain unclassified."}
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"roots": len(entries), "sequences": manifest["sequence_count"],
            "selected_bytes": SELECTED_BYTES, "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("nested graphics frame export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
