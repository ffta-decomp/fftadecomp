#!/usr/bin/env python3
"""Extract shared-command battle scripts while leaving unowned FF gaps unselected."""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
START = 0xA1A908
END = 0xA1B90C
DISPATCH_START = 0x36D5A4
COMMAND_LENGTHS = (1, 3, 4, 4, 5, 3, 4, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3)
DISPATCH_END = DISPATCH_START + 6 * len(COMMAND_LENGTHS)
# These are validated physical extents for the pinned retail revision. Gaps
# between them are not selected or classified as padding.
GROUP_SECTIONS = (
    (0xA1A918, 0xA1ABEC, 63),
    (0xA1ABEC, 0xA1AEAB, 63),
    (0xA1AEAC, 0xA1AF65, 1),
    (0xA1AF68, 0xA1B200, 63),
    (0xA1B200, 0xA1B292, 63),
    (0xA1B294, 0xA1B48A, 63),
    (0xA1B48C, 0xA1B682, 63),
    (0xA1B684, 0xA1B90A, 63),
)


def section_ranges():
    return [(DISPATCH_START, DISPATCH_END), (START, GROUP_SECTIONS[0][0])] + [
        (start, end) for start, end, _ in GROUP_SECTIONS]


def _check_dispatch(rom):
    rows = []
    for opcode, length in enumerate(COMMAND_LENGTHS):
        actual, handler = struct.unpack_from("<HI", rom, DISPATCH_START + 6 * opcode)
        if actual != length:
            raise ValueError("retail command descriptor length differs")
        if not 0x08000001 <= handler < 0x0A000000 or not handler & 1:
            raise ValueError("retail handler pointer is not Thumb ROM code")
        rows.append({"opcode": opcode, "encoded_length": length,
                     "handler_thumb": handler})
    return rows


def extract(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    dispatch = _check_dispatch(rom)
    outer_offsets = struct.unpack_from("<8H", rom, START)
    if tuple(START + offset for offset in outer_offsets) != tuple(
            start for start, _, _ in GROUP_SECTIONS):
        raise ValueError("nested battle-script group addresses differ")
    groups = []
    for group_start, group_end, entry_count in GROUP_SECTIONS:
        entry_offsets = struct.unpack_from("<" + "H" * entry_count, rom, group_start)
        cursor = group_start + 2 * entry_count
        command_offsets = []
        commands = []
        while cursor < group_end:
            opcode = rom[cursor]
            if opcode >= len(COMMAND_LENGTHS):
                raise ValueError("unknown nested battle-script opcode")
            length = COMMAND_LENGTHS[opcode]
            if cursor + length > group_end:
                raise ValueError("command crosses a validated group boundary")
            command_offsets.append(cursor)
            commands.append({"opcode": opcode,
                             "arguments": list(rom[cursor + 1:cursor + length])})
            cursor += length
        index_by_address = {address: index for index, address in enumerate(command_offsets)}
        try:
            entries = [index_by_address[group_start + offset]
                       for offset in entry_offsets]
        except KeyError as error:
            raise ValueError("directory entry does not target a command") from error
        groups.append({"start": group_start, "end": group_end,
                       "entry_command_indices": entries, "commands": commands})
    previous_end = GROUP_SECTIONS[0][0]
    gaps = []
    for start, end, _ in GROUP_SECTIONS:
        if start != previous_end:
            if rom[previous_end:start] != b"\xff" * (start - previous_end):
                raise ValueError("unselected inter-group bytes differ")
            gaps.append({"start": previous_end, "end": start})
        previous_end = end
    if rom[previous_end:END] != b"\xff" * (END - previous_end):
        raise ValueError("unselected trailing bytes differ")
    gaps.append({"start": previous_end, "end": END})
    if sum(gap["end"] - gap["start"] for gap in gaps) != 12:
        raise ValueError("unselected gap accounting differs")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "start": START, "end": END, "dispatch": dispatch, "groups": groups,
            "unselected_ff_gaps": gaps}


