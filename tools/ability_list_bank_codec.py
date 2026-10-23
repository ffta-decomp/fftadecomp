"""Lossless, fixed-address ability-list pointer and eight-byte row bank."""

import struct


RETAIL_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
START = 0x51BA84
END = 0x51D0F4
POINTER_COUNT = 24
ROW_BYTES = 8
ROW_COUNTS = (16, 142, 77, 95, 85, 88, 8, 22, 9, 13, 11, 10,
              10, 9, 9, 9, 9, 10, 9, 11, 11, 17, 17, 9)


def list_offsets():
    offset = START + POINTER_COUNT * 4
    offsets = []
    for count in ROW_COUNTS:
        offsets.append(offset)
        offset += count * ROW_BYTES
    if offset != END:
        raise ValueError("Ability-list boundaries do not cover the bank")
    return offsets


def decode_ability_list_bank(rom):
    if len(rom) < END:
        raise ValueError("Ability-list bank exceeds input")
    offsets = list_offsets()
    lists = []
    for list_index, (offset, count) in enumerate(zip(offsets, ROW_COUNTS)):
        pointer = struct.unpack_from("<I", rom, START + list_index * 4)[0]
        if pointer != ROM_BASE + offset:
            raise ValueError(f"Ability-list pointer {list_index} differs")
        rows = []
        for index in range(count):
            fields = struct.unpack_from("<HHBBBB", rom, offset + index * ROW_BYTES)
            rows.append(dict(zip(("field_u16_00", "field_u16_02",
                                  "value_at_04", "byte_at_05",
                                  "category_at_06", "requirement_at_07"),
                                 fields), index=index))
        lists.append({"list_index": list_index, "rom_offset": offset,
                      "row_count": count, "rows": rows})
    return {"reference_sha256": RETAIL_SHA256, "rom_offset": START,
            "end_exclusive": END, "pointer_count": POINTER_COUNT,
            "row_bytes": ROW_BYTES, "row_count": sum(ROW_COUNTS),
            "lists": lists}


def encode_ability_list_bank(asset):
    if (asset.get("reference_sha256") != RETAIL_SHA256 or
            asset.get("rom_offset") != START or
            asset.get("end_exclusive") != END or
            asset.get("pointer_count") != POINTER_COUNT or
            asset.get("row_bytes") != ROW_BYTES or
            asset.get("row_count") != sum(ROW_COUNTS)):
        raise ValueError("Ability-list bank revision or boundary differs")
    lists = asset.get("lists")
    if not isinstance(lists, list) or len(lists) != POINTER_COUNT:
        raise ValueError("Ability-list count differs")
    out = bytearray()
    offsets = list_offsets()
    for offset in offsets:
        out.extend(struct.pack("<I", ROM_BASE + offset))
    field_names = ("field_u16_00", "field_u16_02", "value_at_04",
                   "byte_at_05", "category_at_06", "requirement_at_07")
    for list_index, (entry, offset, count) in enumerate(
            zip(lists, offsets, ROW_COUNTS)):
        rows = entry.get("rows")
        if (entry.get("list_index") != list_index or
                entry.get("rom_offset") != offset or
                entry.get("row_count") != count or
                not isinstance(rows, list) or len(rows) != count):
            raise ValueError(f"Ability-list {list_index} layout differs")
        for index, row in enumerate(rows):
            values = [row.get(name) for name in field_names]
            if (row.get("index") != index or
                    any(type(value) is not int for value in values) or
                    any(not 0 <= value <= limit for value, limit in
                        zip(values, (0xFFFF, 0xFFFF, 255, 255, 255, 255)))):
                raise ValueError(f"Ability-list {list_index} row {index} differs")
            out.extend(struct.pack("<HHBBBB", *values))
    if len(out) != END - START:
        raise ValueError("Ability-list encoded length differs")
    return bytes(out)
