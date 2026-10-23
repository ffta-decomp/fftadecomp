"""Typed codec for the consumer-bounded graphics action-script bank."""

import hashlib
import json
import struct
from pathlib import Path

from extract_graphics_action_scripts import POINTER_END, POINTER_START
from extract_pointer_lz77_records import ROM_BASE, ROM_SHA256

START = 0x948450
END = 0x94D5C4
POINTER_WINDOW = (POINTER_START, POINTER_END)
FIXED_WIDTHS = {3: 6, 4: 2, 5: 2, 6: 6, 7: 4, 8: 1, 9: 1, 10: 2, 12: 6}


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def argument_size(opcode, header, prefix):
    if opcode == 0:
        return 2 * header[2]
    if opcode == 11:
        if len(prefix) < 2:
            raise ValueError("truncated opcode 11 prefix")
        return 2 + 2 * max(1, prefix[0])
    return FIXED_WIDTHS.get(opcode, 0)


def encode_script(script):
    size = script["span_bytes"]
    header = script["header_prefix"]
    commands = script["commands"]
    if (type(size) is not int or size < 6 or len(header) != 3 or
            any(type(value) is not int or not 0 <= value <= 255 for value in header) or
            not 1 <= len(commands) <= 255):
        raise ValueError("graphics action script header differs")
    result, covered = bytearray(size), bytearray(size)

    def write(offset, data):
        if offset < 0 or offset + len(data) > size:
            raise ValueError("graphics action field leaves its bounded span")
        for index, value in enumerate(data):
            position = offset + index
            if covered[position] and result[position] != value:
                raise ValueError("graphics action fields overlap inconsistently")
            result[position] = value
            covered[position] = 1

    write(0, bytes(header + [len(commands)]) +
          struct.pack("<H", script["initial_delay"]))
    command_end = 6 + 6 * len(commands)
    for index, command in enumerate(commands):
        opcode, flags = command["opcode"], command["flags"]
        offset = command["argument_offset"]
        argument = command["argument"]
        if (type(opcode) is not int or not 0 <= opcode <= 13 or
                type(flags) is not int or not 0 <= flags <= 255 or
                type(offset) is not int or offset < 0):
            raise ValueError("graphics action command metadata differs")
        if opcode in (8, 9):
            data = bytes(argument["bytes"])
        elif opcode == 11:
            data = bytes(argument["prefix"])
            data += b"".join(struct.pack("<H", value)
                             for value in argument["halfwords"])
        else:
            data = b"".join(struct.pack("<H", value)
                             for value in argument["halfwords"])
        if len(data) != argument_size(opcode, script["header_prefix"], data):
            raise ValueError("graphics action argument width differs")
        if data and offset < command_end:
            raise ValueError("graphics action payload overlaps command stream")
        write(6 + index * 6, struct.pack("<BBHH", opcode, flags,
                                         command["duration"], offset))
        if data:
            write(offset, data)
    for offset in script.get("halfword_alignment_offsets", []):
        if type(offset) is not int or offset % 2 != 1:
            raise ValueError("graphics action halfword alignment differs")
        write(offset, b"\0")
    padding = script["padding_bytes"]
    if type(padding) is not int or not 0 <= padding <= 3:
        raise ValueError("graphics action word alignment differs")
    if padding:
        write(size - padding, bytes(padding))
    if not all(covered):
        raise ValueError("graphics action span contains unclassified bytes")
    return bytes(result)


