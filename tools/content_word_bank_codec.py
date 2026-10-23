"""Lossless, size-preserving US retail content-word bank codec."""

import hashlib
import json
import struct
from pathlib import Path
from typing import NamedTuple

from extract_resources import decode_word
from scene_text_codec import encode_tokens


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
PAYLOAD_START = 0x52336C
POINTER_START = 0x526680
ENTRY_COUNT = 754
TABLE_END = POINTER_START + ENTRY_COUNT * 4
CONSUMER_LITERAL = 0x18DA4


class WordBankLayout(NamedTuple):
    payload_start: int
    pointer_start: int
    word_count: int
    zero_alignment: int
    consumer_literal: int

    @property
    def end(self):
        return self.pointer_start + self.word_count * 4


WORD_BANKS = {
    "battle": WordBankLayout(0x5541B4, 0x5567F0, 767, 3, 0x9028),
    "rumor": WordBankLayout(0x5577EC, 0x557E98, 92, 1, 0x5FD9C),
    "quest": WordBankLayout(0x558008, 0x55A64C, 512, 2, 0x191F0),
    "clan": WordBankLayout(0x56588C, 0x565F14, 128, 2, 0x9A10),
    "system": WordBankLayout(0x5661F8, 0x5668B0, 84, 2, 0x39F54),
    "name": WordBankLayout(0x566A00, 0x5680DC, 725, 0, 0xC9ED0),
    "title": WordBankLayout(0x568C30, 0x569034, 52, 0, 0x192BC),
    "reference_names": WordBankLayout(0x55128C, 0x5516D0, 107, 0, 0x16264),
}


def encode_word_entry(entry, cursor, verify_retail):
    if entry.get("status") != "decoded" or entry.get("rom_offset") != cursor:
        raise ValueError("content word payload offset differs")
    encoded = encode_tokens({**entry, "encoding": "normal",
                             "decoded_sha256": entry["raw_sha256"]},
                            verify_hash=verify_retail)
    if len(encoded) != entry.get("size"):
        raise ValueError("content word edit changes the fixed allocation")
    decoded = decode_word(encoded, 0)
    if decoded["size"] != len(encoded) or decoded["tokens"] != entry["tokens"]:
        raise ValueError("content word edit changes token boundaries")
    return encoded


def decode_catalog_bank(rom, bank_id, verify_retail=True):
    layout = WORD_BANKS[bank_id]
    if len(rom) != 0x1000000 or (verify_retail and
            hashlib.sha256(rom).hexdigest() != ROM_SHA256):
        raise ValueError("expected the pinned US retail ROM")
    if struct.unpack_from("<I", rom, layout.consumer_literal)[0] != \
            0x08000000 + layout.pointer_start:
        raise ValueError("word-bank consumer literal differs")
    entries = []
    cursor = layout.payload_start
    for index in range(layout.word_count):
        pointer_offset = layout.pointer_start + index * 4
        pointer = struct.unpack_from("<I", rom, pointer_offset)[0]
        if pointer != 0x08000000 + cursor:
            raise ValueError(f"{bank_id} pointer {index} breaks the payload")
        word = decode_word(rom, cursor)
        word.update({"index": index, "status": "decoded",
                     "pointer_rom_offset": pointer_offset})
        entries.append(word)
        cursor += word["size"]
    if (layout.pointer_start - cursor != layout.zero_alignment or
            any(rom[cursor:layout.pointer_start])):
        raise ValueError(f"{bank_id} alignment differs")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "bank_id": bank_id, "payload_start": layout.payload_start,
            "pointer_start": layout.pointer_start, "table_end": layout.end,
            "word_count": layout.word_count,
            "zero_alignment": layout.zero_alignment, "entries": entries}


