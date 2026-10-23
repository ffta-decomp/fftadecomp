"""Lossless, editable ROM pointer table for the retail text callbacks."""

import hashlib
import struct


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
TABLE_START = 0x36D768
ENTRY_COUNT = 173
TABLE_END = TABLE_START + ENTRY_COUNT * 4
CALLER_LITERAL = 0x18D0C


def decode(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if struct.unpack_from("<I", rom, CALLER_LITERAL)[0] != TABLE_START + 0x08000000:
        raise ValueError("text dispatcher table literal differs")
    values = list(struct.unpack_from("<" + "I" * ENTRY_COUNT, rom, TABLE_START))
    if any(value and not (0x08000001 <= value < 0x09000000 and value & 1)
           for value in values):
        raise ValueError("text callback table contains a non-Thumb pointer")
    # The following word starts another data structure, so it is not slot 173.
    if struct.unpack_from("<I", rom, TABLE_END)[0] != 0x10:
        raise ValueError("text callback table end differs")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "start": TABLE_START, "end": TABLE_END, "values": values}


def encode(asset):
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("start"), asset.get("end")) != (TABLE_START, TABLE_END)):
        raise ValueError("text callback table metadata differs")
    values = asset.get("values")
    if not isinstance(values, list) or len(values) != ENTRY_COUNT:
        raise ValueError("text callback table entry count differs")
    if any(type(value) is not int or
           (value != 0 and not (0x08000001 <= value < 0x09000000 and value & 1))
           for value in values):
        raise ValueError("text callback table pointer is invalid")
    return struct.pack("<" + "I" * ENTRY_COUNT, *values)