def decode_script(data, start=0):
    if start < 0 or start + 12 > len(data):
        raise ValueError("graphics action header leaves pointer root")
    header = list(data[start:start + 3])
    count = data[start + 3]
    command_end = 6 + 6 * count
    if not count or start + command_end > len(data):
        raise ValueError("graphics action command table leaves pointer root")
    commands = []
    payload_end = command_end
    byte_argument_ends = set()
    halfword_argument_starts = set()
    for index in range(count):
        at = start + 6 + index * 6
        opcode, flags, duration, offset = struct.unpack_from("<BBHH", data, at)
        if opcode > 13 or offset > len(data) - start:
            raise ValueError("graphics action opcode or offset leaves pointer root")
        prefix = data[start + offset:start + offset + 2]
        length = argument_size(opcode, header, prefix)
        if length and (offset < command_end or start + offset + length > len(data)):
            raise ValueError("graphics action payload leaves pointer root")
        payload = data[start + offset:start + offset + length]
        if opcode in (8, 9):
            fields = {"bytes": list(payload)}
            if length:
                byte_argument_ends.add(offset + length)
        elif opcode == 11:
            fields = {"prefix": list(payload[:2]),
                      "halfwords": list(struct.unpack("<" + "H" * ((length - 2) // 2),
                                                       payload[2:]))}
            halfword_argument_starts.add(offset)
        else:
            fields = {"halfwords": list(struct.unpack("<" + "H" * (length // 2),
                                                       payload))}
            if length and opcode not in (1, 2, 13):
                halfword_argument_starts.add(offset)
        commands.append({"opcode": opcode, "flags": flags, "duration": duration,
                         "argument_offset": offset, "argument": fields})
        if length:
            payload_end = max(payload_end, offset + length)
    span_end = payload_end
    padding = (-span_end) & 3
    if start + span_end + padding > len(data) or any(data[start + span_end:start + span_end + padding]):
        padding = 0
    span_bytes = span_end + padding
    script = {"header_prefix": header,
              "initial_delay": struct.unpack_from("<H", data, start + 4)[0],
              "commands": commands, "span_bytes": span_bytes,
              "padding_bytes": padding}
    alignment = [offset for offset in byte_argument_ends
                 if offset % 2 == 1 and offset + 1 in halfword_argument_starts and
                 offset < span_bytes and data[start + offset] == 0]
    if alignment:
        script["halfword_alignment_offsets"] = sorted(alignment)
    provisional = encode_script(script)
    if provisional != data[start:start + span_bytes]:
        raise ValueError("graphics action script does not round-trip")
    return script, span_bytes


def encode_bank(manifest, directory):
    if (manifest.get("schema_version") != 1 or
            manifest.get("reference_sha256") != ROM_SHA256 or
            (manifest.get("start"), manifest.get("end_exclusive")) != (START, END) or
            manifest.get("script_count") != 255 or len(manifest.get("records", [])) != 255 or
            len(manifest.get("roots", [])) != 73):
        raise ValueError("graphics action bank descriptor differs")
    output = bytearray()
    expected = START
    for record in manifest["records"]:
        if record.get("start") != expected or record.get("end_exclusive", 0) <= expected:
            raise ValueError("graphics action record boundaries are not contiguous")
        script_path = (directory / record["file"]).resolve()
        if not script_path.is_relative_to(directory.resolve()) or not script_path.is_file():
            raise ValueError("graphics action script source is missing")
        script = json.loads(script_path.read_text())
        encoded = encode_script(script)
        if (len(encoded) != record["end_exclusive"] - record["start"] or
                sha256(encoded) != record.get("source_sha256")):
            raise ValueError("graphics action script source hash/span differs")
        output.extend(encoded)
        expected = record["end_exclusive"]
    if expected != END or len(output) != END - START:
        raise ValueError("graphics action bank extent differs")
    return bytes(output)


def export(rom, output):
    if len(rom) != 0x1000000 or sha256(rom) != ROM_SHA256:
        raise ValueError("expected pinned US retail ROM")
    output = Path(output)
    output.mkdir(parents=True, exist_ok=True)
    pointers = {}
    for site in range(POINTER_WINDOW[0], POINTER_WINDOW[1], 4):
        target = struct.unpack_from("<I", rom, site)[0] - ROM_BASE
        if START <= target < END:
            pointers.setdefault(target, []).append(site)
    roots = sorted(pointers)
    if len(roots) != 73 or roots[0] != START:
        raise ValueError("graphics action pointer roots differ")
    records, root_rows, padding = [], [], 0
    cursor = START
    for root, root_end in zip(roots, roots[1:] + [END]):
        root_records = []
        while cursor < root_end:
            script, span = decode_script(rom[root:root_end], cursor - root)
            script_start = cursor
            script_end = script_start + span
            if script_end > root_end:
                raise ValueError("graphics action script crosses pointer root")
            file_name = f"action-{script_start:08x}.json"
            (output / file_name).write_text(json.dumps(script, indent=2, sort_keys=True) + "\n")
            encoded = encode_script(script)
            records.append({"start": script_start, "end_exclusive": script_end,
                            "root": root, "root_end": root_end, "file": file_name,
                            "source_sha256": sha256(encoded),
                            "padding_bytes": script["padding_bytes"] +
                                             len(script.get("halfword_alignment_offsets", []))})
            root_records.append(script_start)
            padding += records[-1]["padding_bytes"]
            cursor = script_end
        if cursor != root_end:
            raise ValueError("graphics action root end differs")
        root_rows.append({"start": root, "end_exclusive": root_end,
                          "pointer_sites": pointers[root], "record_starts": root_records})
    manifest = {"schema_version": 1, "reference_sha256": ROM_SHA256,
                "start": START, "end_exclusive": END,
                "pointer_table_window": list(POINTER_WINDOW), "roots": root_rows,
                "records": records, "script_count": len(records),
                "padding_bytes": padding,
                "typed_bytes": END - START - padding}
    if len(records) != 255 or padding != 292 or encode_bank(manifest, output) != rom[START:END]:
        raise ValueError("graphics action bank coverage differs")
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n")
    return manifest
