"""Structured codec for the 116 retail job-definition records."""
import struct

TABLE_ROM_OFFSET = 0x521A14
ENTRY_SIZE = 52
ENTRY_COUNT = 116
TABLE_SIZE = ENTRY_SIZE * ENTRY_COUNT

U16_OFFSETS = {0: 0, 4: 7, 5: 9}
U8_OFFSETS = {
    3: 6,
    **{selector: selector + 4 for selector in range(8, 14)},
    **{selector: selector for selector in range(22, 26)},
    **{selector: selector + 10 for selector in range(30, 33)},
    33: 44,
    **{selector: selector + 9 for selector in range(36, 41)},
    **{selector: selector - 9 for selector in range(41, 48)},
}


def field_name(selector):
    if selector == 1:
        return "category"
    if selector == 2:
        return "inherit_job"
    if selector == 37:
        return "ability_first"
    if selector == 38:
        return "ability_last"
    return f"property{selector:02d}"


def decode_job_definitions(rom):
    """Decode fields observed by GetJobProperty without assigning unknown meanings."""
    span = rom[TABLE_ROM_OFFSET:TABLE_ROM_OFFSET + TABLE_SIZE]
    if len(span) != TABLE_SIZE:
        raise ValueError("Job-definition table exceeds input")
    records = []
    for index in range(ENTRY_COUNT):
        row = span[index * ENTRY_SIZE:(index + 1) * ENTRY_SIZE]
        record = {"index": index, "unknown02_hex": row[2:4].hex(),
                  "unknown18_low3": row[18] & 7,
                  "unknown21_high5": row[21] >> 3,
                  "unknown39": row[39], "unknown50_hex": row[50:52].hex()}
        for selector, offset in U16_OFFSETS.items():
            record[field_name(selector)] = struct.unpack_from("<H", row, offset)[0]
        record["category"] = row[4]
        record["inherit_job"] = row[5]
        for selector, offset in U8_OFFSETS.items():
            record[field_name(selector)] = row[offset]
        record["property06"] = row[11] & 15
        record["property07"] = row[11] >> 4
        packed_three_bit = struct.unpack_from("<I", row, 18)[0]
        for selector in range(14, 22):
            record[field_name(selector)] = (packed_three_bit >> (3 + 3 * (selector - 14))) & 7
        packed_twelve_bit = int.from_bytes(row[26:32], "little")
        for selector in range(26, 30):
            record[field_name(selector)] = (packed_twelve_bit >> (12 * (selector - 26))) & 0xfff
        record["property34"] = row[43] & 15
        record["property35"] = row[43] >> 4
        records.append(record)
    return {"rom_offset": TABLE_ROM_OFFSET, "entry_size": ENTRY_SIZE,
            "entry_count": ENTRY_COUNT, "records": records}


def encode_job_definitions(asset):
    """Rebuild the selected 52-byte rows from checked structured fields."""
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (TABLE_ROM_OFFSET, ENTRY_SIZE, ENTRY_COUNT):
        raise ValueError("Job-definition table metadata differs from retail")
    records = asset.get("records")
    if not isinstance(records, list) or len(records) != ENTRY_COUNT:
        raise ValueError("Job-definition record count differs from retail")
    result = bytearray()
    for index, record in enumerate(records):
        if record.get("index") != index:
            raise ValueError("Job-definition record order changed")
        row = bytearray(ENTRY_SIZE)
        for key, offset, length in (("unknown02_hex", 2, 2),
                                    ("unknown50_hex", 50, 2)):
            value = bytes.fromhex(record[key])
            if len(value) != length:
                raise ValueError(f"Invalid job-definition field {key}")
            row[offset:offset + length] = value

        def checked(key, bits):
            value = record.get(key)
            if type(value) is not int or not 0 <= value < 1 << bits:
                raise ValueError(f"Invalid job-definition field {key}")
            return value

        for selector, offset in U16_OFFSETS.items():
            struct.pack_into("<H", row, offset, checked(field_name(selector), 16))
        row[4] = checked("category", 8)
        row[5] = checked("inherit_job", 8)
        for selector, offset in U8_OFFSETS.items():
            row[offset] = checked(field_name(selector), 8)
        row[11] = checked("property06", 4) | checked("property07", 4) << 4
        packed_three_bit = checked("unknown18_low3", 3)
        for selector in range(14, 22):
            packed_three_bit |= checked(field_name(selector), 3) << (3 + 3 * (selector - 14))
        packed_three_bit |= checked("unknown21_high5", 5) << 27
        struct.pack_into("<I", row, 18, packed_three_bit)
        packed_twelve_bit = 0
        for selector in range(26, 30):
            packed_twelve_bit |= checked(field_name(selector), 12) << (12 * (selector - 26))
        row[26:32] = packed_twelve_bit.to_bytes(6, "little")
        row[43] = checked("property34", 4) | checked("property35", 4) << 4
        row[39] = checked("unknown39", 8)
        result.extend(row)
    return bytes(result)
