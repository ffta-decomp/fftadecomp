"""Structured codec for the populated 14-byte indexed unit-record span."""
import struct

TABLE_POINTER_ROM_OFFSET = 0x5273d8
FIRST_INDEX = 2
ENTRY_COUNT = 93
ENTRY_SIZE = 14
TABLE_ROM_OFFSET = TABLE_POINTER_ROM_OFFSET + FIRST_INDEX * ENTRY_SIZE
TABLE_SIZE = ENTRY_COUNT * ENTRY_SIZE
ZERO_TAIL_OFFSET = TABLE_ROM_OFFSET + TABLE_SIZE


def decode_unit_records(rom):
    """Decode only populated indices 2..94; index 95 is an unclassified zero tail."""
    if rom[ZERO_TAIL_OFFSET:ZERO_TAIL_OFFSET + ENTRY_SIZE] != bytes(ENTRY_SIZE):
        raise ValueError("Expected zero boundary after indexed unit records")
    records = []
    for index in range(FIRST_INDEX, FIRST_INDEX + ENTRY_COUNT):
        offset = TABLE_POINTER_ROM_OFFSET + index * ENTRY_SIZE
        raw = rom[offset:offset + ENTRY_SIZE]
        if len(raw) != ENTRY_SIZE:
            raise ValueError("Indexed unit record exceeds input")
        records.append({
            "index": index,
            "prefix_hex": raw[:4].hex(),
            "property04": struct.unpack_from("<H", raw, 4)[0],
            "property05": struct.unpack_from("<H", raw, 6)[0],
            "slot_a": raw[8] & 15,
            "source_a": (raw[8] >> 4) | ((raw[9] & 15) << 4),
            "slot_b": raw[9] >> 4,
            "source_b": raw[10],
            "property09": raw[11],
            "property10": raw[12],
            "property11": raw[13],
        })
    return {"rom_offset": TABLE_ROM_OFFSET,
            "table_pointer_rom_offset": TABLE_POINTER_ROM_OFFSET,
            "first_index": FIRST_INDEX, "entry_count": ENTRY_COUNT,
            "entry_size": ENTRY_SIZE, "records": records}


def encode_unit_records(asset):
    """Rebuild records from named fields, rejecting layout and range changes."""
    expected = (TABLE_ROM_OFFSET, TABLE_POINTER_ROM_OFFSET,
                FIRST_INDEX, ENTRY_COUNT, ENTRY_SIZE)
    actual = tuple(asset.get(key) for key in (
        "rom_offset", "table_pointer_rom_offset", "first_index",
        "entry_count", "entry_size"))
    if actual != expected or not isinstance(asset.get("records"), list) or \
            len(asset["records"]) != ENTRY_COUNT:
        raise ValueError("Indexed unit-record span metadata does not match retail")
    result = bytearray()
    for expected_index, record in enumerate(asset["records"], FIRST_INDEX):
        if record.get("index") != expected_index:
            raise ValueError("Indexed unit-record order changed")
        prefix = bytes.fromhex(record["prefix_hex"])
        if len(prefix) != 4:
            raise ValueError("Indexed unit-record prefix must have four bytes")
        widths = {"property04": 16, "property05": 16,
                  "slot_a": 4, "source_a": 8, "slot_b": 4, "source_b": 8,
                  "property09": 8, "property10": 8, "property11": 8}
        for key, bits in widths.items():
            value = record.get(key)
            if type(value) is not int or not 0 <= value < (1 << bits):
                raise ValueError(f"Invalid indexed unit-record field {key}")
        result += prefix
        result += struct.pack("<HH", record["property04"], record["property05"])
        result += bytes((record["slot_a"] | ((record["source_a"] & 15) << 4),
                         (record["source_a"] >> 4) | (record["slot_b"] << 4),
                         record["source_b"], record["property09"],
                         record["property10"], record["property11"]))
    return bytes(result)
