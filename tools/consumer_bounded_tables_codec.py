"""Fixed-span tables bounded by observed retail consumers."""

import hashlib
import struct
from typing import NamedTuple


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"


class TableLayout(NamedTuple):
    start: int
    count: int
    row_format: str
    fields: tuple
    first_index: int = 0
    terminator: int = -1

    @property
    def stride(self):
        return struct.calcsize(self.row_format)

    @property
    def end(self):
        return self.start + self.count * self.stride + (2 if self.terminator >= 0 else 0)


REWARD_FIELDS = (("weight_at_00", "byte_at_01", "dispatch_at_02") +
                 tuple(f"byte_at_{index:02x}" for index in range(3, 12)))
REWARD_GROUPS = (
    (3, 15), (15, 23), (23, 32), (32, 41), (41, 50), (50, 64),
    (64, 80), (80, 94), (94, 111), (111, 138),
    (138, 140), (140, 142), (142, 144), (144, 146),
    (146, 148), (148, 150), (150, 151),
    (152, 153), (154, 155), (156, 157), (158, 159),
)


TABLES = {
    "threshold_rows64": TableLayout(
        0x528256, 64, "<12B",
        tuple(f"byte_at_{index:02x}" for index in range(4)) +
        tuple(f"threshold_{index}" for index in range(8))),
    "condition_rows_1_to_64": TableLayout(
        0x528566, 64, "<BB7H",
        ("byte_at_00", "condition_at_01") +
        tuple(f"field_u16_{index:02x}" for index in range(2, 16, 2)), 1),
    "item_index_rows31": TableLayout(
        0x528968, 31, "<BBH",
        ("byte_at_00", "text_index_at_01", "cost_units_at_02")),
    "bucket_random_halfwords": TableLayout(
        0x5295D4, 10, "<20H", tuple(f"choice_{index:02d}" for index in range(20))),
    "terminated_flag_indices": TableLayout(
        0x529EE4, 300, "<H", ("flag_index",), 0, 0xFFFF),
    "reward_rows_3_to_150": TableLayout(
        0x529788, 148, "<12B", REWARD_FIELDS, 3),
    "reward_row_152": TableLayout(
        0x529E84, 1, "<12B", REWARD_FIELDS, 152),
    "reward_row_154": TableLayout(
        0x529E9C, 1, "<12B", REWARD_FIELDS, 154),
    "reward_row_156": TableLayout(
        0x529EB4, 1, "<12B", REWARD_FIELDS, 156),
    "reward_row_158": TableLayout(
        0x529ECC, 1, "<12B", REWARD_FIELDS, 158),
    # These fixed prefixes are bounded by the observed ability-effect
    # consumers; they do not establish a runtime maximum for every producer.
    "ability_effect_details209": TableLayout(
        0x553E70, 209, "<4B",
        ("callback_index_00", "execution_index_01",
         "callback_index_02", "callback_index_03")),
    "effect_callbacks_00_prefix29": TableLayout(
        0x3A8604, 29, "<I", ("handler_thumb",)),
    "effect_callbacks_02_prefix32": TableLayout(
        0x3A8678, 32, "<I", ("handler_thumb",)),
    "effect_callbacks_03_prefix45": TableLayout(
        0x3A86F8, 45, "<I", ("handler_thumb",)),
    "effect_execution_descriptors93": TableLayout(
        0x3A87B0, 93, "<III",
        ("handler_thumb", "metadata_04_u32", "metadata_08_u32")),
    "initial_audio_copy_words36": TableLayout(
        0x36D098, 36, "<I", ("copied_u32",)),
    "crc32_lookup_256": TableLayout(
        0x393318, 256, "<I", ("lookup_remainder",)),
    "condition_rows_1_to_127": TableLayout(
        0x5573F4, 127, "<BBHBHB",
        ("entry_id", "selector_filter", "first_condition_code",
         "first_compare_value", "second_condition_code",
         "second_compare_value"), 1),
}

