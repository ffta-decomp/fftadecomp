"""Structured codec for the 225 item-granted ability sets."""

TABLE_ROM_OFFSET = 0x520080
ENTRY_SIZE = 20
ENTRY_COUNT = 225
MAX_PAIRS = 9
TABLE_SIZE = ENTRY_SIZE * ENTRY_COUNT
NEXT_REGION_ROM_OFFSET = TABLE_ROM_OFFSET + TABLE_SIZE


def decode_item_ability_sets(rom):
    """Decode active job/ability pairs and verify unused slots are zero."""
    span = rom[TABLE_ROM_OFFSET:NEXT_REGION_ROM_OFFSET]
    if len(span) != TABLE_SIZE:
        raise ValueError("Item-ability-set table exceeds input")
    records = []
    for index in range(ENTRY_COUNT):
        row = span[index * ENTRY_SIZE:(index + 1) * ENTRY_SIZE]
        count = row[0]
        if count > MAX_PAIRS or any(row[2 + count * 2:]):
            raise ValueError(f"Item-ability-set {index} has an invalid tail")
        records.append({
            "index": index,
            "count": count,
            "unknown01": row[1],
            "pairs": [{"job_id": row[2 + pair * 2],
                       "ability_id": row[3 + pair * 2]}
                      for pair in range(count)],
        })
    return {"rom_offset": TABLE_ROM_OFFSET, "entry_size": ENTRY_SIZE,
            "entry_count": ENTRY_COUNT, "records": records}


def encode_item_ability_sets(asset):
    """Rebuild each fixed-size row from its checked active pairs."""
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (TABLE_ROM_OFFSET, ENTRY_SIZE, ENTRY_COUNT):
        raise ValueError("Item-ability-set metadata differs from retail")
    records = asset.get("records")
    if not isinstance(records, list) or len(records) != ENTRY_COUNT:
        raise ValueError("Item-ability-set record count differs from retail")
    result = bytearray()
    for index, record in enumerate(records):
        if record.get("index") != index:
            raise ValueError("Item-ability-set record order changed")
        pairs = record.get("pairs")
        count = record.get("count")
        unknown = record.get("unknown01")
        if (not isinstance(pairs, list) or type(count) is not int or
                len(pairs) != count or not 0 <= count <= MAX_PAIRS or
                type(unknown) is not int or not 0 <= unknown <= 255):
            raise ValueError(f"Invalid item-ability-set header at {index}")
        row = bytearray(ENTRY_SIZE)
        row[0] = count
        row[1] = unknown
        for pair_index, pair in enumerate(pairs):
            for key, offset in (("job_id", 2), ("ability_id", 3)):
                value = pair.get(key)
                if type(value) is not int or not 0 <= value <= 255:
                    raise ValueError(f"Invalid item-ability-set pair at {index}")
                row[pair_index * 2 + offset] = value
        result.extend(row)
    return bytes(result)
