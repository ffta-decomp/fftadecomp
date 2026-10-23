#!/usr/bin/env python3
"""Export bounded frame, halfword-sample, and palette graphics records."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_pointer_lz77_records import POINTER_START, POINTER_END, ROM_BASE, ROM_SHA256

FRAME_START = 0x94d5c4
SAMPLE_START = 0x94dfa4
PALETTE_START = 0x94ebdc
END = 0x94ecfc
FRAME_COUNT = 22
SAMPLE_COUNT = 6
PALETTE_COLORS = 144


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def encode_u16(values):
    if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("graphics frame halfword differs")
    return b"".join(value.to_bytes(2, "little") for value in values)


def encode_record(record, source_dir):
    fields = json.loads((source_dir / record["file"]).read_text())
    if record["format"] == "frame_sequence":
        frames = fields["frames"]
        if len(frames) != record["entry_count"]:
            raise ValueError("graphics frame count differs")
        encoded = bytearray(encode_u16([fields["attribute0"], fields["attribute1"], len(frames)]))
        for frame in frames:
            primary = frame["primary_index"]
            secondary = frame["secondary_index"]
            if (type(primary) is not int or not 0 <= primary <= 255 or
                    type(secondary) is not int or not 0 <= secondary <= 255):
                raise ValueError("graphics frame index differs")
            encoded += encode_u16([frame["duration"]]) + bytes((primary, secondary))
        encoded += b"\0\0"
    elif record["format"] == "halfword_samples":
        values = fields["samples"]
        if len(values) != record["entry_count"]:
            raise ValueError("graphics sample count differs")
        encoded = encode_u16([len(values)] + values) + b"\0\0"
    elif record["format"] == "bgr555_palettes":
        palettes = fields["palettes"]
        if len(palettes) != 9 or any(len(palette) != 16 for palette in palettes):
            raise ValueError("graphics palette shape differs")
        values = []
        for palette in palettes:
            for color in palette:
                channels = [color[channel] for channel in ("red", "green", "blue")]
                if any(type(value) is not int or not 0 <= value <= 31 for value in channels):
                    raise ValueError("graphics palette channel differs")
                values.append(channels[0] | channels[1] << 5 | channels[2] << 10)
        encoded = encode_u16(values)
    else:
        raise ValueError("unknown graphics frame record format")
    if len(encoded) != record["selected_bytes"] or sha256(encoded) != record["source_sha256"]:
        raise ValueError(f"graphics frame record differs at 0x{record['start']:08x}")
    return bytes(encoded)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    record_dir = output / "records"
    record_dir.mkdir(exist_ok=True)
    pointers = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if FRAME_START <= target < END:
            pointers.setdefault(target, []).append(site)
    starts = sorted(pointers)
    if (len(starts) != FRAME_COUNT + SAMPLE_COUNT + 1 or starts[0] != FRAME_START or
            starts[FRAME_COUNT] != SAMPLE_START or starts[-1] != PALETTE_START):
        raise ValueError("graphics frame pointer directory differs")
    records = []
    for index, start in enumerate(starts):
        end = starts[index + 1] if index + 1 < len(starts) else END
        if index < FRAME_COUNT:
            count = int.from_bytes(rom[start + 4:start + 6], "little")
            selected = 8 + 4 * count
            if start + selected > end or rom[start + selected - 2:start + selected] != b"\0\0":
                raise ValueError("graphics frame boundary or alignment differs")
            frames = []
            for frame_index in range(count):
                at = start + 6 + 4 * frame_index
                frames.append({"duration": int.from_bytes(rom[at:at + 2], "little"),
                               "primary_index": rom[at + 2], "secondary_index": rom[at + 3]})
            fields = {"attribute0": int.from_bytes(rom[start:start + 2], "little"),
                      "attribute1": int.from_bytes(rom[start + 2:start + 4], "little"),
                      "frames": frames}
            format_name = "frame_sequence"
            padding = 2
        elif index < FRAME_COUNT + SAMPLE_COUNT:
            count = int.from_bytes(rom[start:start + 2], "little")
            selected = 4 + 2 * count
            if start + selected > end or rom[start + selected - 2:start + selected] != b"\0\0":
                raise ValueError("graphics sample boundary or alignment differs")
            fields = {"samples": [int.from_bytes(rom[pos:pos + 2], "little")
                                  for pos in range(start + 2, start + 2 + 2 * count, 2)]}
            format_name = "halfword_samples"
            padding = 2
        else:
            count = PALETTE_COLORS
            selected = END - PALETTE_START
            if selected != 2 * count:
                raise ValueError("graphics palette boundary differs")
            colors = [int.from_bytes(rom[pos:pos + 2], "little")
                      for pos in range(start, end, 2)]
            if any(color & 0x8000 for color in colors):
                raise ValueError("graphics BGR555 palette has reserved high bits")
            fields = {"palettes": [[{"red": color & 31, "green": color >> 5 & 31,
                                      "blue": color >> 10 & 31}
                                     for color in colors[group * 16:(group + 1) * 16]]
                                    for group in range(9)]}
            format_name = "bgr555_palettes"
            padding = 0
        file_name = f"record-0x{start:06x}.json"
        (record_dir / file_name).write_text(json.dumps(fields, indent=2) + "\n")
        record = {"start": start, "end": end, "selected_bytes": selected,
                  "opaque_bytes": end - start - selected, "padding_bytes": padding,
                  "entry_count": count, "format": format_name,
                  "pointer_sites": pointers[start], "file": file_name,
                  "source_sha256": sha256(rom[start:start + selected])}
        if encode_record(record, record_dir) != rom[start:start + selected]:
            raise ValueError("graphics frame record does not round-trip")
        records.append(record)
    manifest = {"reference_sha256": ROM_SHA256,
                "frame_consumer": 0x080d3bd0, "sample_consumer": 0x0810f6c2,
                "pointer_table_window": [POINTER_START, POINTER_END],
                "records": records, "selected_bytes": sum(record["selected_bytes"] for record in records),
                "padding_bytes": sum(record["padding_bytes"] for record in records),
                "opaque_bytes": sum(record["opaque_bytes"] for record in records),
                "scope_note": "Selected prefixes and the nine 16-color palettes rebuild exactly. Long record tails are not selected."}
    if (manifest["selected_bytes"] != 2212 or manifest["padding_bytes"] != 56):
        raise ValueError("graphics frame resource coverage differs")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"record_count": len(records), "selected_bytes": manifest["selected_bytes"],
            "padding_bytes": manifest["padding_bytes"], "opaque_bytes": manifest["opaque_bytes"],
            "manifest_sha256": sha256(path.read_bytes())}


def record_entry(manifest, offset):
    matches = [record for record in manifest["records"] if record["start"] == offset]
    if len(matches) != 1:
        raise ValueError("graphics frame record is not unique")
    return matches[0]


def record_source_file(manifest, offset, source_dir):
    return source_dir / "records" / record_entry(manifest, offset)["file"]


def reconstruct_record(manifest, source_dir, offset):
    return encode_record(record_entry(manifest, offset), source_dir / "records")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("graphics frame export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