def encode_catalog_bank(asset, bank_id, verify_retail=True):
    layout = WORD_BANKS[bank_id]
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            asset.get("bank_id") != bank_id or
            (asset.get("payload_start"), asset.get("pointer_start"),
             asset.get("table_end"), asset.get("word_count"),
             asset.get("zero_alignment")) !=
            (layout.payload_start, layout.pointer_start, layout.end,
             layout.word_count, layout.zero_alignment)):
        raise ValueError("catalog word-bank metadata differs")
    entries = asset.get("entries")
    if not isinstance(entries, list) or len(entries) != layout.word_count:
        raise ValueError("catalog word-bank entry count differs")
    payload = bytearray()
    pointers = []
    for index, entry in enumerate(entries):
        cursor = layout.payload_start + len(payload)
        if (entry.get("index") != index or entry.get("pointer_rom_offset") !=
                layout.pointer_start + index * 4):
            raise ValueError("catalog word-bank pointer index differs")
        payload.extend(encode_word_entry(entry, cursor, verify_retail))
        pointers.append(0x08000000 + cursor)
    if layout.payload_start + len(payload) + layout.zero_alignment != \
            layout.pointer_start:
        raise ValueError("catalog word-bank payload length differs")
    return (bytes(payload) + bytes(layout.zero_alignment) +
            struct.pack("<" + "I" * layout.word_count, *pointers))


def decode(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    if struct.unpack_from("<I", rom, CONSUMER_LITERAL)[0] != 0x08000000 + POINTER_START:
        raise ValueError("content pointer consumer literal differs")
    entries = []
    cursor = PAYLOAD_START
    for index in range(ENTRY_COUNT):
        pointer_offset = POINTER_START + 4 * index
        pointer = struct.unpack_from("<I", rom, pointer_offset)[0]
        if index == ENTRY_COUNT - 1:
            if pointer != 0:
                raise ValueError("content bank terminal pointer is not null")
            entries.append({"index": index, "status": "null",
                            "pointer_rom_offset": pointer_offset})
            continue
        if pointer != 0x08000000 + cursor:
            raise ValueError(f"content pointer {index} breaks the contiguous payload")
        word = decode_word(rom, cursor)
        word.update({"index": index, "status": "decoded",
                     "pointer_rom_offset": pointer_offset})
        entries.append(word)
        cursor += word["size"]
    if cursor != POINTER_START:
        raise ValueError("content payload does not reach its pointer table")
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "payload_start": PAYLOAD_START, "pointer_start": POINTER_START,
            "table_end": TABLE_END, "entries": entries}


def encode(asset, verify_retail=True):
    if (asset.get("schema_version") != 1 or
            asset.get("reference_sha256") != ROM_SHA256 or
            (asset.get("payload_start"), asset.get("pointer_start"),
             asset.get("table_end")) != (PAYLOAD_START, POINTER_START, TABLE_END)):
        raise ValueError("content bank metadata differs")
    entries = asset.get("entries")
    if not isinstance(entries, list) or len(entries) != ENTRY_COUNT:
        raise ValueError("content bank entry count differs")
    payload = bytearray()
    pointers = []
    cursor = PAYLOAD_START
    for index, entry in enumerate(entries):
        if entry.get("index") != index or entry.get("pointer_rom_offset") != \
                POINTER_START + index * 4:
            raise ValueError("content bank pointer index differs")
        if index == ENTRY_COUNT - 1:
            if entry.get("status") != "null":
                raise ValueError("content bank terminal slot differs")
            pointers.append(0)
            continue
        encoded = encode_word_entry(entry, cursor, verify_retail)
        payload.extend(encoded)
        pointers.append(0x08000000 + cursor)
        cursor += len(encoded)
    if cursor != POINTER_START:
        raise ValueError("content bank payload length differs")
    return bytes(payload) + struct.pack("<" + "I" * ENTRY_COUNT, *pointers)


def export(rom, directory):
    asset = decode(rom)
    encoded = encode(asset)
    if encoded != rom[PAYLOAD_START:TABLE_END]:
        raise ValueError("content bank round trip differs")
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    (directory / "content-word-bank.json").write_text(
        json.dumps(asset, indent=2, ensure_ascii=False) + "\n")
    return {"entries": ENTRY_COUNT, "decoded_entries": ENTRY_COUNT - 1,
            "selected_resource_bytes": len(encoded),
            "payload_bytes": POINTER_START - PAYLOAD_START,
            "pointer_bytes": TABLE_END - POINTER_START}
