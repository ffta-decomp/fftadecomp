"""Lossless codecs for two retail tables with bounded index consumers."""

import struct

from mission_definition_codec import decode_mission_definitions


EQUIPMENT_MASK_START = 0x51D0F4
EQUIPMENT_MASK_COUNT = 35
MISSION_PROPERTY_ROW_START = 0x563A70
MISSION_PROPERTY_ROW_COUNT = 225
MISSION_PROPERTY_ROW_BYTES = 12


def decode_equipment_masks(rom):
    end = EQUIPMENT_MASK_START + EQUIPMENT_MASK_COUNT * 4
    if len(rom) < end:
        raise ValueError("equipment mask table exceeds input")
    values = struct.unpack_from(f"<{EQUIPMENT_MASK_COUNT}I", rom,
                                EQUIPMENT_MASK_START)
    return {"rom_offset": EQUIPMENT_MASK_START, "entry_size": 4,
            "entry_count": EQUIPMENT_MASK_COUNT,
            "entries": [{"index": index, "mask_u32": value}
                        for index, value in enumerate(values)]}


def encode_equipment_masks(asset):
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (EQUIPMENT_MASK_START, 4,
                                           EQUIPMENT_MASK_COUNT):
        raise ValueError("equipment mask table boundary differs")
    entries = asset.get("entries")
    if not isinstance(entries, list) or len(entries) != EQUIPMENT_MASK_COUNT:
        raise ValueError("equipment mask entry count differs")
    values = []
    for index, entry in enumerate(entries):
        value = entry.get("mask_u32")
        if (entry.get("index") != index or type(value) is not int or
                not 0 <= value <= 0xFFFFFFFF):
            raise ValueError("equipment mask entry differs")
        values.append(value)
    return struct.pack(f"<{EQUIPMENT_MASK_COUNT}I", *values)


def decode_mission_property_rows(rom):
    end = MISSION_PROPERTY_ROW_START + (MISSION_PROPERTY_ROW_COUNT *
                                        MISSION_PROPERTY_ROW_BYTES)
    if len(rom) < end:
        raise ValueError("mission property row table exceeds input")
    property_indices = {row["property60"] for row in
                        decode_mission_definitions(rom)["records"]}
    if min(property_indices) != 0 or max(property_indices) != 224:
        raise ValueError("mission property-60 index domain differs")
    rows = []
    for index in range(MISSION_PROPERTY_ROW_COUNT):
        start = MISSION_PROPERTY_ROW_START + index * MISSION_PROPERTY_ROW_BYTES
        rows.append({"index": index, "selector_byte_00": rom[start],
                     "unclassified_01_to_07_hex": rom[start + 1:start + 8].hex(),
                     "field_u16_08": struct.unpack_from("<H", rom, start + 8)[0],
                     "unclassified_0a_to_0b_hex": rom[start + 10:start + 12].hex()})
    return {"rom_offset": MISSION_PROPERTY_ROW_START,
            "entry_size": MISSION_PROPERTY_ROW_BYTES,
            "entry_count": MISSION_PROPERTY_ROW_COUNT,
            "rows": rows}


def encode_mission_property_rows(asset):
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (MISSION_PROPERTY_ROW_START,
                                           MISSION_PROPERTY_ROW_BYTES,
                                           MISSION_PROPERTY_ROW_COUNT):
        raise ValueError("mission property row table boundary differs")
    rows = asset.get("rows")
    if not isinstance(rows, list) or len(rows) != MISSION_PROPERTY_ROW_COUNT:
        raise ValueError("mission property row count differs")
    output = bytearray()
    for index, row in enumerate(rows):
        selector = row.get("selector_byte_00")
        middle = row.get("unclassified_01_to_07_hex")
        field_08 = row.get("field_u16_08")
        tail = row.get("unclassified_0a_to_0b_hex")
        if (row.get("index") != index or type(selector) is not int or
                not 0 <= selector <= 255 or not isinstance(middle, str) or
                len(middle) != 14 or type(field_08) is not int or
                not 0 <= field_08 <= 0xFFFF or not isinstance(tail, str) or
                len(tail) != 4):
            raise ValueError("mission property row differs")
        try:
            middle_bytes = bytes.fromhex(middle)
            tail_bytes = bytes.fromhex(tail)
        except ValueError as error:
            raise ValueError("mission property row field is not hex") from error
        if len(middle_bytes) != 7 or len(tail_bytes) != 2:
            raise ValueError("mission property row field length differs")
        output.append(selector)
        output.extend(middle_bytes)
        output.extend(struct.pack("<H", field_08))
        output.extend(tail_bytes)
    return bytes(output)