def encode_sections(asset):
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("start"), asset.get("end")) != (START, END) or
            not isinstance(asset.get("groups"), list) or
            len(asset["groups"]) != len(GROUP_SECTIONS)):
        raise ValueError("nested battle-script metadata differs")
    expected_gaps = []
    previous_end = GROUP_SECTIONS[0][0]
    for start, end, _ in GROUP_SECTIONS:
        if start != previous_end:
            expected_gaps.append({"start": previous_end, "end": start})
        previous_end = end
    expected_gaps.append({"start": previous_end, "end": END})
    if asset.get("unselected_ff_gaps") != expected_gaps:
        raise ValueError("unselected gap boundaries differ")
    dispatch = asset.get("dispatch")
    if not isinstance(dispatch, list) or len(dispatch) != len(COMMAND_LENGTHS):
        raise ValueError("nested battle-script dispatch size differs")
    dispatch_bytes = bytearray()
    for opcode, (row, length) in enumerate(zip(dispatch, COMMAND_LENGTHS)):
        handler = row.get("handler_thumb")
        if (row.get("opcode") != opcode or row.get("encoded_length") != length or
                type(handler) is not int or not 0x08000001 <= handler < 0x0A000000 or
                not handler & 1):
            raise ValueError("nested battle-script dispatch entry differs")
        dispatch_bytes.extend(struct.pack("<HI", length, handler))
    outer = struct.pack("<8H", *(start - START for start, _, _ in GROUP_SECTIONS))
    result = {(DISPATCH_START, DISPATCH_END): bytes(dispatch_bytes),
              (START, GROUP_SECTIONS[0][0]): outer}
    for (start, end, entry_count), group in zip(GROUP_SECTIONS, asset["groups"]):
        if (group.get("start"), group.get("end")) != (start, end):
            raise ValueError("nested battle-script group boundary differs")
        commands = group.get("commands")
        entries = group.get("entry_command_indices")
        if not isinstance(commands, list) or not isinstance(entries, list) or len(entries) != entry_count:
            raise ValueError("nested battle-script directory size differs")
        payload = bytearray()
        command_offsets = []
        for command in commands:
            opcode = command.get("opcode")
            arguments = command.get("arguments")
            if (type(opcode) is not int or not 0 <= opcode < len(COMMAND_LENGTHS) or
                    not isinstance(arguments, list) or
                    len(arguments) != COMMAND_LENGTHS[opcode] - 1 or
                    any(type(value) is not int or not 0 <= value <= 255
                        for value in arguments)):
                raise ValueError("invalid nested battle-script command")
            command_offsets.append(2 * entry_count + len(payload))
            payload.extend((opcode, *arguments))
        if 2 * entry_count + len(payload) != end - start:
            raise ValueError("nested battle-script group changed its physical extent")
        if any(type(index) is not int or not 0 <= index < len(command_offsets)
               for index in entries):
            raise ValueError("directory entry has no command target")
        directory = struct.pack("<" + "H" * entry_count,
                                *(command_offsets[index] for index in entries))
        result[(start, end)] = directory + payload
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
    sections = encode_sections(asset)
    if list(sections) != section_ranges() or any(
            encoded != rom[start:end] for (start, end), encoded in sections.items()):
        raise ValueError("nested battle-script section roundtrip differs")
    output.mkdir(parents=True, exist_ok=True)
    (output / "manifest.json").write_text(json.dumps(asset, indent=2) + "\n")
    commands = sum(len(group["commands"]) for group in asset["groups"])
    covered = sum(end - start for start, end in sections)
    print(json.dumps({"dispatch_entries": len(asset["dispatch"]),
        "groups": len(asset["groups"]), "entries": sum(
        len(group["entry_command_indices"]) for group in asset["groups"]),
        "commands": commands, "selected_bytes": covered,
        "unselected_gap_bytes": END - START - (covered - (DISPATCH_END - DISPATCH_START)),
        "sections": [[start, end] for start, end in sections]}))


if __name__ == "__main__":
    main()
