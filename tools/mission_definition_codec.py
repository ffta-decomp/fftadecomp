"""Field-preserving codec for the 512 US retail mission definitions.

Field names follow the observed GetMissionProperty selector when its meaning is
not established. Bit ranges are stored as independent integers, not opaque rows.
"""

import struct

TABLE_ROM_OFFSET = 0x55AE4C
ENTRY_SIZE = 70
ENTRY_COUNT = 512
TABLE_SIZE = ENTRY_SIZE * ENTRY_COUNT

HEADER_BITS = (("behavior_code", 3), ("icon_group", 3),
               ("property03", 6), ("property04", 3),
               ("property07", 3), ("unknown_header", 6))
MIDDLE_BITS = (("property14", 3), ("property15", 8),
               ("property16", 8), ("property17", 3),
               ("property18", 8), ("unknown_middle", 2))
REWARD_BITS = ((f"property{selector}", width) for selector, width in
               ((46, 4), (47, 7), (48, 6), (49, 4),
                (50, 7), (51, 6), (52, 6)))
REWARD_BITS = tuple(REWARD_BITS)
HALFWORDS = (("record_id", 0), ("property08", 5),
             ("property10", 8), ("property12", 11),
             ("property25", 34), ("property26", 36),
             ("property27", 38), ("property28", 40),
             ("flags", 65), ("property59", 67))
BYTES = (("property09", 7), ("property11", 10),
         ("property13", 13), ("gil_reward_units", 51),
         ("ap_reward_units", 52), ("item_reward", 53),
         ("required_item_a", 54), ("required_item_b", 55),
         ("excluded_item", 61), ("property54_units", 62),
         ("property57", 63), ("property58", 64),
         ("property60", 69))


def unpack_bits(row, offset, length, fields):
    packed = int.from_bytes(row[offset:offset + length], "little")
    result = {}
    shift = 0
    for name, width in fields:
        result[name] = (packed >> shift) & ((1 << width) - 1)
        shift += width
    if shift != length * 8:
        raise ValueError("Bit fields do not cover their byte span")
    return result


def pack_bits(record, fields):
    packed = 0
    shift = 0
    for name, width in fields:
        packed |= checked(record, name, width) << shift
        shift += width
    return packed.to_bytes(shift // 8, "little")


def checked(record, name, width):
    value = record.get(name)
    if type(value) is not int or not 0 <= value < 1 << width:
        raise ValueError(f"Invalid mission-definition field {name}")
    return value


def decode_mission_definitions(rom):
    """Decode every byte of the bounded mission table into typed fields."""
    span = rom[TABLE_ROM_OFFSET:TABLE_ROM_OFFSET + TABLE_SIZE]
    if len(span) != TABLE_SIZE:
        raise ValueError("Mission-definition table exceeds input")
    records = []
    for index in range(ENTRY_COUNT):
        row = span[index * ENTRY_SIZE:(index + 1) * ENTRY_SIZE]
        record = {"index": index}
        for name, offset in HALFWORDS:
            record[name] = struct.unpack_from("<H", row, offset)[0]
        for name, offset in BYTES:
            record[name] = row[offset]
        record.update(unpack_bits(row, 2, 3, HEADER_BITS))
        record.update(unpack_bits(row, 14, 4, MIDDLE_BITS))
        record.update(unpack_bits(row, 56, 5, REWARD_BITS))
        record["auxiliary_blocks"] = list(struct.unpack_from("<4I", row, 18))
        record["clan_rewards"] = list(row[42:51])
        if record["record_id"] != index:
            raise ValueError(f"Mission-definition ID differs at index {index}")
        records.append(record)
    return {"rom_offset": TABLE_ROM_OFFSET, "entry_size": ENTRY_SIZE,
            "entry_count": ENTRY_COUNT, "records": records}


def encode_mission_definitions(asset):
    """Rebuild exactly 512 checked 70-byte records in their original order."""
    if (asset.get("rom_offset"), asset.get("entry_size"),
            asset.get("entry_count")) != (TABLE_ROM_OFFSET, ENTRY_SIZE, ENTRY_COUNT):
        raise ValueError("Mission-definition metadata differs from retail")
    records = asset.get("records")
    if not isinstance(records, list) or len(records) != ENTRY_COUNT:
        raise ValueError("Mission-definition record count differs from retail")
    result = bytearray()
    for index, record in enumerate(records):
        if record.get("index") != index or record.get("record_id") != index:
            raise ValueError(f"Mission-definition ID/order differs at {index}")
        row = bytearray(ENTRY_SIZE)
        for name, offset in HALFWORDS:
            struct.pack_into("<H", row, offset, checked(record, name, 16))
        for name, offset in BYTES:
            row[offset] = checked(record, name, 8)
        row[2:5] = pack_bits(record, HEADER_BITS)
        row[14:18] = pack_bits(record, MIDDLE_BITS)
        row[56:61] = pack_bits(record, REWARD_BITS)
        blocks = record.get("auxiliary_blocks")
        if not isinstance(blocks, list) or len(blocks) != 4:
            raise ValueError("Mission auxiliary blocks must contain four words")
        for block_index, value in enumerate(blocks):
            if type(value) is not int or not 0 <= value < 1 << 32:
                raise ValueError("Invalid mission auxiliary block")
            struct.pack_into("<I", row, 18 + block_index * 4, value)
        rewards = record.get("clan_rewards")
        if not isinstance(rewards, list) or len(rewards) != 9 or any(
                type(value) is not int or not 0 <= value < 256 for value in rewards):
            raise ValueError("Mission clan rewards must contain nine bytes")
        row[42:51] = bytes(rewards)
        result.extend(row)
    return bytes(result)
