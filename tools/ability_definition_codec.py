"""Structured codec for the bounded US retail ability-definition table."""
import struct

TABLE_ROM_OFFSET = 0x55187C
ENTRY_SIZE = 28
ENTRY_COUNT = 347
TABLE_SIZE = ENTRY_SIZE * ENTRY_COUNT
NEXT_REGION_ROM_OFFSET = TABLE_ROM_OFFSET + TABLE_SIZE

BYTE_FIELDS = {
    "category": 2,
    "unknown03": 3,
    "mp_cost": 4,
    "unknown05": 5,
    "unknown06": 6,
    "unknown07": 7,
    "range": 8,
    "area": 9,
    "unknown0a": 10,
    "power": 11,
}


def decode_ability_definitions(rom):
    """Decode only records 0..346, before the separately referenced next region."""
    span = rom[TABLE_ROM_OFFSET:NEXT_REGION_ROM_OFFSET]
    if len(span) != TABLE_SIZE:
        raise ValueError("Ability-definition table exceeds input")
    records = []
    for index in range(ENTRY_COUNT):
        row = span[index * ENTRY_SIZE:(index + 1) * ENTRY_SIZE]
        record = {
            "index": index,
            "name_id": struct.unpack_from("<H", row, 0)[0],
            "effects": list(row[12:16]),
            "flags": struct.unpack_from("<I", row, 16)[0],
            "unknown14": struct.unpack_from("<H", row, 20)[0],
            "tail16_hex": row[22:28].hex(),
        }
        record.update({name: row[offset] for name, offset in BYTE_FIELDS.items()})
        records.append(record)
    return {"rom_offset": TABLE_ROM_OFFSET, "entry_size": ENTRY_SIZE,
            "entry_count": ENTRY_COUNT, "records": records}


def encode_ability_definitions(asset):
    """Encode editable fields while preserving unknown bytes explicitly."""
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (TABLE_ROM_OFFSET, ENTRY_SIZE, ENTRY_COUNT):
        raise ValueError("Ability-definition table metadata differs from retail")
    records = asset.get("records")
    if not isinstance(records, list) or len(records) != ENTRY_COUNT:
        raise ValueError("Ability-definition record count differs from retail")
    result = bytearray()
    for index, record in enumerate(records):
        if record.get("index") != index:
            raise ValueError("Ability-definition record order changed")

        def checked(key, bits):
            value = record.get(key)
            if type(value) is not int or not 0 <= value < 1 << bits:
                raise ValueError(f"Invalid ability-definition field {key}")
            return value

        row = bytearray(ENTRY_SIZE)
        struct.pack_into("<H", row, 0, checked("name_id", 16))
        for name, offset in BYTE_FIELDS.items():
            row[offset] = checked(name, 8)
        effects = record.get("effects")
        if not isinstance(effects, list) or len(effects) != 4 or \
                any(type(value) is not int or not 0 <= value < 256 for value in effects):
            raise ValueError("Ability-definition effects must contain four bytes")
        row[12:16] = bytes(effects)
        struct.pack_into("<I", row, 16, checked("flags", 32))
        struct.pack_into("<H", row, 20, checked("unknown14", 16))
        tail = bytes.fromhex(record["tail16_hex"])
        if len(tail) != 6:
            raise ValueError("Ability-definition tail must contain six bytes")
        row[22:28] = tail
        result.extend(row)
    return bytes(result)