LIBRARY42_TABLES = {
    'library42_149568': TableLayout(0x149568, 320, '<h', ('signed_lookup_value',)),
    'library42_1497e8': TableLayout(0x1497e8, 6, '<I', ('callback_thumb',)),
    'library42_149800': TableLayout(0x149800, 3, '<H', ('halfword_value',)),
    'library42_149806': TableLayout(0x149806, 3, '<H', ('halfword_value',)),
    'library42_14980c': TableLayout(0x14980c, 3, '<I', ('callback_thumb',)),
    'library42_149818': TableLayout(0x149818, 3, '<H', ('halfword_value',)),
    'library42_14bb24': TableLayout(0x14bb24, 3, '<IIBBH', ('state_pointer', 'track_buffer_pointer', 'track_limit_u8', 'unclassified_09', 'initial_field_0a_u16')),
    'library42_1498f4': TableLayout(0x1498f4, 8, '<I', ('loaded_u32',)),
    'library42_149924': TableLayout(0x149924, 4, '<I', ('loaded_u32',)),
    'library42_1499c4': TableLayout(0x1499c4, 6, '<I', ('loaded_u32',)),
    'library42_149a88': TableLayout(0x149a88, 6, '<I', ('loaded_u32',)),
    'library42_149aa4': TableLayout(0x149aa4, 8, '<I', ('loaded_u32',)),
    'library42_149ad4': TableLayout(0x149ad4, 36, '<I', ('loaded_u32',)),
    'library42_149c14': TableLayout(0x149c14, 28, '<I', ('loaded_u32',)),
    'library42_149c88': TableLayout(0x149c88, 6, '<I', ('loaded_u32',)),
    'library42_149ca4': TableLayout(0x149ca4, 8, '<I', ('loaded_u32',)),
    'library42_149ce8': TableLayout(0x149ce8, 8, '<I', ('loaded_u32',)),
    'library42_149d94': TableLayout(0x149d94, 12, '<I', ('loaded_u32',)),
    'library42_149de0': TableLayout(0x149de0, 4, '<I', ('loaded_u32',)),
    'library42_149e44': TableLayout(0x149e44, 4, '<I', ('loaded_u32',)),
    'library42_149ff8': TableLayout(0x149ff8, 2, '<I', ('loaded_u32',)),
    'library42_14a000': TableLayout(0x14a000, 1, '<H', ('loaded_u16',)),
    'library42_149868': TableLayout(0x149868, 3, '<B', ('copied_u8',)),
    'library42_149914': TableLayout(0x149914, 8, '<B', ('copied_u8',)),
    'library42_14991c': TableLayout(0x14991c, 8, '<B', ('copied_u8',)),
    'library42_149994': TableLayout(0x149994, 2, '<B', ('copied_u8',)),
    'library42_149998': TableLayout(0x149998, 10, '<B', ('copied_u8',)),
    'library42_1499a2': TableLayout(0x1499a2, 10, '<B', ('copied_u8',)),
    'library42_1499ac': TableLayout(0x1499ac, 10, '<B', ('copied_u8',)),
    'library42_1499b6': TableLayout(0x1499b6, 8, '<B', ('copied_u8',)),
    'library42_1499c0': TableLayout(0x1499c0, 4, '<B', ('copied_u8',)),
    'library42_149aa0': TableLayout(0x149aa0, 4, '<B', ('copied_u8',)),
    'library42_149ac4': TableLayout(0x149ac4, 8, '<B', ('copied_u8',)),
    'library42_149acc': TableLayout(0x149acc, 8, '<B', ('copied_u8',)),
    'library42_149b64': TableLayout(0x149b64, 4, '<B', ('copied_u8',)),
    'library42_149b68': TableLayout(0x149b68, 8, '<B', ('copied_u8',)),
    'library42_149b70': TableLayout(0x149b70, 4, '<B', ('copied_u8',)),
    'library42_149b74': TableLayout(0x149b74, 3, '<B', ('copied_u8',)),
    'library42_149b77': TableLayout(0x149b77, 4, '<B', ('copied_u8',)),
    'library42_149b7b': TableLayout(0x149b7b, 4, '<B', ('copied_u8',)),
    'library42_149b80': TableLayout(0x149b80, 8, '<B', ('copied_u8',)),
    'library42_149c0c': TableLayout(0x149c0c, 4, '<B', ('copied_u8',)),
    'library42_149c10': TableLayout(0x149c10, 4, '<B', ('copied_u8',)),
    'library42_149ca0': TableLayout(0x149ca0, 3, '<B', ('copied_u8',)),
    'library42_149cc4': TableLayout(0x149cc4, 4, '<B', ('copied_u8',)),
    'library42_149cc8': TableLayout(0x149cc8, 24, '<B', ('copied_u8',)),
    'library42_149ce0': TableLayout(0x149ce0, 8, '<B', ('copied_u8',)),
    'library42_149d0c': TableLayout(0x149d0c, 4, '<B', ('copied_u8',)),
    'library42_149d14': TableLayout(0x149d14, 4, '<B', ('copied_u8',)),
    'library42_149d18': TableLayout(0x149d18, 4, '<B', ('copied_u8',)),
    'library42_149d1c': TableLayout(0x149d1c, 4, '<B', ('copied_u8',)),
    'library42_149d20': TableLayout(0x149d20, 4, '<B', ('copied_u8',)),
    'library42_149d24': TableLayout(0x149d24, 4, '<B', ('copied_u8',)),
    'library42_149d28': TableLayout(0x149d28, 4, '<B', ('copied_u8',)),
    'library42_149d2c': TableLayout(0x149d2c, 4, '<B', ('copied_u8',)),
    'library42_149d30': TableLayout(0x149d30, 4, '<B', ('copied_u8',)),
    'library42_149d34': TableLayout(0x149d34, 4, '<B', ('copied_u8',)),
    'library42_149d38': TableLayout(0x149d38, 4, '<B', ('copied_u8',)),
    'library42_149d6c': TableLayout(0x149d6c, 4, '<B', ('copied_u8',)),
    'library42_149dc4': TableLayout(0x149dc4, 8, '<B', ('copied_u8',)),
    'library42_149dcc': TableLayout(0x149dcc, 3, '<B', ('copied_u8',)),
    'library42_149df0': TableLayout(0x149df0, 3, '<B', ('copied_u8',)),
    'library42_149df3': TableLayout(0x149df3, 3, '<B', ('copied_u8',)),
    'library42_149df6': TableLayout(0x149df6, 3, '<B', ('copied_u8',)),
    'library42_149df9': TableLayout(0x149df9, 3, '<B', ('copied_u8',)),
    'library42_149e5c': TableLayout(0x149e5c, 64, '<B', ('copied_u8',)),
    'library42_149e9c': TableLayout(0x149e9c, 64, '<B', ('copied_u8',)),
    'library42_149f14': TableLayout(0x149f14, 3, '<B', ('copied_u8',)),
    'library42_149f17': TableLayout(0x149f17, 3, '<B', ('copied_u8',)),
    'library42_149f1a': TableLayout(0x149f1a, 3, '<B', ('copied_u8',)),
    'library42_149f1d': TableLayout(0x149f1d, 3, '<B', ('copied_u8',)),
    'library42_149f24': TableLayout(0x149f24, 3, '<B', ('copied_u8',)),
    'library42_149f27': TableLayout(0x149f27, 3, '<B', ('copied_u8',)),
    'library42_149f2a': TableLayout(0x149f2a, 3, '<B', ('copied_u8',)),
    'library42_149f2d': TableLayout(0x149f2d, 3, '<B', ('copied_u8',)),
    'library42_149f34': TableLayout(0x149f34, 10, '<B', ('copied_u8',)),
    'library42_149f40': TableLayout(0x149f40, 10, '<B', ('copied_u8',)),
    'library42_149f4c': TableLayout(0x149f4c, 10, '<B', ('copied_u8',)),
    'library42_149f56': TableLayout(0x149f56, 10, '<B', ('copied_u8',)),
    'library42_149f60': TableLayout(0x149f60, 6, '<B', ('copied_u8',)),
    'library42_149f66': TableLayout(0x149f66, 6, '<B', ('copied_u8',)),
    'library42_149f6c': TableLayout(0x149f6c, 4, '<B', ('copied_u8',)),
    'library42_149f70': TableLayout(0x149f70, 4, '<B', ('copied_u8',)),
    'library42_1499dc': TableLayout(0x1499dc, 6, '<B', ('terminated_string_byte',)),
    'library42_1499e4': TableLayout(0x1499e4, 5, '<B', ('terminated_string_byte',)),
    'library42_1499ec': TableLayout(0x1499ec, 5, '<B', ('terminated_string_byte',)),
    'library42_1499f4': TableLayout(0x1499f4, 5, '<B', ('terminated_string_byte',)),
    'library42_1499fc': TableLayout(0x1499fc, 5, '<B', ('terminated_string_byte',)),
    'library42_149a04': TableLayout(0x149a04, 5, '<B', ('terminated_string_byte',)),
    'library42_149a0c': TableLayout(0x149a0c, 5, '<B', ('terminated_string_byte',)),
    'library42_149a14': TableLayout(0x149a14, 5, '<B', ('terminated_string_byte',)),
    'library42_149a1c': TableLayout(0x149a1c, 9, '<B', ('terminated_string_byte',)),
    'library42_149a28': TableLayout(0x149a28, 8, '<B', ('terminated_string_byte',)),
    'library42_149a30': TableLayout(0x149a30, 8, '<B', ('terminated_string_byte',)),
    'library42_149a38': TableLayout(0x149a38, 8, '<B', ('terminated_string_byte',)),
    'library42_149a40': TableLayout(0x149a40, 6, '<B', ('terminated_string_byte',)),
    'library42_149a48': TableLayout(0x149a48, 8, '<B', ('terminated_string_byte',)),
    'library42_149a50': TableLayout(0x149a50, 8, '<B', ('terminated_string_byte',)),
    'library42_149a58': TableLayout(0x149a58, 7, '<B', ('terminated_string_byte',)),
    'library42_149a60': TableLayout(0x149a60, 6, '<B', ('terminated_string_byte',)),
    'library42_149a68': TableLayout(0x149a68, 8, '<B', ('terminated_string_byte',)),
    'library42_149a70': TableLayout(0x149a70, 10, '<B', ('terminated_string_byte',)),
    'library42_149a7c': TableLayout(0x149a7c, 10, '<B', ('terminated_string_byte',)),
}

