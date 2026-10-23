"""Serialize extracted FFTA scene programs from command and pointer records."""
import hashlib
import struct


def word(value):
    if not 0 <= value <= 0xffffffff:
        raise ValueError("Script pointer does not fit in a word")
    return struct.pack("<I", value)


def encode_scene_scripts(source):
    table = source["script_table_rom_offset"]
    groups = source["groups"]
    if len(groups) != source["group_count"]:
        raise ValueError("Scene script group count differs")
    first_group = table + len(groups) * 4
    output = bytearray()
    output.extend(b"".join(word(group["group_rom_offset"] - table) for group in groups))
    if table + len(output) != first_group:
        raise ValueError("Scene script outer table has invalid length")
    command_count = 0
    program_count = 0
    for group_index, group in enumerate(groups):
        start = group["group_rom_offset"]
        end = group["group_end_exclusive"]
        if group["group_index"] != group_index or table + len(output) != start or end <= start:
            raise ValueError(f"Invalid scene script group boundary {group_index}")
        programs = group["programs"]
        if len(programs) != group["program_count"]:
            raise ValueError(f"Invalid scene script program count in group {group_index}")
        pointer_count = ((programs[0]["program_rom_offset"] - start) // 4 if programs
                         else (end - start) // 4)
        if pointer_count < len(programs) or pointer_count <= 0 or start + pointer_count * 4 > end:
            raise ValueError(f"Invalid scene script pointer table in group {group_index}")
        pointer_values = [program["program_rom_offset"] - start for program in programs]
        pointer_values.extend([end - start] * (pointer_count - len(programs)))
        chunk = bytearray(b"".join(word(value) for value in pointer_values))
        for program_index, program in enumerate(programs):
            if program["group_index"] != group_index or program["program_index"] != program_index:
                raise ValueError("Scene script program index differs")
            if start + len(chunk) != program["program_rom_offset"]:
                raise ValueError("Scene script program pointer differs")
            command_bytes = bytearray()
            for command in program["commands"]:
                if command["program_offset"] != len(command_bytes):
                    raise ValueError("Scene script command offset differs")
                opcode = command["opcode"]
                if not 0 <= opcode <= 255:
                    raise ValueError("Scene script opcode is not a byte")
                raw = bytes.fromhex(command["parameters_hex"])
                if command["size"] != len(raw) + 1:
                    raise ValueError("Scene script command size differs")
                command_bytes.append(opcode)
                command_bytes.extend(raw)
            if len(command_bytes) != program["program_size"]:
                raise ValueError("Scene script program size differs")
            if hashlib.sha256(command_bytes).hexdigest() != program["program_sha256"]:
                raise ValueError("Scene script program digest differs")
            chunk.extend(command_bytes)
            padding = program["padding_size"]
            if not 0 <= padding <= 3:
                raise ValueError("Invalid scene script alignment padding")
            chunk.extend(bytes((0xff,)) * padding)
            if start + len(chunk) != program["program_end_exclusive"]:
                raise ValueError("Scene script program end differs")
            command_count += len(program["commands"])
            program_count += 1
        if start + len(chunk) != end:
            raise ValueError(f"Scene script group size differs at {group_index}")
        output.extend(chunk)
    if program_count != source["program_count"] or command_count != source["command_count"]:
        raise ValueError("Scene script totals differ")
    return bytes(output)
