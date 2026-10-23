"""Preserve header-linked voice roots and their referenced PCM sample bank.

The byte after each sample payload is represented as a neutral trailing byte.
The data proves its physical presence, but its mixer lookahead role is not yet
established. Zero bytes after it are recorded separately as alignment.
"""

import hashlib
import struct
from collections import Counter, defaultdict

from audio_song_codec import ROM_BASE, ROM_SHA256


SAMPLE_BANK_START = 0x14CF4C
SAMPLE_BANK_END = 0x3337E4
TONE_RECORD_BYTES = 12
TONE_TYPES = {0, 1, 2, 3, 8, 0x40, 0x80}
PCM_TYPES = {0, 8}
EXPECTED_ROOTS = (0x14A004, 0x14A580, 0x14AB80, 0x14B174)
EXPECTED_ROOT_COUNTS = (117, 128, 127, 127)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def tone_record(rom, site):
    kind, field_01, field_02, field_03, word_04, word_08 = struct.unpack_from(
        "<4BII", rom, site)
    if kind not in TONE_TYPES:
        raise ValueError(f"unsupported tone record at {site:#x}")
    return {"rom_offset": site, "kind": kind, "field_01": field_01,
            "field_02": field_02, "field_03": field_03,
            "word_04": word_04, "word_08": word_08}


def decode_tone_pcm_assets(rom, song_asset, candidates, candidate_sha256):
    if len(rom) != 0x1000000 or sha256(rom) != ROM_SHA256:
        raise ValueError("expected pinned US retail ROM")
    if (song_asset["reference_sha256"] != ROM_SHA256 or
            candidates["reference_sha256"] != ROM_SHA256 or
            candidates["sample_count"] != 285):
        raise ValueError("song headers or PCM candidates differ from retail")
    roots = sorted({row["voicegroup_offset"] for row in song_asset["headers"]
                    if row["track_count"]})
    if tuple(roots) != EXPECTED_ROOTS:
        raise ValueError("song headers select unexpected voice roots")
    groups = []
    for index, start in enumerate(roots):
        if index + 1 < len(roots):
            end = roots[index + 1]
        else:
            # The next 12-byte position has type 0x57 and a non-ROM word;
            # that is the first key-map byte sequence, not another tone.
            end = start
            while rom[end] in TONE_TYPES:
                end += TONE_RECORD_BYTES
            if (end, rom[end]) != (0x14B768, 0x57):
                raise ValueError("last voice root termination differs")
        if (end - start) % TONE_RECORD_BYTES:
            raise ValueError("voice root is not a 12-byte record group")
        records = [tone_record(rom, site)
                   for site in range(start, end, TONE_RECORD_BYTES)]
        groups.append({"start": start, "end": end, "records": records,
                       "source_sha256": sha256(rom[start:end])})
    if tuple(len(group["records"]) for group in groups) != EXPECTED_ROOT_COUNTS:
        raise ValueError("voice root record counts differ")
    pcm_sites = {row["rom_offset"]: row for group in groups
                 for row in group["records"] if row["kind"] in PCM_TYPES}
    if len(pcm_sites) != 446:
        raise ValueError("PCM tone record count differs")
    samples = []
    references = defaultdict(list)
    for candidate in candidates["samples"]:
        start = candidate["start"]
        if start % 4 or not SAMPLE_BANK_START <= start < SAMPLE_BANK_END:
            raise ValueError("PCM sample start is not in the bounded bank")
        references[start].extend(candidate["tone_candidate_sites"])
    for site, tone in pcm_sites.items():
        pointer = tone["word_04"]
        if not ROM_BASE + SAMPLE_BANK_START <= pointer < ROM_BASE + SAMPLE_BANK_END:
            raise ValueError(f"PCM tone {site:#x} does not point into the sample bank")
        if site not in references[pointer - ROM_BASE]:
            raise ValueError(f"PCM tone {site:#x} is absent from candidate references")
    if set(pcm_sites) != {site for sites in references.values() for site in sites}:
        raise ValueError("candidate scan contains a non-root PCM tone")
    cursor = SAMPLE_BANK_START
    for candidate in candidates["samples"]:
        start, payload_end = candidate["start"], candidate["payload_end"]
        count = candidate["sample_count"]
        physical_end = (payload_end + 4) & ~3
        if start != cursor or payload_end != start + 16 + count or \
                physical_end > SAMPLE_BANK_END:
            raise ValueError("PCM sample physical spans are not contiguous")
        wave_type, status, frequency, loop_start, header_count = \
            struct.unpack_from("<HHIII", rom, start)
        if ((wave_type, status, frequency, loop_start, header_count) !=
                (candidate["wave_type"], candidate["status"],
                 candidate["frequency_raw"], candidate["loop_start"], count) or
                wave_type != 0 or not 0 <= loop_start <= count or
                sha256(rom[start:payload_end]) != candidate["sha256"] or
                any(rom[payload_end + 1:physical_end])):
            raise ValueError(f"PCM sample {start:#x} differs from candidate")
        samples.append({"start": start, "payload_end": payload_end,
                        "physical_end": physical_end,
                        "wave_type": wave_type, "status": status,
                        "frequency_raw": frequency, "loop_start": loop_start,
                        "sample_count": count,
                        "trailing_byte": rom[payload_end],
                        "padding_bytes": physical_end - payload_end - 1,
                        "payload_file": f"samples/{start:06x}.pcm",
                        "payload_sha256": sha256(rom[start + 16:payload_end]),
                        "source_sha256": sha256(rom[start:physical_end]),
                        "tone_sites": sorted(references[start])})
        cursor = physical_end
    if cursor != SAMPLE_BANK_END or len(samples) != 285 or \
            sum(row["padding_bytes"] for row in samples) != 424:
        raise ValueError("PCM bank boundary or padding differs")
    type_counts = Counter(row["kind"] for group in groups for row in group["records"])
    return {"schema_version": 1, "reference_sha256": ROM_SHA256,
            "candidate_report_sha256": candidate_sha256,
            "tone_roots": groups,
            "tone_record_count": sum(len(group["records"]) for group in groups),
            "tone_type_counts": {str(key): value for key, value in sorted(type_counts.items())},
            "pcm_tone_sites": len(pcm_sites),
            "sample_bank": {"start": SAMPLE_BANK_START, "end": SAMPLE_BANK_END,
                            "source_sha256": sha256(rom[SAMPLE_BANK_START:SAMPLE_BANK_END]),
                            "padding_bytes": 424, "samples": samples},
            "scope_note": "All PCM candidates have a pointer from one of four header-linked voice roots. A physical trailing byte and zero alignment follow each payload; mixer use and individual track reachability are unproven."}