from remaining_data41_layouts import (
    REMAINING_DATA41_EXTRA_TABLES as COUNTED_DATA_EXTRA_TABLES,
    REMAINING_DATA41_FRAMES_TABLES as FRAME_TABLES,
)

BASE_TABLES = dict(TABLES)
from counted_data_v2_layouts import TABLES as COUNTED_DATA_V2_TABLES
CORE_TABLES_63_LAYOUTS_JSON_SHA256 = (
    "fd7c64581e186c6eb686cdaa1ee403c538558cb362a5a2f2bb4727af4478b51c")
CORE_TABLES_63_TABLES = {
    "bounded_class_records16": TableLayout(
        0x528F34, 86, "<BBH12B",
        ("flags_00", "byte_at_01", "flags_02_u16", "byte_at_04",
         "byte_at_05", "byte_at_06", "byte_at_07", "byte_at_08",
         "byte_at_09", "byte_at_0a", "byte_at_0b", "byte_at_0c",
         "byte_at_0d", "byte_at_0e", "byte_at_0f")),
    "bounded_sentinel_reward_halfwords": TableLayout(
        0x529494, 140, "<H", ("reward_value_u16",)),
    "bounded_default_reward_halfwords": TableLayout(
        0x5295AC, 20, "<H", ("reward_value_u16",)),
}

