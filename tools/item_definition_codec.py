"""Structured codec for item IDs 0..375 in the US retail ROM."""
import struct

TABLE_ROM_OFFSET = 0x51D180
ENTRY_SIZE = 32
ENTRY_COUNT = 376
TABLE_SIZE = ENTRY_SIZE * ENTRY_COUNT
NEXT_REGION_ROM_OFFSET = TABLE_ROM_OFFSET + TABLE_SIZE


def decode_item_definitions(rom):
    """Decode the bounded item table, retaining fields without known meanings."""
    span = rom[TABLE_ROM_OFFSET:NEXT_REGION_ROM_OFFSET]
    if len(span) != TABLE_SIZE:
        raise ValueError("Item-definition table exceeds input")
    records = []
    for index in range(ENTRY_COUNT):
        row = span[index * ENTRY_SIZE:(index + 1) * ENTRY_SIZE]
        record = {
            "index": index,
            "name_id": struct.unpack_from("<H", row, 0)[0],
            "unknown02": struct.unpack_from("<H", row, 2)[0],
            "unknown04": struct.unpack_from("<H", row, 4)[0],
            "unknown06": struct.unpack_from("<H", row, 6)[0],
            "category": row[8],
            "unknown0e": struct.unpack_from("<H", row, 14)[0],
            "modifiers": list(struct.unpack_from("<8b", row, 16)),
            "unknown18_hex": row[24:29].hex(),
            "ability_set": row[29],
            "unknown1e_hex": row[30:32].hex(),
        }
        record.update({f"property{selector:02d}": row[selector + 5]
                       for selector in range(4, 9)})
        records.append(record)
    return {"rom_offset": TABLE_ROM_OFFSET, "entry_size": ENTRY_SIZE,
            "entry_count": ENTRY_COUNT, "records": records}


def encode_item_definitions(asset):
    """Rebuild exactly 376 checked 32-byte item records."""
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (TABLE_ROM_OFFSET, ENTRY_SIZE, ENTRY_COUNT):
        raise ValueError("Item-definition table metadata differs from retail")
    records = asset.get("records")
    if not isinstance(records, list) or len(records) != ENTRY_COUNT:
        raise ValueError("Item-definition record count differs from retail")
    result = bytearray()
    for index, record in enumerate(records):
        if record.get("index") != index:
            raise ValueError("Item-definition record order changed")

        def checked(key, bits):
            value = record.get(key)
            if type(value) is not int or not 0 <= value < 1 << bits:
                raise ValueError(f"Invalid item-definition field {key}")
            return value

        row = bytearray(ENTRY_SIZE)
        for key, offset in (("name_id", 0), ("unknown02", 2),
                            ("unknown04", 4), ("unknown06", 6),
                            ("unknown0e", 14)):
            struct.pack_into("<H", row, offset, checked(key, 16))
        row[8] = checked("category", 8)
        for selector in range(4, 9):
            row[selector + 5] = checked(f"property{selector:02d}", 8)
        modifiers = record.get("modifiers")
        if not isinstance(modifiers, list) or len(modifiers) != 8 or \
                any(type(value) is not int or not -128 <= value <= 127
                    for value in modifiers):
            raise ValueError("Item modifiers must contain eight signed bytes")
        struct.pack_into("<8b", row, 16, *modifiers)
        for key, offset, length in (("unknown18_hex", 24, 5),
                                    ("unknown1e_hex", 30, 2)):
            value = bytes.fromhex(record[key])
            if len(value) != length:
                raise ValueError(f"Invalid item-definition field {key}")
            row[offset:offset + length] = value
        row[29] = checked("ability_set", 8)
        result.extend(row)
    return bytes(result)
