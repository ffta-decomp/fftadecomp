"""Decode the consumer-backed US retail song table and bounded song headers.

Track bodies and voicegroups are pointers only here. A zero-track header owns
four bytes; the following word belongs to a different, unclassified region.
"""

import hashlib
import struct
from collections import defaultdict


ROM_BASE = 0x08000000
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
SONG_TABLE_START = 0x14BB48
SONG_COUNT = 640
SONG_ENTRY_BYTES = 8
PLAYER_TABLE_START = 0x14BB24
PLAYER_COUNT = 3
PLAYER_RECORD_BYTES = 12


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def checked_integer(value, bits, name):
    if type(value) is not int or not 0 <= value < 1 << bits:
        raise ValueError(f"invalid {name}")
    return value


def checked_rom_offset(value, name):
    if type(value) is not int or not 0 <= value < 0x1000000:
        raise ValueError(f"invalid {name}")
    return value


def decode_song_assets(rom):
    """Use the table's pointers to decode exactly the bytes each header owns."""
    if len(rom) != 0x1000000:
        raise ValueError("expected a 16 MiB GBA ROM")
    entries = []
    aliases = defaultdict(list)
    for song_id in range(SONG_COUNT):
        site = SONG_TABLE_START + song_id * SONG_ENTRY_BYTES
        header_pointer, player_index, field_06 = struct.unpack_from("<IHH", rom, site)
        header_offset = header_pointer - ROM_BASE
        if (not 0 <= header_offset < len(rom) or header_offset % 4 or
                player_index >= PLAYER_COUNT):
            raise ValueError(f"song {song_id} has an invalid header or player")
        aliases[header_offset].append(song_id)
        entries.append({"song_id": song_id, "header_offset": header_offset,
                        "player_index": player_index, "field_06": field_06})
    headers = []
    for offset, song_ids in sorted(aliases.items()):
        track_count, field_01, priority, control_byte_3 = rom[offset:offset + 4]
        if track_count > 16:
            raise ValueError(f"song header {offset:#x} has too many tracks")
        size = 4 if track_count == 0 else 8 + 4 * track_count
        if offset + size > len(rom):
            raise ValueError("song header leaves ROM")
        header = {"start": offset, "end": offset + size,
                  "song_ids": song_ids, "track_count": track_count,
                  "field_01": field_01, "priority": priority,
                  "control_byte_3": control_byte_3,
                  "source_sha256": sha256(rom[offset:offset + size])}
        if track_count:
            voice_pointer = struct.unpack_from("<I", rom, offset + 4)[0]
            track_pointers = struct.unpack_from("<" + "I" * track_count,
                                                rom, offset + 8)
            pointers = (voice_pointer, *track_pointers)
            if any(not ROM_BASE <= pointer < ROM_BASE + len(rom)
                   for pointer in pointers):
                raise ValueError(f"song header {offset:#x} has an invalid pointer")
            header["voicegroup_offset"] = voice_pointer - ROM_BASE
            header["track_entry_offsets"] = [pointer - ROM_BASE
                                             for pointer in track_pointers]
        headers.append(header)
    if any(left["end"] > right["start"]
           for left, right in zip(headers, headers[1:])):
        raise ValueError("song headers overlap")
    return {"schema_version": 1, "reference_sha256": sha256(rom),
            "song_table": {"start": SONG_TABLE_START,
                           "end": SONG_TABLE_START + SONG_COUNT * SONG_ENTRY_BYTES,
                           "entry_bytes": SONG_ENTRY_BYTES,
                           "entries": entries,
                           "source_sha256": sha256(rom[SONG_TABLE_START:
                                                        SONG_TABLE_START + SONG_COUNT * SONG_ENTRY_BYTES])},
            "headers": headers,
            "header_bytes": sum(row["end"] - row["start"] for row in headers),
            "scope_note": "Song table and bounded headers only; track bodies, voicegroups, PCM guards, and mixer behavior are outside this asset."}


def encode_song_table(asset):
    table = asset["song_table"]
    if (table["start"], table["end"], table["entry_bytes"]) != (
            SONG_TABLE_START, SONG_TABLE_START + SONG_COUNT * SONG_ENTRY_BYTES,
            SONG_ENTRY_BYTES):
        raise ValueError("song table boundary differs")
    entries = table["entries"]
    if len(entries) != SONG_COUNT:
        raise ValueError("song table entry count differs")
    known_headers = {row["start"] for row in asset["headers"]}
    output = bytearray()
    for song_id, row in enumerate(entries):
        header = checked_rom_offset(row["header_offset"], "song header offset")
        if row["song_id"] != song_id or header not in known_headers or header % 4:
            raise ValueError(f"song {song_id} selects an unknown header")
        player = checked_integer(row["player_index"], 16, "song player index")
        if player >= PLAYER_COUNT:
            raise ValueError("song player index leaves the player table")
        output.extend(struct.pack("<IHH", ROM_BASE + header, player,
                                  checked_integer(row["field_06"], 16,
                                                  "song field_06")))
    return bytes(output)


def encode_song_header(asset, start):
    matches = [row for row in asset["headers"] if row["start"] == start]
    if len(matches) != 1:
        raise ValueError("song header selection is not unique")
    row = matches[0]
    count = checked_integer(row["track_count"], 8, "track count")
    if count > 16:
        raise ValueError("song header has too many tracks")
    output = bytearray((count,
                        checked_integer(row["field_01"], 8, "header field_01"),
                        checked_integer(row["priority"], 8, "header priority"),
                        checked_integer(row["control_byte_3"], 8,
                                        "header control byte")))
    if count:
        tracks = row["track_entry_offsets"]
        if len(tracks) != count:
            raise ValueError("song header track count differs")
        voice = checked_rom_offset(row["voicegroup_offset"], "voicegroup offset")
        output.extend(struct.pack("<I", ROM_BASE + voice))
        for track in tracks:
            output.extend(struct.pack("<I", ROM_BASE +
                                      checked_rom_offset(track, "track offset")))
    elif "voicegroup_offset" in row or "track_entry_offsets" in row:
        raise ValueError("zero-track sentinel has no proven pointer fields")
    if row["end"] != start + len(output):
        raise ValueError("song header size differs")
    return bytes(output)


def verify_song_assets(asset, rom):
    if (asset["schema_version"] != 1 or
            asset["reference_sha256"] != ROM_SHA256 or
            sha256(rom) != ROM_SHA256):
        raise ValueError("song asset input revision differs")
    if asset["song_table"]["source_sha256"] != sha256(
            rom[SONG_TABLE_START:SONG_TABLE_START + SONG_COUNT * SONG_ENTRY_BYTES]):
        raise ValueError("song table source hash differs")
    if encode_song_table(asset) != rom[SONG_TABLE_START:
                                       SONG_TABLE_START + SONG_COUNT * SONG_ENTRY_BYTES]:
        raise ValueError("song table does not reproduce retail")
    if len(asset["headers"]) != 455 or asset["header_bytes"] != 10076:
        raise ValueError("song header count or byte total differs")
    aliases = defaultdict(list)
    for row in asset["song_table"]["entries"]:
        aliases[row["header_offset"]].append(row["song_id"])
    for row in asset["headers"]:
        start, end = row["start"], row["end"]
        if row["song_ids"] != aliases[start] or row["source_sha256"] != sha256(
                rom[start:end]) or encode_song_header(asset, start) != rom[start:end]:
            raise ValueError(f"song header {start:#x} does not reproduce retail")
    return 5120 + asset["header_bytes"]