if set(BASE_TABLES) & set(COUNTED_DATA_V2_TABLES):
    raise RuntimeError("counted-data-v2 table IDs overlap the base table set")

if set(BASE_TABLES) & set(LIBRARY42_TABLES):
    raise RuntimeError("library42 table IDs overlap the base table set")
if set(COUNTED_DATA_V2_TABLES) & set(LIBRARY42_TABLES):
    raise RuntimeError("library42 table IDs overlap counted-data-v2")
if (set(COUNTED_DATA_EXTRA_TABLES) &
        (set(BASE_TABLES) | set(COUNTED_DATA_V2_TABLES) |
         set(LIBRARY42_TABLES))):
    raise RuntimeError("data41 extra table IDs overlap an existing table set")
if (set(FRAME_TABLES) &
        (set(BASE_TABLES) | set(COUNTED_DATA_V2_TABLES) |
         set(LIBRARY42_TABLES) | set(COUNTED_DATA_EXTRA_TABLES) |
         set(CORE_TABLES_63_TABLES))):
    raise RuntimeError("data41 frame table IDs overlap an existing table set")
if (set(CORE_TABLES_63_TABLES) &
        (set(BASE_TABLES) | set(COUNTED_DATA_V2_TABLES) |
         set(LIBRARY42_TABLES) | set(COUNTED_DATA_EXTRA_TABLES) |
         set(FRAME_TABLES))):
    raise RuntimeError("core-tables-63 IDs overlap an existing table set")

TABLE_SETS = {
    "base-v1": BASE_TABLES,
    "counted-data-v2": COUNTED_DATA_V2_TABLES,
    "library42-wave8": LIBRARY42_TABLES,
    "data41-extra-v1": COUNTED_DATA_EXTRA_TABLES,
    "data41-frame-tables-v1": FRAME_TABLES,
    "core-tables-63": CORE_TABLES_63_TABLES,
}
TABLES.update(COUNTED_DATA_V2_TABLES)
TABLES.update(LIBRARY42_TABLES)
TABLES.update(COUNTED_DATA_EXTRA_TABLES)
TABLES.update(FRAME_TABLES)
TABLES.update(CORE_TABLES_63_TABLES)



