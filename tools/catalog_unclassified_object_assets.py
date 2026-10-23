#!/usr/bin/env python3
"""Catalog the bounded object-animation bank without storing game payloads."""
import argparse
import hashlib
import json
import struct
from pathlib import Path

from extract_object_animation_resources import ROM_SHA256

BANK_START = 0x4EF9D8
BANK_END = 0x509F18
REPO = Path(__file__).resolve().parents[1]


def parse_table(rom, base, offset_width, record_width):
    """Infer the count from the first relative offset; require contiguous records."""
    offset_format = '<H' if offset_width == 2 else '<I'
    first_offset = struct.unpack_from(offset_format, rom, base)[0]
    if not first_offset or first_offset % offset_width:
        raise ValueError('invalid offset array extent')
    count = first_offset // offset_width
    if base + first_offset > BANK_END:
        raise ValueError('offset array exceeds bank')
    rebuilt = bytearray(first_offset)
    records = []
    record_positions = []
    cursor = first_offset
    for index in range(count):
        offset = struct.unpack_from(offset_format, rom, base + index * offset_width)[0]
        if offset != cursor:
            raise ValueError('noncontiguous record')
        struct.pack_into(offset_format, rebuilt, index * offset_width, offset)
        item_count = struct.unpack_from('<H', rom, base + offset)[0]
        end = base + offset + 2 + item_count * record_width
        if end > BANK_END:
            raise ValueError('record exceeds bank')
        values = struct.unpack_from('<' + 'H' * (item_count * record_width // 2),
                                    rom, base + offset + 2)
        record_positions.append(base + offset + 2)
        records.append(values)
        rebuilt.extend(struct.pack('<H', item_count))
        rebuilt.extend(struct.pack('<' + 'H' * len(values), *values))
        cursor = end - base
        # Wide sequence offset arrays use word-aligned record starts.
        if offset_width == 4 and index + 1 < count:
            padding = (-cursor) % 4
            if rom[base + cursor:base + cursor + padding] != bytes(padding):
                raise ValueError('nonzero sequence alignment')
            rebuilt.extend(bytes(padding))
            cursor += padding
    return base + cursor, bytes(rebuilt), records, record_positions


def catalog(rom):
    if len(rom) != 0x1000000 or hashlib.sha256(rom).hexdigest() != ROM_SHA256:
        raise ValueError('expected pinned US retail ROM')
    selected = json.loads((REPO / 'config/object-animation-roots.json').read_text())
    anchors = {row['start']: row for row in selected['roots']}
    manifest = json.loads((REPO / 'config/retail-us.json').read_text())
    selected_unclassified = {
        row['offset']: row for row in manifest['modules']
        if row.get('format') == 'unclassified-object-animation-json'
        and row.get('enabled', True)
    }
    rows = []
    cursor = BANK_START
    while cursor < BANK_END:
        start = cursor
        flags, secondary_offset = struct.unpack_from('<HH', rom, start)
        if flags not in (4, 12):
            raise ValueError(f'unexpected flags at {start:#x}')
        first_end, first_bytes, frames, positions = parse_table(rom, start + 4, 2, 6)
        secondary_start = start + secondary_offset
        alignment = secondary_start - first_end
        if alignment not in (0, 2) or rom[first_end:secondary_start] != bytes(alignment):
            raise ValueError('invalid inter-table alignment')
        wide = flags == 4
        end, second_bytes, sequences, _ = parse_table(
            rom, secondary_start, 4 if wide else 2, 4 if wide else 2)
        frame_ids = [value for seq in sequences for value in
                     (seq[::2] if wide else [word & 255 for word in seq])]
        if any(index >= len(frames) for index in frame_ids):
            raise ValueError('sequence references absent frame')
        rebuilt = struct.pack('<HH', flags, secondary_offset) + first_bytes + bytes(alignment) + second_bytes
        if rebuilt != rom[start:end]:
            raise ValueError('typed reconstruction differs')
        first_nonempty = next((i for i, frame in enumerate(frames) if frame), None)
        mutation_offset = None
        if first_nonempty is not None:
            mutation_offset = positions[first_nonempty]
            changed = bytearray(rebuilt)
            changed_fields = list(frames[first_nonempty])
            changed_fields[0] ^= 1
            struct.pack_into('<' + 'H' * len(changed_fields), changed,
                             mutation_offset - start, *changed_fields)
            differences = [start + i for i, (a, b) in enumerate(zip(rebuilt, changed)) if a != b]
            if differences != [mutation_offset]:
                raise ValueError('mutation offset differs')
        next_start = (end + 3) & ~3
        if rom[end:next_start] != bytes(next_start - end):
            raise ValueError('nonzero resource alignment')
        anchor = anchors.get(start)
        if anchor and anchor['end'] != end:
            raise ValueError('integrated resource extent differs')
        for literal in anchor['literal_offsets'] if anchor else []:
            if struct.unpack_from('<I', rom, literal)[0] != 0x08000000 + start:
                raise ValueError('literal reference differs')
        integrated = selected_unclassified.get(start)
        if integrated and integrated['size'] != next_start - start:
            raise ValueError('selected unclassified resource extent differs')
        if integrated and anchor:
            raise ValueError('object resource is selected twice')
        rows.append({
            'id': f'object-animation-{start:06x}',
            'classification': 'unclassified', 'asset_type': 'object-frame-and-animation-tables',
            'rom_start': start, 'rom_end_exclusive': end, 'gba_address': 0x08000000 + start,
            'span_bytes': end - start, 'flags': flags,
            'frame_count': len(frames), 'sprite_piece_count': sum(len(frame) // 3 for frame in frames),
            'sequence_count': len(sequences), 'sequence_step_count': len(frame_ids),
            'first_table_end': first_end, 'secondary_table_start': secondary_start,
            'inter_table_alignment_bytes': alignment, 'following_alignment_bytes': next_start - end,
            'literal_offsets': anchor['literal_offsets'] if anchor else [],
            'build_status': 'selected' if anchor or integrated else 'cataloged-not-selected',
            'evidence': 'literal-anchored' if anchor else 'contiguous-structural-parse',
            'exact_typed_roundtrip': True, 'mutation_rom_offset': mutation_offset,
            'source_sha256': hashlib.sha256(rebuilt).hexdigest(),
            'graphics_binding': 'unresolved', 'palette_binding': 'unresolved',
            'gameplay_role': None,
            'suggested_external_path': f'unclassified/object-animations/{start:08x}.json'})
        cursor = next_start
    if cursor != BANK_END or len(rows) != 199:
        raise ValueError('bank partition differs')
    return {'schema_version': 1, 'reference_sha256': ROM_SHA256,
            'bank_start': BANK_START, 'bank_end_exclusive': BANK_END,
            'scope': 'Address inventory only. Payloads remain external. Structural classification does not prove runtime reachability or gameplay role.',
            'resource_count': len(rows), 'span_bytes': sum(row['span_bytes'] for row in rows),
            'following_alignment_bytes': sum(row['following_alignment_bytes'] for row in rows),
            'selected_count': sum(row['build_status'] == 'selected' for row in rows), 'resources': rows}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    result = catalog(args.rom.read_bytes())
    args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({key: value for key, value in result.items() if key != 'resources'}))


if __name__ == '__main__':
    main()