def encode_tone_root(asset, start):
    groups = [row for row in asset["tone_roots"] if row["start"] == start]
    if len(groups) != 1:
        raise ValueError("tone root selection is not unique")
    group = groups[0]
    output = bytearray()
    for index, record in enumerate(group["records"]):
        if record["rom_offset"] != start + index * TONE_RECORD_BYTES or \
                record["kind"] not in TONE_TYPES:
            raise ValueError("tone root record position or kind differs")
        values = (record["kind"], record["field_01"], record["field_02"],
                  record["field_03"], record["word_04"], record["word_08"])
        if any(type(value) is not int or not 0 <= value < 1 << bits
               for value, bits in zip(values, (8, 8, 8, 8, 32, 32))):
            raise ValueError("tone root field width differs")
        output.extend(struct.pack("<4BII", *values))
    if group["end"] != start + len(output):
        raise ValueError("tone root boundary differs")
    return bytes(output)


def encode_pcm_bank(asset, source_dir, verify_retail=True):
    bank = asset["sample_bank"]
    if (bank["start"], bank["end"], bank["padding_bytes"]) != (
            SAMPLE_BANK_START, SAMPLE_BANK_END, 424):
        raise ValueError("PCM bank boundary or padding differs")
    output = bytearray()
    for row in bank["samples"]:
        if row["start"] != SAMPLE_BANK_START + len(output):
            raise ValueError("PCM sample start differs")
        payload_path = (source_dir / row["payload_file"]).resolve()
        if not payload_path.is_relative_to(source_dir.resolve()):
            raise ValueError("PCM payload escapes asset directory")
        payload = payload_path.read_bytes()
        if len(payload) != row["sample_count"] or \
                (verify_retail and sha256(payload) != row["payload_sha256"]):
            raise ValueError("PCM payload length or retail hash differs")
        fields = (row["wave_type"], row["status"], row["frequency_raw"],
                  row["loop_start"], row["sample_count"])
        if any(type(value) is not int or not 0 <= value < 1 << bits
               for value, bits in zip(fields, (16, 16, 32, 32, 32))) or \
                fields[0] != 0 or fields[3] > fields[4]:
            raise ValueError("PCM header field width or loop differs")
        trailing = row["trailing_byte"]
        padding = row["padding_bytes"]
        if type(trailing) is not int or not 0 <= trailing <= 255 or \
                type(padding) is not int or not 0 <= padding <= 3:
            raise ValueError("PCM trailing byte or alignment differs")
        data = struct.pack("<HHIII", *fields) + payload + bytes([trailing]) + bytes(padding)
        if row["payload_end"] != row["start"] + 16 + len(payload) or \
                row["physical_end"] != row["start"] + len(data) or \
                row["physical_end"] % 4 or \
                (verify_retail and sha256(data) != row["source_sha256"]):
            raise ValueError("PCM sample physical span differs")
        output.extend(data)
    if len(bank["samples"]) != 285 or len(output) != SAMPLE_BANK_END - SAMPLE_BANK_START or \
            (verify_retail and sha256(output) != bank["source_sha256"]):
        raise ValueError("PCM bank does not reproduce its bounded source")
    return bytes(output)


def pcm_payload_files(asset, source_dir):
    for row in asset["sample_bank"]["samples"]:
        yield source_dir / row["payload_file"]