# Consumer-bounded additions accepted in the 2026-10-19 recovery batch.
LIBRARY42_WAVE13_LAYOUTS_JSON_SHA256 = "730277545998e7807587c1e933c4e276a3b12216ac9ef36a52351a4f98209526"
LIBRARY42_WAVE13_TABLES = {
    'library42_14942c': TableLayout(0x14942C, 15, '<I', ('initial_word',), 0, -1),
    'library42_149510': TableLayout(0x149510, 16, '<hh', ('width_s16', 'height_s16'), 0, -1),
    'library42_149828': TableLayout(0x149828, 64, '<B', ('copied_template_u8',), 0, -1),
    'library42_14ba84': TableLayout(0x14BA84, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14ba94': TableLayout(0x14BA94, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14baa4': TableLayout(0x14BAA4, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14bab4': TableLayout(0x14BAB4, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14bac4': TableLayout(0x14BAC4, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14bad4': TableLayout(0x14BAD4, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14bae4': TableLayout(0x14BAE4, 4, '<I', ('wave_ram_word',), 0, -1),
    'library42_14baf4': TableLayout(0x14BAF4, 4, '<I', ('wave_ram_word',), 0, -1),
}

MISSION_TABLE_DOMAIN_64_LAYOUTS_JSON_SHA256 = "f386f2b74909e26764909e16e3f0fce9cd41bc4cad9436049f384d4d6def483c"
MISSION_PARAMETER27_FIELDS = tuple(f"byte_at_{index:02x}" for index in range(27))
MISSION_TABLE_DOMAIN_64_TABLES = {
    'mission_secondary12_prefix': TableLayout(0x5644FC, 31, '<BBH8B', ('byte_at_00', 'byte_at_01', 'field_02_u16', 'byte_at_04', 'byte_at_05', 'parameter_row_id', 'byte_at_07', 'byte_at_08', 'byte_at_09', 'byte_at_0a', 'byte_at_0b')),
}
MISSION_TABLE_DOMAIN_64_TABLES.update({
    f"mission_parameter27_row_{row_index:03d}": TableLayout(
        0x564670 + row_index * 27, 1, "<27B", MISSION_PARAMETER27_FIELDS)
    for row_index in (*range(0, 51), *range(115, 123))
})
MISSION_TABLE_DOMAIN_64_TABLES['mission_threshold38_prefix'] = TableLayout(0x5653F0, 31, '<38B', ('byte_at_00', 'random_extent_01', 'byte_at_02', 'byte_at_03', 'byte_at_04', 'byte_at_05', 'byte_at_06', 'byte_at_07', 'byte_at_08', 'byte_at_09', 'byte_at_0a', 'byte_at_0b', 'byte_at_0c', 'byte_at_0d', 'byte_at_0e', 'byte_at_0f', 'byte_at_10', 'byte_at_11', 'byte_at_12', 'byte_at_13', 'byte_at_14', 'byte_at_15', 'byte_at_16', 'byte_at_17', 'byte_at_18', 'byte_at_19', 'byte_at_1a', 'byte_at_1b', 'byte_at_1c', 'byte_at_1d', 'byte_at_1e', 'byte_at_1f', 'byte_at_20', 'byte_at_21', 'byte_at_22', 'byte_at_23', 'byte_at_24', 'byte_at_25'))
if (set(LIBRARY42_WAVE13_TABLES) & set(TABLES) or
        set(MISSION_TABLE_DOMAIN_64_TABLES) & (set(TABLES) | set(LIBRARY42_WAVE13_TABLES))):
    raise RuntimeError("new bounded table IDs overlap an existing table set")
TABLE_SETS.update({
    "library42-wave13": LIBRARY42_WAVE13_TABLES,
    "mission-table-domain-64": MISSION_TABLE_DOMAIN_64_TABLES,
})
TABLES.update(LIBRARY42_WAVE13_TABLES)
TABLES.update(MISSION_TABLE_DOMAIN_64_TABLES)

from consumer_bounded_table_registry_codec import (
    LAYOUTS_SHA256 as REGISTERED_LAYOUTS_SHA256,
    TABLE_LAYOUT_ROWS as REGISTERED_TABLE_LAYOUT_ROWS,
)

REGISTERED_TABLE_SETS = {}
for _set_name, _rows in REGISTERED_TABLE_LAYOUT_ROWS.items():
    _layouts = {table_id: TableLayout(*definition)
                for table_id, definition in _rows.items()}
    if (set(_layouts) & set(TABLES) or
            any(layout.end <= layout.start for layout in _layouts.values())):
        raise RuntimeError(f"registered table layout collision: {_set_name}")
    REGISTERED_TABLE_SETS[_set_name] = _layouts
for _set_name, _layouts in REGISTERED_TABLE_SETS.items():
    TABLE_SETS[_set_name] = _layouts
    TABLES.update(_layouts)

def crc32_lookup_words():
    words = []
    for value in range(256):
        for _ in range(8):
            value = (value >> 1) ^ (0xEDB88320 if value & 1 else 0)
        words.append(value)
    return words


def decode_table(rom, table_id, verify_retail=True):
    layout = TABLES[table_id]
    if len(rom) != 0x1000000 or (verify_retail and
            hashlib.sha256(rom).hexdigest() != ROM_SHA256):
        raise ValueError("expected the pinned US retail ROM")
    rows = []
    for index in range(layout.count):
        values = struct.unpack_from(layout.row_format, rom,
                                    layout.start + index * layout.stride)
        row = dict(zip(layout.fields, values))
        if layout.terminator >= 0 and row[layout.fields[0]] == layout.terminator:
            raise ValueError("table terminates before its bounded final entry")
        rows.append(row)
    if table_id == "crc32_lookup_256" and [row[layout.fields[0]] for row in rows] != crc32_lookup_words():
        raise ValueError("CRC-32 lookup recurrence differs")
    if layout.terminator >= 0 and struct.unpack_from("<H", rom,
                                                     layout.end - 2)[0] != layout.terminator:
        raise ValueError("table terminator differs")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "table_id": table_id, "start": layout.start,
            "end_exclusive": layout.end, "row_format": layout.row_format,
            "first_index": layout.first_index, "row_count": layout.count,
            "rows": rows}


def encode_table(asset, table_id):
    layout = TABLES[table_id]
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("table_id"), asset.get("start"),
             asset.get("end_exclusive"), asset.get("row_format"),
             asset.get("first_index"), asset.get("row_count")) !=
            (table_id, layout.start, layout.end, layout.row_format,
             layout.first_index, layout.count)):
        raise ValueError("consumer-bounded table metadata differs")
    rows = asset.get("rows")
    if not isinstance(rows, list) or len(rows) != layout.count:
        raise ValueError("consumer-bounded table row count differs")
    if table_id.startswith("reward_"):
        if any(not isinstance(row, dict) for row in rows):
            raise ValueError("reward row schema differs")
        for group_start, group_end in REWARD_GROUPS:
            if group_start < layout.first_index or group_end > layout.first_index + layout.count:
                continue
            weights = [rows[index - layout.first_index].get("weight_at_00")
                       for index in range(group_start, group_end)]
            if (any(type(weight) is not int or weight <= 0 for weight in weights) or
                    sum(weights) != 100):
                raise ValueError("reward group weights must remain positive and sum to 100")
    output = bytearray()
    for index, row in enumerate(rows):
        if (not isinstance(row, dict) or set(row) != set(layout.fields) or
                any(type(row[field]) is not int for field in layout.fields)):
            raise ValueError(f"{table_id} row {index} schema differs")
        if layout.terminator >= 0 and row[layout.fields[0]] == layout.terminator:
            raise ValueError("premature table terminator")
        if table_id == "initial_audio_copy_words36":
            value = row["copied_u32"]
            if index < 30 and not 0x08000001 <= value < 0x09000000:
                raise ValueError("initial audio callback word leaves observed ROM domain")
        if table_id == "crc32_lookup_256" and row["lookup_remainder"] != crc32_lookup_words()[index]:
            raise ValueError("CRC-32 lookup recurrence differs")
        try:
            output.extend(struct.pack(layout.row_format,
                                      *(row[field] for field in layout.fields)))
        except struct.error as error:
            raise ValueError(f"{table_id} row {index} field out of range") from error
    if layout.terminator >= 0:
        output.extend(struct.pack("<H", layout.terminator))
    if len(output) != layout.end - layout.start:
        raise ValueError("consumer-bounded table encoded length differs")
    return bytes(output)
