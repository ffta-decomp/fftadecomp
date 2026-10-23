#!/usr/bin/env python3
"""Export the uncompressed pointer-backed records between LZ77 runs."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_pointer_lz77_records import POINTER_START, POINTER_END, ROM_BASE, ROM_SHA256

GAPS = (
    (0x8fea47, 0x8fea54, 1),
    (0x901f34, 0x902538, 1),
    (0x90716c, 0x907178, 1),
    (0x90a234, 0x90a278, 1),
    (0x90f9d3, 0x90f9f8, 1),
    (0x913a04, 0x914208, 1),
    (0x917fbb, 0x918030, 1),
    (0x91f80b, 0x91f824, 1),
    (0x92dc7b, 0x92de00, 1),
    (0x92fd33, 0x92fd58, 1),
    (0x931e7c, 0x931f68, 3),
    (0x93a675, 0x93a87c, 1),
    (0x93c83b, 0x93c860, 1),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def pointer_sites(rom):
    sites = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if GAPS[0][0] <= target < GAPS[-1][1]:
            sites.setdefault(target, []).append(site)
    return sites


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    payload_dir = output / "payloads"
    payload_dir.mkdir(exist_ok=True)
    sites = pointer_sites(rom)
    gaps = []
    for start, end, expected_count in GAPS:
        pointers = sorted(pointer for pointer in sites if start <= pointer < end)
        if len(pointers) != expected_count or pointers[0] != ((start + 3) & ~3):
            raise ValueError("raw record pointers or alignment differ")
        if rom[start:pointers[0]] != bytes(pointers[0] - start):
            raise ValueError("raw record leading alignment is not zero")
        records = []
        for index, pointer in enumerate(pointers):
            record_end = pointers[index + 1] if index + 1 < len(pointers) else end
            header = rom[pointer:pointer + 4]
            if (len(header) != 4 or header[0] not in (1, 2, 3, 4) or
                    header[1] not in (0, 1, 2) or header[2:] != b"\xfd\x7f"):
                raise ValueError("raw record header differs")
            payload = rom[pointer + 4:record_end]
            if not payload or len(payload) % 2:
                raise ValueError("raw record payload is not halfword-aligned")
            # Mode 1 contains the two large 4bpp-aligned banks; the shorter
            # records remain neutral halfwords until their consumers are known.
            format_name = "4bpp_tiles" if header[1] == 1 else "u16_halfwords"
            file_name = f"record-0x{pointer:06x}.{'4bpp' if format_name == '4bpp_tiles' else 'json'}"
            if format_name == "4bpp_tiles":
                if len(payload) % 32:
                    raise ValueError("raw tile bank does not contain whole 4bpp tiles")
                (payload_dir / file_name).write_bytes(payload)
            else:
                values = [int.from_bytes(payload[pos:pos + 2], "little")
                          for pos in range(0, len(payload), 2)]
                (payload_dir / file_name).write_text(json.dumps({"halfwords": values}, indent=2) + "\n")
            records.append({"start": pointer, "end": record_end, "header": header.hex(),
                            "pointer_sites": sites[pointer], "format": format_name,
                            "file": file_name, "payload_sha256": sha256(payload)})
        gaps.append({"start": start, "end": end, "leading_padding_bytes": pointers[0] - start,
                     "source_sha256": sha256(rom[start:end]), "records": records})
    manifest = {"reference_sha256": ROM_SHA256,
                "pointer_table_window": [POINTER_START, POINTER_END],
                "gaps": gaps, "record_count": sum(len(gap["records"]) for gap in gaps),
                "source_bytes": sum(gap["end"] - gap["start"] for gap in gaps),
                "padding_bytes": sum(gap["leading_padding_bytes"] for gap in gaps),
                "layout_note": "Only word alignment, pointer ownership, record headers, and payload widths are established. Mode-1 payloads are tile-aligned; final image layout is unproven."}
    if manifest["record_count"] != 15:
        raise ValueError("raw record count differs")
    for gap in gaps:
        if reconstruct_gap(manifest, output, gap["start"]) != rom[gap["start"]:gap["end"]]:
            raise ValueError("raw record gap does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"gap_count": len(gaps), "record_count": manifest["record_count"],
            "source_bytes": manifest["source_bytes"], "padding_bytes": manifest["padding_bytes"],
            "manifest_sha256": sha256(path.read_bytes())}


def gap_entry(manifest, offset):
    matches = [gap for gap in manifest["gaps"] if gap["start"] == offset]
    if len(matches) != 1:
        raise ValueError("raw record gap is not unique")
    return matches[0]


def payload_source_files(manifest, offset, source_dir):
    return [source_dir / "payloads" / record["file"]
            for record in gap_entry(manifest, offset)["records"]]


def reconstruct_gap(manifest, source_dir, offset):
    gap = gap_entry(manifest, offset)
    output = bytearray(gap["leading_padding_bytes"])
    for record in gap["records"]:
        if gap["start"] + len(output) != record["start"]:
            raise ValueError("raw record position differs")
        path = source_dir / "payloads" / record["file"]
        if record["format"] == "4bpp_tiles":
            payload = path.read_bytes()
            if len(payload) % 32:
                raise ValueError("raw record tile payload is not aligned")
        elif record["format"] == "u16_halfwords":
            values = json.loads(path.read_text())["halfwords"]
            if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
                raise ValueError("raw record halfword differs")
            payload = b"".join(value.to_bytes(2, "little") for value in values)
        else:
            raise ValueError("raw record format differs")
        if (len(payload) != record["end"] - record["start"] - 4 or
                sha256(payload) != record["payload_sha256"]):
            raise ValueError(f"raw record payload differs at 0x{record['start']:08x}")
        output += bytes.fromhex(record["header"]) + payload
    if len(output) != gap["end"] - gap["start"] or sha256(output) != gap["source_sha256"]:
        raise ValueError("raw record gap differs")
    return bytes(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("raw record export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
