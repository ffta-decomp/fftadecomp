#!/usr/bin/env python3
"""Export complete dimension-bounded graphics run records before the LZ77 bank.

The stream interpretation is structural: each four-byte command advances a
number of cells given by the low ten bits of its second halfword. The source
code and remaining flag bits have not yet been assigned rendering semantics.
"""

import argparse
import hashlib
import json
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
BANK_START = 0x8f4674
BANK_END = 0x8f6cfc
POINTER_START = 0x390000
POINTER_END = 0x3b0000
EXPECTED_POINTER_ROOTS = 78
EXPECTED_COMPLETE_RECORDS = 60
EXPECTED_COMPLETE_BYTES = 3588
LITERAL_TAIL_RECORD = 0x8f4cd4
SECOND_RUN_RECORD = 0x8f5f08


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def encode_record(record, source_dir):
    fields = json.loads((source_dir / "records" / record["file"]).read_text())
    width = fields["width_cells"]
    height = fields["height_cells"]
    offset_x = fields["position_offset_x"]
    offset_y = fields["position_offset_y"]
    if any(type(value) is not int or not 1 <= value <= 32 for value in (width, height)):
        raise ValueError("graphics run dimensions differ")
    if any(type(value) is not int or not 0 <= value <= 255 for value in (offset_x, offset_y)):
        raise ValueError("graphics run position offset differs")
    output = bytearray((width, height, offset_x, offset_y))
    covered = 0
    for command in fields["commands"]:
        source_code = command["source_code"]
        run_length = command["run_length"]
        flags = command["flags"]
        if (any(type(value) is not int for value in (source_code, run_length, flags)) or
                not 0 <= source_code <= 0xffff or not 1 <= run_length <= 0x3ff or
                flags & 0x3ff or not 0 <= flags <= 0xffff):
            raise ValueError("graphics run command differs")
        covered += run_length
        if covered > width * height:
            raise ValueError("graphics run exceeds declared dimensions")
        output += source_code.to_bytes(2, "little")
        output += (flags | run_length).to_bytes(2, "little")
    if covered != width * height:
        raise ValueError("graphics run does not fill declared dimensions")
    tail = fields["tail"]
    if tail["kind"] == "zero_span_terminator":
        terminator = tail["source_code"]
        if type(terminator) is not int or not 0 <= terminator <= 0xffff:
            raise ValueError("graphics run terminator differs")
        output += terminator.to_bytes(2, "little") + b"\0\0"
    elif tail["kind"] == "literal_values" and record["start"] == LITERAL_TAIL_RECORD:
        values = tail["halfwords"]
        literal_count = sum(command["run_length"] for command in fields["commands"]
                            if command["source_code"] == 0x3ff)
        if len(values) != literal_count or any(type(value) is not int or not 0 <= value <= 0xffff
                                               for value in values):
            raise ValueError("graphics run literal count or value differs")
        output += b"".join(value.to_bytes(2, "little") for value in values)
    elif tail["kind"] == "second_run_stream" and record["start"] == SECOND_RUN_RECORD:
        second_commands = tail["commands"]
        if not second_commands or len(second_commands) != 105:
            raise ValueError("graphics secondary run count differs")
        secondary_cells = 0
        for command in second_commands:
            source_code, run_length, flags = (command[key] for key in
                                              ("source_code", "run_length", "flags"))
            if (any(type(value) is not int for value in (source_code, run_length, flags)) or
                    not 0 <= source_code <= 0xffff or not 1 <= run_length <= 0x3ff or
                    flags & 0x3ff or not 0 <= flags <= 0xffff):
                raise ValueError("graphics secondary command differs")
            secondary_cells += run_length
            output += source_code.to_bytes(2, "little")
            output += (flags | run_length).to_bytes(2, "little")
        if secondary_cells != 416 or type(tail["terminator_source_code"]) is not int or not 0 <= tail["terminator_source_code"] <= 0xffff:
            raise ValueError("graphics secondary run total or terminator differs")
        output += tail["terminator_source_code"].to_bytes(2, "little") + b"\0\0"
    else:
        raise ValueError("unknown graphics run tail")
    if len(output) != record["end"] - record["start"] or sha256(output) != record["source_sha256"]:
        raise ValueError("graphics run record differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output.mkdir(parents=True, exist_ok=True)
    record_dir = output / "records"
    record_dir.mkdir(exist_ok=True)
    pointers = {}
    for site in range(POINTER_START, POINTER_END, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if BANK_START <= target < BANK_END:
            pointers.setdefault(target, []).append(site)
    starts = sorted(pointers)
    if len(starts) != EXPECTED_POINTER_ROOTS or starts[0] != BANK_START:
        raise ValueError("graphics run pointer roots differ")
    records = []
    incomplete = []
    for index, start in enumerate(starts):
        end = starts[index + 1] if index + 1 < len(starts) else BANK_END
        data = rom[start:end]
        if len(data) < 12 or len(data) % 4:
            raise ValueError("graphics run pointer bounds differ")
        width, height, offset_x, offset_y = data[:4]
        if not 1 <= width <= 32 or not 1 <= height <= 32:
            raise ValueError("graphics run header dimensions differ")
        commands = []
        covered = 0
        cursor = 4
        while cursor + 4 <= len(data) and covered < width * height:
            source_code = u16(data, cursor)
            span_code = u16(data, cursor + 2)
            run_length = span_code & 0x3ff
            if not run_length or covered + run_length > width * height:
                break
            commands.append({"source_code": source_code, "run_length": run_length,
                             "flags": span_code & 0xfc00})
            covered += run_length
            cursor += 4
        if covered != width * height:
            incomplete.append(start)
            continue
        if cursor + 4 == len(data) and not u16(data, cursor + 2):
            tail = {"kind": "zero_span_terminator", "source_code": u16(data, cursor)}
        elif start == LITERAL_TAIL_RECORD:
            literal_count = sum(command["run_length"] for command in commands
                                if command["source_code"] == 0x3ff)
            if len(data) - cursor != literal_count * 2:
                raise ValueError("graphics literal tail length differs")
            tail = {"kind": "literal_values", "halfwords":
                    [u16(data, pos) for pos in range(cursor, len(data), 2)]}
        elif start == SECOND_RUN_RECORD:
            second_commands = []
            second_cells = 0
            while cursor + 4 < len(data):
                source_code = u16(data, cursor)
                span_code = u16(data, cursor + 2)
                run_length = span_code & 0x3ff
                if not run_length:
                    raise ValueError("graphics secondary run ends early")
                second_commands.append({"source_code": source_code,
                                        "run_length": run_length,
                                        "flags": span_code & 0xfc00})
                second_cells += run_length
                cursor += 4
            if (cursor + 4 != len(data) or u16(data, cursor + 2) or
                    len(second_commands) != 105 or second_cells != 416):
                raise ValueError("graphics secondary run boundary differs")
            tail = {"kind": "second_run_stream", "commands": second_commands,
                    "terminator_source_code": u16(data, cursor)}
        else:
            incomplete.append(start)
            continue
        name = f"run-0x{start:06x}.json"
        fields = {"width_cells": width, "height_cells": height,
                  "position_offset_x": offset_x, "position_offset_y": offset_y,
                  "commands": commands, "tail": tail}
        (record_dir / name).write_text(json.dumps(fields, indent=2) + "\n")
        record = {"start": start, "end": end, "file": name,
                  "pointer_sites": pointers[start], "command_count": len(commands),
                  "source_sha256": sha256(data)}
        records.append(record)
        if encode_record(record, output) != data:
            raise ValueError("graphics run export does not round-trip")
    selected_bytes = sum(record["end"] - record["start"] for record in records)
    if len(records) != EXPECTED_COMPLETE_RECORDS or selected_bytes != EXPECTED_COMPLETE_BYTES:
        raise ValueError("complete graphics run coverage differs")
    manifest = {"reference_sha256": ROM_SHA256, "bank_start": BANK_START,
                "bank_end": BANK_END, "pointer_root_count": len(starts),
                "complete_record_count": len(records), "selected_bytes": selected_bytes,
                "incomplete_starts": incomplete, "records": records,
                "caveat": "Primary run lengths fill the header grid. One literal tail matches the 0x03ff run length; one record has a separately terminated second run stream. Source-code and flag rendering semantics are not assigned; 18 other records remain original-byte inclusion."}
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"complete_records": len(records), "selected_bytes": selected_bytes,
            "incomplete_records": len(incomplete), "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
