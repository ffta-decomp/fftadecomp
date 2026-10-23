#!/usr/bin/env python3
"""Extract US retail word tables, scene text/scripts, and 4bpp font outside source."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
from font_codec import decode_atlas
from ability_definition_codec import (decode_ability_definitions,
                                      encode_ability_definitions,
                                      TABLE_SIZE as ABILITY_TABLE_SIZE)
from scene_text_codec import parse_compression
from job_definition_codec import (decode_job_definitions, encode_job_definitions,
                                  TABLE_SIZE as JOB_TABLE_SIZE)
from item_definition_codec import (decode_item_definitions, encode_item_definitions,
                                   TABLE_SIZE as ITEM_TABLE_SIZE)
from mission_definition_codec import (decode_mission_definitions,
                                      encode_mission_definitions,
                                      TABLE_SIZE as MISSION_TABLE_SIZE)
from consumer_indexed_table_codec import (
    decode_equipment_masks, encode_equipment_masks,
    decode_mission_property_rows, encode_mission_property_rows,
    EQUIPMENT_MASK_START, EQUIPMENT_MASK_COUNT,
    MISSION_PROPERTY_ROW_START, MISSION_PROPERTY_ROW_COUNT,
    MISSION_PROPERTY_ROW_BYTES)
from item_ability_set_codec import (decode_item_ability_sets,
                                    encode_item_ability_sets,
                                    TABLE_SIZE as ITEM_ABILITY_SET_SIZE)
from unit_record_codec import (decode_unit_records, encode_unit_records,
                               TABLE_ROM_OFFSET, TABLE_SIZE)

RETAIL_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
SYSTEM_TABLE_POINTER_OFFSET = 0x39f54
SYSTEM_ENTRY_COUNT = 0x54
WORD_TABLES = {
    "ico": (0x198d0, 0x0a),
    "uitm": (0x538b8, 0x04),
    "content": (0x18da4, 0x2f2),
    "refer": (0x9a08, 0x6b),
    "battle": (0x9028, 0x2ff),
    "rumor": (0x5fd9c, 0x5c),
    "quest": (0x191f0, 0x200),
    "clan": (0x9a10, 0x80),
    "system": (SYSTEM_TABLE_POINTER_OFFSET, SYSTEM_ENTRY_COUNT),
    "name": (0xc9ed0, 0x2d5),
    "title": (0x192bc, 0x34),
}
SCENE_TEXT_POINTER_OFFSET = 0x9a88
SCENE_PAGE_COUNT = 63
SCENE_SCRIPT_POINTER_OFFSET = 0x1223c0
SCENE_COMMAND_POINTER_OFFSET = 0x122b10
FIXED_TEXT_POINTER_OFFSET = 0x18050
FIXED_TEXT_PAGE_COUNT = 27
CONSUMER_TEXT_PAGES = ((0x497418, 0x49B1C7, 401, 0x08013E9C),
                       (0x4A002C, 0x4AADFC, 200, 0x08013E9C),
                       (0x4AADFC, 0x4B5374, 311, 0x08013E9C),
                       (0x4B64A4, 0x4B683C, 51, 0x08013E9C),
                       (0x4B83A0, 0x4B8882, 21, 0x08013E9C),
                       (0x4C3D50, 0x4C3E5D, 2, 0x08013E9C),
                       (0x4E8FD4, 0x4E9363, 10, 0x08013E9C),
                       (0x4EF3F4, 0x4EF9D8, 29, 0x08013E9C))
FONT_POINTER_OFFSET = 0x13474
FONT_GLYPH_COUNT = 0xc67
FONT_GLYPH_BYTES = 128
FONT_ATLAS_COLUMNS = 64
DISPLAY_MASK_TABLE_OFFSET = 0x149550
DISPLAY_MASK_HALFWORDS = 8

# GBA FFTA US character codes. Unknown codes remain explicit in exported text.
KANA = 'ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむめもゃやゅゆょよらりるれろゎわをんァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロヮワヲンヴ、。ー'
PUNCT = ".「」『』…?!,·:_々/~‘’“”(){}[]+-±"
EXTRA = "×=<>∞♂♀%&*※—|↑↓←→○△□■^;◎"
PARAMETER_BYTES = {
    **{x: 0 for x in (0x40, 0x41, 0x42, 0x4a, 0x4d, 0x4f, 0x52, 0x54, 0x56, 0x57, 0x58)},
    **{x: 1 for x in (0x00, 0x1b, 0x1d, 0x46, 0x4b, 0x51, 0x53, 0x32, 0x04)},
    0x45: 2,
}
ALT_CONTROL_CODES = (0x04, 0x46, 0x4b, 0x45, 0x45, None, 0x53, 0x51,
                     0x4d, 0x52, 0x42, 0x57, 0x54, 0x40, 0x4f, 0x41,
                     0x56, 0x4a, None, 0x1b, 0x1d, 0x58, 0x00)


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def rom_offset(pointer, size):
    offset = pointer - ROM_BASE
    if not 0 <= offset < size:
        raise ValueError(f"Pointer outside ROM: 0x{pointer:08x}")
    return offset


def char(code):
    if 0 <= code < len(KANA):
        return KANA[code]
    if 0xa6 <= code <= 0xaf:
        return chr(ord("0") + code - 0xa6)
    if 0xb0 <= code <= 0xc9:
        return chr(ord("A") + code - 0xb0)
    if 0xca <= code <= 0xe3:
        return chr(ord("a") + code - 0xca)
    if 0xe4 <= code <= 0xff:
        return PUNCT[code - 0xe4]
    if 0x100 <= code <= 0x117:
        return EXTRA[code - 0x100]
    return f"<glyph:{code:04x}>"


def decode_word(data, offset):
    cursor = offset
    decoded = []
    tokens = []
    half_mode = False
    direct_strings_remaining = 0
    while cursor < len(data) and cursor - offset < 4096:
        byte = data[cursor]
        cursor += 1
        if byte == 0:
            if direct_strings_remaining:
                direct_strings_remaining -= 1
                tokens.append({"type": "control_eos"})
                decoded.append("@[ ]")
                continue
            break
        if byte == 1:
            half_mode = True
            continue
        if half_mode:
            code = byte - 1
            tokens.append({"type": "half_glyph", "code": code})
            decoded.append(char(code))
        elif byte == 0x40:
            code = data[cursor] - 0x21
            cursor += 1
            if code not in PARAMETER_BYTES:
                raise ValueError(f"Unknown control code 0x{code:02x} at 0x{cursor - 2:x}")
            length = PARAMETER_BYTES[code]
            params = data[cursor:cursor + length]
            cursor += length
            tokens.append({"type": "control", "code": code, "parameters_hex": params.hex()})
            if code == 4:
                value = 0x400 | params[0]
            elif code == 0x32:
                value = 0x3200 | params[0]
                direct_strings_remaining = 2
            else:
                value = 1 if code == 0 else code
                for parameter in params:
                    value = (value << 8) | parameter
            decoded.append(" " if code == 0x52 else f"@[{value:X}]")
        elif byte & 0x80:
            code = ((byte & 0x7f) << 8) | data[cursor]
            cursor += 1
            tokens.append({"type": "full_glyph", "code": code})
            decoded.append(char(code))
        else:
            raise ValueError(f"Unknown text byte 0x{byte:02x} at 0x{cursor - 1:x}")
    else:
        raise ValueError(f"Unterminated text at ROM offset 0x{offset:x}")
    raw = data[offset:cursor]
    return {"rom_offset": offset, "size": len(raw), "raw_sha256": hashlib.sha256(raw).hexdigest(),
            "text": "".join(decoded), "tokens": tokens}


def decode_alt_word(data, offset):
    cursor = offset
    decoded = []
    tokens = []
    while cursor < len(data) and cursor - offset < 4096:
        byte = data[cursor]
        cursor += 1
        if byte == 0xff:
            break
        if byte < 0x80:
            code = data[cursor]
            cursor += 1
            tokens.append({"type": "half_glyph", "code": code})
            decoded.append(char(code))
            continue
        opcode = byte - 0x80
        if opcode >= len(ALT_CONTROL_CODES) or ALT_CONTROL_CODES[opcode] is None:
            raise ValueError(f"Unknown alternate control code 0x{opcode:02x}")
        code = ALT_CONTROL_CODES[opcode]
        if opcode in (3, 4):
            value = (0x454c00 if opcode == 3 else 0x455200) | data[cursor]
            params = data[cursor:cursor + 1]
            cursor += 1
        else:
            length = PARAMETER_BYTES[code]
            params = data[cursor:cursor + length]
            cursor += length
            value = code
            for parameter in params:
                value = (value << 8) | parameter
        tokens.append({"type": "control", "code": code, "parameters_hex": params.hex(),
                       "value": value})
        decoded.append(" " if value == 0x52 else f"@[{value:X}]")
    else:
        raise ValueError(f"Unterminated alternate text at offset 0x{offset:x}")
    raw = data[offset:cursor]
    return {"rom_offset": offset, "size": len(raw), "raw_sha256": hashlib.sha256(raw).hexdigest(),
            "text": "".join(decoded), "tokens": tokens}



def decode_lzss_line(data, cursor, expected):
    if not 0 < expected <= 65536:
        raise ValueError("Invalid scene text output length")
    out = bytearray()
    start = cursor
    while len(out) < expected and cursor - start < 65536:
        command = data[cursor]
        cursor += 1
        if command & 0x80:
            length = ((command >> 3) & 15) + 3
            distance = (((command & 7) << 8) | data[cursor]) + 1
            cursor += 1
            for _ in range(length):
                if not 0 < distance <= len(out):
                    raise ValueError("Invalid scene text back-reference")
                out.append(out[-distance])
        elif command & 0x40:
            length = (command & 63) + 1
            out.extend(data[cursor:cursor + length])
            cursor += length
        elif command & 0x20:
            out.extend(bytes((0,)) * ((command & 31) + 2))
        elif command & 0x10:
            second, third = data[cursor:cursor + 2]
            cursor += 2
            length = (((second & 0xc0) >> 2) | (command & 15)) + 4
            distance = (((second & 63) << 8) | third) + 1
            for _ in range(length):
                if not 0 < distance <= len(out):
                    raise ValueError("Invalid scene text back-reference")
                out.append(out[-distance])
        elif command in (1, 2):
            length = data[cursor] + 3
            cursor += 1
            out.extend(bytes((0xff if command == 1 else 0,)) * length)
        elif command == 0:
            length = data[cursor] + 5
            distance = ((data[cursor + 1] << 8) | data[cursor + 2]) + 1
            cursor += 3
            for _ in range(length):
                if not 0 < distance <= len(out):
                    raise ValueError("Invalid scene text back-reference")
                out.append(out[-distance])
        else:
            raise ValueError(f"Unknown scene text compression command {command}")
        if len(out) > expected:
            raise ValueError("Scene text decompression overrun")
    if len(out) != expected:
        raise ValueError("Scene text decompression truncated")
    return bytes(out), cursor - start


def extract_scene_page(data, page_index, subpage_index=None):
    table = rom_offset(u32(data, SCENE_TEXT_POINTER_OFFSET), len(data))
    page = table + u32(data, table + page_index * 4)
    if subpage_index is not None:
        page = table + u32(data, page + subpage_index * 4)
    result = extract_text_page_at(data, page, page_index)
    result.update({"table_rom_offset": table, "subpage_index": subpage_index})
    return result


def extract_text_page_at(data, page, page_index):
    entry_count = struct.unpack_from("<H", data, page)[0] // 2 - 1
    if not 0 < entry_count < 4096:
        raise ValueError("Invalid scene text page entry count")
    entries = []
    for index in range(entry_count):
        offset = page + struct.unpack_from("<H", data, page + index * 2)[0]
        flags = struct.unpack_from("<H", data, offset)[0]
        if flags & 2:
            size = int.from_bytes(data[offset + 2:offset + 6], "big")
            operations, payload, consumed = parse_compression(memoryview(data)[offset + 6:], size)
            checked_payload, checked_consumed = decode_lzss_line(data, offset + 6, size)
            if (payload, consumed) != (checked_payload, checked_consumed):
                raise ValueError("Scene text compression decoders disagree")
            compressed_size = consumed + 6
        else:
            payload = data[offset + 2:]
            compressed_size = None
        item = (decode_alt_word if flags & 1 else decode_word)(payload, 0)
        entries.append({"index": index, "rom_offset": offset, "flags": flags,
                        "encoding": "alternate" if flags & 1 else "standard",
                        "compressed": bool(flags & 2), "compressed_size": compressed_size,
                        "compression_ops": operations if flags & 2 else None,
                        "decoded_tail_hex": payload[item["size"]:].hex() if flags & 2 else None,
                        "decoded_size": item["size"], "decoded_sha256": item["raw_sha256"],
                        "text": item["text"], "tokens": item["tokens"]})
    return {"reference_sha256": RETAIL_SHA256, "page_index": page_index,
            "page_rom_offset": page,
            "entry_count": entry_count, "entries": entries}


def attach_text_page_end(data, page, end):
    entries = page["entries"]
    if end <= page["page_rom_offset"] or end > len(data):
        raise ValueError("Invalid text page boundary")
    page["page_end_exclusive"] = end
    retained = 0
    for index, entry in enumerate(entries):
        line_end = entries[index + 1]["rom_offset"] if index + 1 < len(entries) else end
        used = entry["compressed_size"] if entry["compressed"] else 2 + entry["decoded_size"]
        if line_end < entry["rom_offset"] + used:
            raise ValueError("Overlapping text entries")
        trailing = data[entry["rom_offset"] + used:line_end]
        entry["line_padding_hex"] = trailing.hex()
        retained += len(trailing)
    return retained


def extract_scene_scripts(data):
    table = rom_offset(u32(data, SCENE_SCRIPT_POINTER_OFFSET), len(data))
    text_table = rom_offset(u32(data, SCENE_TEXT_POINTER_OFFSET), len(data))
    group_count = u32(data, table) // 4
    descriptors = rom_offset(u32(data, SCENE_COMMAND_POINTER_OFFSET), len(data))
    groups = []
    for group_index in range(group_count):
        group = table + u32(data, table + group_index * 4)
        group_end = (table + u32(data, table + (group_index + 1) * 4)
                     if group_index + 1 < group_count else text_table)
        if not table < group < group_end <= text_table:
            raise ValueError(f"Invalid scene script group {group_index}")
        pointer_count = u32(data, group) // 4
        starts = [group + u32(data, group + i * 4) for i in range(pointer_count)]
        if any(not group <= start <= group_end for start in starts) or starts != sorted(starts):
            raise ValueError(f"Invalid scene script program pointers in group {group_index}")
        # A pointer to the group end is a sentinel, not an empty program.
        starts = [start for start in starts if start < group_end]
        programs = []
        for program_index, program in enumerate(starts):
            program_end = starts[program_index + 1] if program_index + 1 < len(starts) else group_end
            cursor = program
            commands = []
            while cursor < program_end:
                if data[cursor:program_end] == bytes((0xff,)) * (program_end - cursor):
                    if program_index + 1 < len(starts) or program_end - cursor > 3:
                        raise ValueError(f"Unexpected scene script padding at 0x{cursor:x}")
                    break
                opcode = data[cursor]
                descriptor = descriptors + opcode * 6
                length = struct.unpack_from("<H", data, descriptor)[0]
                if not 1 <= length <= 64 or cursor + length > program_end:
                    raise ValueError(f"Invalid scene script command at 0x{cursor:x}")
                commands.append({"rom_offset": cursor, "program_offset": cursor - program,
                                 "opcode": opcode, "size": length,
                                 "parameters_hex": data[cursor + 1:cursor + length].hex(),
                                 "handler_address": f"0x{u32(data, descriptor + 2):08x}"})
                cursor += length
            programs.append({"group_index": group_index, "program_index": program_index,
                             "program_rom_offset": program, "program_end_exclusive": program_end,
                             "program_size": cursor - program,
                             "padding_size": program_end - cursor,
                             "program_sha256": hashlib.sha256(data[program:cursor]).hexdigest(),
                             "command_count": len(commands), "commands": commands})
        groups.append({"group_index": group_index, "group_rom_offset": group,
                       "group_end_exclusive": group_end,
                       "program_count": len(programs), "programs": programs})
    return {"reference_sha256": RETAIL_SHA256,
            "script_table_rom_offset": table, "command_table_rom_offset": descriptors,
            "group_count": group_count,
            "program_count": sum(g["program_count"] for g in groups),
            "command_count": sum(p["command_count"] for g in groups for p in g["programs"]),
            "groups": groups}

def write_font_preview(font, path):
    # 16 columns x 16 rows of 16x16 glyphs; raw nibble order is low then high.
    width = height = 256
    pixels = bytearray(width * height * 3)
    for glyph in range(256):
        raw = font[glyph * FONT_GLYPH_BYTES:(glyph + 1) * FONT_GLYPH_BYTES]
        gx = (glyph % 16) * 16
        gy = (glyph // 16) * 16
        for y in range(16):
            for x in range(16):
                byte = raw[(x // 8) * 64 + y * 4 + (x % 8) // 2]
                value = ((byte >> (4 * (x % 2))) & 15) * 17
                p = ((gy + y) * width + gx + x) * 3
                pixels[p:p + 3] = bytes((value, value, value))
    path.write_bytes(f"P6\n{width} {height}\n255\n".encode() + pixels)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    if args.output_dir.resolve().is_relative_to(root) or args.rom.resolve() == args.output_dir.resolve():
        raise SystemExit("Extraction output must be outside the source tree")
    data = args.rom.read_bytes()
    if hashlib.sha256(data).hexdigest() != RETAIL_SHA256:
        raise SystemExit("Input is not the pinned US retail ROM")
    output = args.output_dir
    output.mkdir(parents=True, exist_ok=True)
    unit_records = decode_unit_records(data)
    if encode_unit_records(unit_records) != data[TABLE_ROM_OFFSET:TABLE_ROM_OFFSET + TABLE_SIZE]:
        raise ValueError("Indexed unit-record round trip differs from retail")
    (output / "unit-records14.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **unit_records,
    }, indent=2) + "\n")
    job_definitions = decode_job_definitions(data)
    job_start = job_definitions["rom_offset"]
    if encode_job_definitions(job_definitions) != data[job_start:job_start + JOB_TABLE_SIZE]:
        raise ValueError("Job-definition round trip differs from retail")
    (output / "job-definitions.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **job_definitions,
    }, indent=2) + "\n")
    ability_definitions = decode_ability_definitions(data)
    ability_start = ability_definitions["rom_offset"]
    if encode_ability_definitions(ability_definitions) != \
            data[ability_start:ability_start + ABILITY_TABLE_SIZE]:
        raise ValueError("Ability-definition round trip differs from retail")
    (output / "ability-definitions.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **ability_definitions,
    }, indent=2) + "\n")
    item_definitions = decode_item_definitions(data)
    item_start = item_definitions["rom_offset"]
    if encode_item_definitions(item_definitions) != \
            data[item_start:item_start + ITEM_TABLE_SIZE]:
        raise ValueError("Item-definition round trip differs from retail")
    (output / "item-definitions.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **item_definitions,
    }, indent=2) + "\n")
    mission_definitions = decode_mission_definitions(data)
    mission_start = mission_definitions["rom_offset"]
    if encode_mission_definitions(mission_definitions) != \
            data[mission_start:mission_start + MISSION_TABLE_SIZE]:
        raise ValueError("Mission-definition round trip differs from retail")
    (output / "mission-definitions.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **mission_definitions,
    }, indent=2) + "\n")
    indexed_tables_dir = output / "consumer-indexed-tables"
    indexed_tables_dir.mkdir(exist_ok=True)
    equipment_masks = decode_equipment_masks(data)
    if encode_equipment_masks(equipment_masks) != data[
            EQUIPMENT_MASK_START:EQUIPMENT_MASK_START + EQUIPMENT_MASK_COUNT * 4]:
        raise ValueError("Equipment mask round trip differs from retail")
    (indexed_tables_dir / "equipment-class-masks.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **equipment_masks,
    }, indent=2) + "\n")
    mission_property_rows = decode_mission_property_rows(data)
    mission_rows_end = (MISSION_PROPERTY_ROW_START +
                        MISSION_PROPERTY_ROW_COUNT * MISSION_PROPERTY_ROW_BYTES)
    if encode_mission_property_rows(mission_property_rows) != data[
            MISSION_PROPERTY_ROW_START:mission_rows_end]:
        raise ValueError("Mission property row round trip differs from retail")
    (indexed_tables_dir / "mission-property60-rows.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **mission_property_rows,
    }, indent=2) + "\n")
    item_ability_sets = decode_item_ability_sets(data)
    ability_set_start = item_ability_sets["rom_offset"]
    if encode_item_ability_sets(item_ability_sets) != \
            data[ability_set_start:ability_set_start + ITEM_ABILITY_SET_SIZE]:
        raise ValueError("Item-ability-set round trip differs from retail")
    (output / "item-ability-sets.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, **item_ability_sets,
    }, indent=2) + "\n")
    display_masks = struct.unpack_from(
        f"<{DISPLAY_MASK_HALFWORDS}H", data, DISPLAY_MASK_TABLE_OFFSET)
    (output / "display-mask-tables.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256,
        "rom_offset": DISPLAY_MASK_TABLE_OFFSET,
        "values": list(display_masks),
    }, indent=2) + "\n")
    tables = {}
    for name, (pointer_site, count) in WORD_TABLES.items():
        table = rom_offset(u32(data, pointer_site), len(data))
        words = []
        for index in range(count):
            entry = table + index * 4
            pointer = u32(data, entry)
            if pointer == 0:
                words.append({"index": index, "pointer_rom_offset": entry, "status": "null"})
                continue
            try:
                offset = rom_offset(pointer, len(data))
                item = decode_word(data, offset)
                item.update({"index": index, "pointer_rom_offset": entry, "status": "decoded"})
            except ValueError as error:
                item = {"index": index, "pointer_rom_offset": entry,
                        "status": "unresolved", "reason": str(error)}
            words.append(item)
        tables[name] = {"table_pointer_rom_offset": pointer_site,
                        "table_rom_offset": table, "entry_count": count,
                        "decoded_entries": sum(x["status"] == "decoded" for x in words),
                        "entries": words}
    (output / "word-tables.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, "tables": tables,
    }, indent=2, ensure_ascii=False) + "\n")
    (output / "system-words.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256,
        "table_pointer_rom_offset": SYSTEM_TABLE_POINTER_OFFSET,
        "table_rom_offset": tables["system"]["table_rom_offset"],
        "entry_count": SYSTEM_ENTRY_COUNT,
        "entries": tables["system"]["entries"],
    }, indent=2, ensure_ascii=False) + "\n")
    scene_table = rom_offset(u32(data, SCENE_TEXT_POINTER_OFFSET), len(data))
    page_count = SCENE_PAGE_COUNT
    pages = []
    for index in range(page_count):
        if index == 61:
            subpages = []
            for subindex in range(26):
                try:
                    subpage = extract_scene_page(data, index, subindex)
                    subpage["status"] = "decoded"
                except (ValueError, IndexError, struct.error) as error:
                    subpage = {"page_index": index, "subpage_index": subindex,
                               "status": "unresolved", "reason": str(error)}
                subpages.append(subpage)
            page = {"page_index": index, "status": "group", "subpage_count": 26,
                    "subpages": subpages}
        else:
            try:
                page = extract_scene_page(data, index)
                page["status"] = "decoded"
            except (ValueError, IndexError, struct.error) as error:
                page = {"page_index": index, "status": "unresolved", "reason": str(error)}
        pages.append(page)
    # Pages can alias one another and the outer pointer order is not monotone.
    unique_pages = {}
    for page in pages:
        sections = page["subpages"] if page["status"] == "group" else [page]
        for section in sections:
            if section["status"] == "decoded":
                unique_pages.setdefault(section["page_rom_offset"], section)
    scene_text_end = 0xa19970
    boundaries = sorted(set(unique_pages) | {scene_text_end, pages[61]["subpages"][0]["page_rom_offset"] - 104})
    for start, page in unique_pages.items():
        page_end = boundaries[boundaries.index(start) + 1]
        for i, entry in enumerate(page["entries"]):
            line_end = (page["entries"][i + 1]["rom_offset"] if i + 1 < len(page["entries"])
                        else page_end)
            used = entry["compressed_size"] if entry["compressed"] else 2 + entry["decoded_size"]
            if line_end < entry["rom_offset"] + used:
                raise ValueError("Overlapping scene text entries")
            entry["line_padding_hex"] = data[entry["rom_offset"] + used:line_end].hex()
    # Copy metadata to aliased page views so each decoded page remains standalone.
    for page in pages:
        sections = page["subpages"] if page["status"] == "group" else [page]
        for section in sections:
            if section["status"] == "decoded" and section is not unique_pages[section["page_rom_offset"]]:
                for entry, primary in zip(section["entries"], unique_pages[section["page_rom_offset"]]["entries"]):
                    entry["line_padding_hex"] = primary["line_padding_hex"]
    pages[61]["group_rom_offset"] = scene_table + int.from_bytes(data[scene_table + 61 * 4:scene_table + 61 * 4 + 4], "little")
    group_end = pages[61]["subpages"][0]["page_rom_offset"]
    pages[61]["group_padding_hex"] = data[pages[61]["group_rom_offset"] + 26 * 4:group_end].hex()
    (output / "scene-text-pages.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, "page_count": page_count,
        "table_rom_offset": scene_table, "end_exclusive": scene_text_end,
        "pages": pages,
    }, indent=2, ensure_ascii=False) + "\n")
    scene = pages[1]
    (output / "scene-page-1.json").write_text(json.dumps(scene, indent=2, ensure_ascii=False) + "\n")
    fixed_table = rom_offset(u32(data, FIXED_TEXT_POINTER_OFFSET), len(data))
    fixed_pages = []
    for index in range(FIXED_TEXT_PAGE_COUNT):
        pointer = u32(data, fixed_table + index * 4)
        if pointer == 0:
            fixed_pages.append({"page_index": index, "status": "null"})
        else:
            page = extract_text_page_at(data, rom_offset(pointer, len(data)), index)
            page["status"] = "decoded"
            fixed_pages.append(page)
    fixed_unique = {}
    for page in fixed_pages:
        if page["status"] == "decoded":
            fixed_unique.setdefault(page["page_rom_offset"], page)
    for page in fixed_unique.values():
        entries = page["entries"]
        last = entries[-1]
        last_used = last["compressed_size"] if last["compressed"] else 2 + last["decoded_size"]
        page_end = (last["rom_offset"] + last_used + 3) & ~3
        attach_text_page_end(data, page, page_end)
    for page in fixed_pages:
        if page["status"] == "decoded" and page is not fixed_unique[page["page_rom_offset"]]:
            primary = fixed_unique[page["page_rom_offset"]]
            page["page_end_exclusive"] = primary["page_end_exclusive"]
            for entry, original in zip(page["entries"], primary["entries"]):
                entry["line_padding_hex"] = original["line_padding_hex"]
    consumer_pages = []
    for start, end, count, consumer in CONSUMER_TEXT_PAGES:
        page = extract_text_page_at(data, start, None)
        if page["entry_count"] != count:
            raise ValueError("Consumer-backed text page count differs")
        retained = attach_text_page_end(data, page, end)
        page.update({"status": "decoded", "consumer_thumb": consumer,
                     "retained_trailing_bytes": retained,
                     "scope": "Trailing bytes are preserved; their role is not established."})
        consumer_pages.append(page)
    (output / "fixed-text-pages.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256, "table_rom_offset": fixed_table,
        "page_count": FIXED_TEXT_PAGE_COUNT, "pages": fixed_pages,
        "consumer_pages": consumer_pages,
    }, indent=2, ensure_ascii=False) + "\n")
    scripts = extract_scene_scripts(data)
    (output / "scene-scripts.json").write_text(json.dumps(scripts, indent=2) + "\n")
    first_script = scripts["groups"][0]["programs"][0].copy()
    first_script.update({"reference_sha256": RETAIL_SHA256,
                         "script_table_rom_offset": scripts["script_table_rom_offset"],
                         "command_table_rom_offset": scripts["command_table_rom_offset"]})
    (output / "scene-script-0-0.json").write_text(json.dumps(first_script, indent=2) + "\n")
    font_start = rom_offset(u32(data, FONT_POINTER_OFFSET), len(data))
    font_size = FONT_GLYPH_COUNT * FONT_GLYPH_BYTES
    font = data[font_start:font_start + font_size]
    if len(font) != font_size:
        raise SystemExit("Font extends beyond ROM")
    (output / "font-4bpp.bin").write_bytes(font)
    atlas = decode_atlas(font, FONT_GLYPH_COUNT, FONT_ATLAS_COLUMNS)
    (output / "font-atlas.pgm").write_bytes(atlas)
    write_font_preview(font, output / "font-preview-first-256.ppm")
    (output / "font.json").write_text(json.dumps({
        "reference_sha256": RETAIL_SHA256,
        "pointer_rom_offset": FONT_POINTER_OFFSET,
        "font_rom_offset": font_start,
        "glyph_count": FONT_GLYPH_COUNT,
        "glyph_size_bytes": FONT_GLYPH_BYTES,
        "glyph_dimensions": [16, 16],
        "bits_per_pixel": 4,
        "atlas_file": "font-atlas.pgm",
        "atlas_columns": FONT_ATLAS_COLUMNS,
        "atlas_sha256": hashlib.sha256(atlas).hexdigest(),
        "font_sha256": hashlib.sha256(font).hexdigest(),
    }, indent=2) + "\n")
    scene_entries = [entry for page in pages for section in
                     (page["subpages"] if page["status"] == "group" else [page])
                     for entry in section["entries"]]
    summary = {"reference_sha256": RETAIL_SHA256,
                      "word_entries": sum(t["entry_count"] for t in tables.values()),
                      "word_entries_decoded": sum(t["decoded_entries"] for t in tables.values()),
                      "system_entries": SYSTEM_ENTRY_COUNT, "system_table_offset": tables["system"]["table_rom_offset"],
                      "scene_pages": page_count,
                      "scene_pages_decoded": sum(p["status"] == "decoded" for p in pages),
                      "scene_subpages_decoded": sum(p["status"] == "decoded" for p in pages[61]["subpages"]),
                      "scene_entries": len(scene_entries),
                      "scene_standard_entries": sum(e["encoding"] == "standard" for e in scene_entries),
                      "scene_alternate_entries": sum(e["encoding"] == "alternate" for e in scene_entries),
                      "scene_compressed_entries": sum(e["compressed"] for e in scene_entries),
                      "scene_entries_with_unmapped_glyphs": sum("<glyph:" in e["text"] for e in scene_entries),
                      "scene_page_1_entries": scene["entry_count"],
                      "fixed_text_pages": FIXED_TEXT_PAGE_COUNT,
                      "fixed_text_pages_decoded": sum(p["status"] == "decoded" for p in fixed_pages),
                      "fixed_text_entries": sum(p.get("entry_count", 0) for p in fixed_pages),
                      "consumer_text_pages": len(consumer_pages),
                      "consumer_text_entries": sum(p["entry_count"] for p in consumer_pages),
                      "consumer_text_bytes": sum(p["page_end_exclusive"] - p["page_rom_offset"]
                                                 for p in consumer_pages),
                      "consumer_text_retained_trailing_bytes": sum(
                          p["retained_trailing_bytes"] for p in consumer_pages),
                      "scene_script_groups": scripts["group_count"],
                      "scene_script_programs": scripts["program_count"],
                      "scene_script_commands": scripts["command_count"],
                      "scene_script_0_0_commands": first_script["command_count"],
                      "font_offset": font_start, "font_bytes": font_size,
                      "display_mask_halfwords": DISPLAY_MASK_HALFWORDS,
                      "indexed_unit_records": unit_records["entry_count"],
                      "indexed_unit_record_bytes": TABLE_SIZE,
                      "job_definition_records": job_definitions["entry_count"],
                      "job_definition_bytes": JOB_TABLE_SIZE,
                      "ability_definition_records": ability_definitions["entry_count"],
                      "ability_definition_bytes": ABILITY_TABLE_SIZE,
                      "item_definition_records": item_definitions["entry_count"],
                      "item_definition_bytes": ITEM_TABLE_SIZE,
                      "mission_definition_records": mission_definitions["entry_count"],
                      "mission_definition_bytes": MISSION_TABLE_SIZE,
                      "item_ability_sets": item_ability_sets["entry_count"],
                      "item_ability_pairs": sum(record["count"] for record in item_ability_sets["records"]),
                      "item_ability_set_bytes": ITEM_ABILITY_SET_SIZE}
    (output / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary))


if __name__ == "__main__":
    main()
