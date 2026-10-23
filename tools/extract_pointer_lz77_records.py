#!/usr/bin/env python3
"""Export pointer-backed LZ77 records adjacent to the shared sprite banks."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_lz77_resources import decode_lz77
from map_layout_source_codec import capture_lz77_plan, encode_lz77_plan

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
POINTER_START = 0x390000
POINTER_END = 0x3b0000
RUN_SPANS = (
    (0x8f6cfc, 0x8fea47, 46),
    (0x8fea54, 0x901f34, 13),
    (0x902538, 0x90716c, 21),
    (0x907178, 0x90a234, 8),
    (0x90a278, 0x90f9d3, 34),
    (0x90f9f8, 0x913a04, 34),
    (0x914208, 0x917fbb, 18),
    (0x918030, 0x91f80b, 27),
    (0x91f824, 0x92dc7b, 55),
    (0x92de00, 0x92fd33, 3),
    (0x92fd58, 0x931e7c, 9),
    (0x931f68, 0x93a675, 40),
    (0x93a87c, 0x93c83b, 10),
    (0x93c860, 0x94844f, 40),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def pointer_sites(rom):
    sites = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if RUN_SPANS[0][0] <= target < RUN_SPANS[-1][1]:
            sites.setdefault(target, []).append(site)
    return sites


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    decoded_dir = output / "decoded"
    decoded_dir.mkdir(exist_ok=True)
    sites = pointer_sites(rom)
    runs = []
    for start, end, expected_count in RUN_SPANS:
        cursor = start
        records = []
        padding_bytes = 0
        while cursor < end:
            if cursor % 4:
                raise ValueError("record header is not word-aligned")
            header = rom[cursor:cursor + 4]
            if (len(header) != 4 or header[0] not in (1, 2, 3, 4) or
                    header[1] not in (2, 3) or header[2:] != b"\xfd\x7f"):
                raise ValueError(f"unknown record header at 0x{cursor:08x}")
            references = sites.get(cursor, [])
            if not references:
                raise ValueError(f"record 0x{cursor:08x} has no pointer-table reference")
            decoded_record = decode_lz77(rom, cursor + 4)
            if decoded_record is None:
                raise ValueError(f"record 0x{cursor:08x} is not strict BIOS LZ77")
            source_end, decoded = decoded_record
            if source_end > end:
                raise ValueError("LZ77 source leaves its pinned run")
            source = rom[cursor + 4:source_end]
            decoded_again, plan = capture_lz77_plan(source)
            if decoded_again != decoded or encode_lz77_plan(decoded, plan) != source:
                raise ValueError("record token plan does not round-trip")
            file_name = f"record-0x{cursor:06x}.bin"
            (decoded_dir / file_name).write_bytes(decoded)
            next_cursor = source_end if source_end == end else (source_end + 3) & ~3
            if next_cursor > end or rom[source_end:next_cursor] != bytes(next_cursor - source_end):
                raise ValueError("record alignment does not contain zero padding")
            padding = next_cursor - source_end
            padding_bytes += padding
            records.append({"start": cursor, "header": header.hex(),
                            "pointer_sites": references, "file": file_name,
                            "decoded_bytes": len(decoded), "decoded_sha256": sha256(decoded),
                            "encoded_bytes": len(source), "encoded_sha256": sha256(source),
                            "padding_bytes": padding, "token_plan": plan})
            cursor = next_cursor
        if cursor != end or len(records) != expected_count:
            raise ValueError("pointer-backed run boundary or record count differs")
        runs.append({"start": start, "end": end, "record_count": len(records),
                     "padding_bytes": padding_bytes,
                     "source_sha256": sha256(rom[start:end]), "records": records})
    manifest = {"reference_sha256": ROM_SHA256, "pointer_table_window":
                [POINTER_START, POINTER_END], "runs": runs,
                "record_count": sum(run["record_count"] for run in runs),
                "source_bytes": sum(run["end"] - run["start"] for run in runs),
                "padding_bytes": sum(run["padding_bytes"] for run in runs),
                "decoded_bytes": sum(record["decoded_bytes"] for run in runs
                                     for record in run["records"]),
                "layout_note": "The four-byte record header and decoded payload layout are not semantically identified. Only the pointer-backed record boundaries and exact codec round-trip are established."}
    if manifest["record_count"] != 358:
        raise ValueError("pointer-backed archive record count differs")
    for run in runs:
        if reconstruct_run(manifest, output, run["start"]) != rom[run["start"]:run["end"]]:
            raise ValueError("pointer-backed archive does not round-trip")
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"record_count": manifest["record_count"], "run_count": len(runs),
            "source_bytes": manifest["source_bytes"], "padding_bytes": manifest["padding_bytes"],
            "decoded_bytes": manifest["decoded_bytes"], "manifest_sha256": sha256(path.read_bytes())}


def run_entry(manifest, offset):
    matches = [run for run in manifest["runs"] if run["start"] == offset]
    if len(matches) != 1:
        raise ValueError("pointer-backed archive run is not unique")
    return matches[0]


def decoded_source_files(manifest, offset, source_dir):
    return [source_dir / "decoded" / record["file"]
            for record in run_entry(manifest, offset)["records"]]


def reconstruct_run(manifest, source_dir, offset):
    run = run_entry(manifest, offset)
    output = bytearray()
    for record in run["records"]:
        if run["start"] + len(output) != record["start"]:
            raise ValueError("pointer-backed record position differs")
        decoded = (source_dir / "decoded" / record["file"]).read_bytes()
        if (len(decoded) != record["decoded_bytes"] or
                sha256(decoded) != record["decoded_sha256"]):
            raise ValueError(f"pointer-backed decoded record differs at 0x{record['start']:08x}")
        encoded = encode_lz77_plan(decoded, record["token_plan"])
        if (len(encoded) != record["encoded_bytes"] or
                sha256(encoded) != record["encoded_sha256"]):
            raise ValueError("pointer-backed LZ77 source differs")
        output += bytes.fromhex(record["header"]) + encoded
        output += bytes(record["padding_bytes"])
    if (len(output) != run["end"] - run["start"] or
            sha256(output) != run["source_sha256"] or
            sum(record["padding_bytes"] for record in run["records"]) != run["padding_bytes"]):
        raise ValueError("pointer-backed archive run differs")
    return bytes(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise SystemExit("pointer-backed archive export must be outside the source tree")
    print(json.dumps(export(args.rom.read_bytes(), output)))


if __name__ == "__main__":
    main()
