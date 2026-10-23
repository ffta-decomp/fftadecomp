"""Extract editable indexed pixels from the bounded scene transfer tile bank."""
import hashlib
import importlib.util
import json
import struct
from pathlib import Path

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
DESCRIPTOR_START = 0x3A832C
DESCRIPTOR_END = 0x3A8410
DESCRIPTOR_COUNT = 19
DATA_START = 0xA1BEDC
DATA_END = 0xA3311C
MAP_DATA_START = 0xA3311C
MAP_BLOCK_BYTES = 1200
MAP_HALFWORDS = 600
VRAM_DESTINATION = 0x06008A40
TILE_BYTES = 32
DMA_CALLS_PER_DESCRIPTOR = 4
TABLE_START_LITERAL = 0x12BE14
TABLE_END_LITERAL = 0x12C1F4
SOURCE_BASE_LITERAL = 0x12BEB0
DESTINATION_LITERAL = 0x12BEB4


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def load_graphics_codec(path):
    path = Path(path).resolve()
    spec = importlib.util.spec_from_file_location("indexed_graphics_codec", path)
    if spec is None or spec.loader is None:
        raise ValueError("could not load indexed_graphics_codec")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    required = ("rasterize_4bpp_grid", "serialize_4bpp_grid",
                "write_index_png", "read_index_png")
    if any(not hasattr(module, name) for name in required):
        raise ValueError("indexed_graphics_codec is missing a required 4bpp helper")
    return module


def tile_grid(tile_count):
    if not 1 <= tile_count <= 64:
        raise ValueError("one editable PNG page must contain 1..64 tiles")
    columns = max(value for value in range(1, int(tile_count ** 0.5) + 1)
                  if tile_count % value == 0)
    rows = tile_count // columns
    return columns, rows


def tile_page_specs(group_index, tile_count):
    pages = []
    start = 0
    while start < tile_count:
        count = min(64, tile_count - start)
        columns, rows = tile_grid(count)
        pages.append({
            "page": len(pages),
            "tile_start": start,
            "tile_count": count,
            "tile_columns": columns,
            "tile_rows": rows,
            "file": f"tiles/group-{group_index:02d}-page-{len(pages):02d}.png",
        })
        start += count
    return pages


def parse_descriptor_table(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("input ROM is not the pinned US retail revision")
    anchors = ((TABLE_START_LITERAL, ROM_BASE + DESCRIPTOR_START),
               (TABLE_END_LITERAL, ROM_BASE + DESCRIPTOR_END),
               (SOURCE_BASE_LITERAL, ROM_BASE + DATA_START),
               (DESTINATION_LITERAL, VRAM_DESTINATION))
    if any(struct.unpack_from("<I", rom, offset)[0] != value
           for offset, value in anchors):
        raise ValueError("loader literals do not match selected transfer family")
    if DESCRIPTOR_END - DESCRIPTOR_START != DESCRIPTOR_COUNT * 12:
        raise ValueError("descriptor span size differs")
    records = []
    cumulative = 0
    for index in range(DESCRIPTOR_COUNT):
        entry_offset = DESCRIPTOR_START + index * 12
        offset, length, map_pointer = struct.unpack_from("<III", rom, entry_offset)
        if offset != cumulative or length == 0 or length % TILE_BYTES:
            raise ValueError(f"descriptor {index} has invalid offset or tile length")
        if length % 16:
            raise ValueError(f"descriptor {index} length cannot form four equal DMA chunks")
        map_start = map_pointer - ROM_BASE
        expected_map = MAP_DATA_START + index * MAP_BLOCK_BYTES
        if map_start != expected_map or map_start + MAP_BLOCK_BYTES > len(rom):
            raise ValueError(f"descriptor {index} map pointer differs")
        map_values = struct.unpack_from("<600H", rom, map_start)
        low_indices = [value & 0x03FF for value in map_values if value & 0x03FF]
        tile_count = length // TILE_BYTES
        maximum_tile = 82 + tile_count - 1
        if not low_indices or min(low_indices) != 82 or max(low_indices) > maximum_tile:
            raise ValueError(f"descriptor {index} map tile indices exceed candidate range")
        pages = tile_page_specs(index, tile_count)
        chunks = []
        chunk_bytes = length // 4
        word_count = length // 16
        for chunk_index in range(DMA_CALLS_PER_DESCRIPTOR):
            source = DATA_START + offset + chunk_index * chunk_bytes
            destination = VRAM_DESTINATION + chunk_index * chunk_bytes
            chunks.append({
                "chunk": chunk_index,
                "source_start": source,
                "source_end_exclusive": source + chunk_bytes,
                "destination_start": destination,
                "destination_end_exclusive": destination + chunk_bytes,
                "word_count_u32": word_count,
                "transfer_bytes": word_count * 4,
            })
        data = rom[DATA_START + offset:DATA_START + offset + length]
        records.append({
            "index": index,
            "descriptor_rom_offset": entry_offset,
            "cumulative_source_offset": offset,
            "length_bytes": length,
            "source_start": DATA_START + offset,
            "source_end_exclusive": DATA_START + offset + length,
            "tile_count_4bpp_8x8": tile_count,
            "tile_pages": pages,
            "tile_source_sha256": sha256(data),
            "map_pointer_gba": map_pointer,
            "map_start_rom_offset": map_start,
            "map_halfword_count": MAP_HALFWORDS,
            "map_sha256": sha256(rom[map_start:map_start + MAP_BLOCK_BYTES]),
            "map_low10_nonzero_count": len(low_indices),
            "map_low10_min_nonzero": min(low_indices),
            "map_low10_max_nonzero": max(low_indices),
            "candidate_tile_index_range": [82, maximum_tile],
            "transfer_chunks": chunks,
        })
        cumulative += length
    if cumulative != DATA_END - DATA_START:
        raise ValueError("descriptor lengths do not cover the selected source range")
    if records[-1]["source_end_exclusive"] != DATA_END:
        raise ValueError("last descriptor does not end at selected source boundary")
    return records


def encode_descriptor_table(manifest):
    if (manifest.get("descriptor_start"), manifest.get("descriptor_end"),
            manifest.get("descriptor_count")) != (
                DESCRIPTOR_START, DESCRIPTOR_END, DESCRIPTOR_COUNT):
        raise ValueError("descriptor manifest boundary differs")
    output = bytearray()
    cumulative = 0
    for index, record in enumerate(manifest["records"]):
        if record["index"] != index or record["cumulative_source_offset"] != cumulative:
            raise ValueError("descriptor order or cumulative offset differs")
        map_pointer = record["map_pointer_gba"]
        if map_pointer != ROM_BASE + MAP_DATA_START + index * MAP_BLOCK_BYTES:
            raise ValueError("descriptor map pointer differs")
        length = record["length_bytes"]
        if length != record["tile_count_4bpp_8x8"] * TILE_BYTES:
            raise ValueError("descriptor tile count differs from byte length")
        output.extend(struct.pack("<III", cumulative, length, map_pointer))
        cumulative += length
    if len(output) != DESCRIPTOR_END - DESCRIPTOR_START:
        raise ValueError("descriptor table output size differs")
    return bytes(output)


def encode_tile_bank(manifest, tile_dir, graphics_codec, verify_hash=True):
    output = bytearray()
    for index, record in enumerate(manifest["records"]):
        if record["index"] != index:
            raise ValueError("tile groups are not in descriptor order")
        group_raw = bytearray()
        expected_tile_start = 0
        for page in record["tile_pages"]:
            if page["tile_start"] != expected_tile_start:
                raise ValueError(f"tile group {index} page order differs")
            width, height, pixels = graphics_codec.read_index_png(
                Path(tile_dir).parent / page["file"])
            expected_shape = (page["tile_columns"] * 8,
                              page["tile_rows"] * 8)
            if (width, height) != expected_shape:
                raise ValueError(f"tile group {index} page dimensions differ")
            page_raw = graphics_codec.serialize_4bpp_grid(
                pixels, page["tile_columns"], page["tile_rows"])
            if len(page_raw) != page["tile_count"] * TILE_BYTES:
                raise ValueError(f"tile group {index} page tile count differs")
            group_raw.extend(page_raw)
            expected_tile_start += page["tile_count"]
        if expected_tile_start != record["tile_count_4bpp_8x8"]:
            raise ValueError(f"tile group {index} pages do not cover its tile count")
        raw = bytes(group_raw)
        if len(raw) != record["length_bytes"]:
            raise ValueError(f"tile group {index} byte length differs")
        if verify_hash and sha256(raw) != record["tile_source_sha256"]:
            raise ValueError(f"tile group {index} pixels differ from retail")
        output.extend(raw)
    if len(output) != DATA_END - DATA_START:
        raise ValueError("encoded tile bank length differs")
    return bytes(output)


def export(rom, output_dir, graphics_codec):
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    records = parse_descriptor_table(rom)
    tile_dir = output_dir / "tiles"
    tile_dir.mkdir(exist_ok=True)
    for record in records:
        start = record["source_start"]
        raw = rom[start:record["source_end_exclusive"]]
        for page in record["tile_pages"]:
            page_start = page["tile_start"] * TILE_BYTES
            page_end = page_start + page["tile_count"] * TILE_BYTES
            page_raw = raw[page_start:page_end]
            pixels = graphics_codec.rasterize_4bpp_grid(
                page_raw, page["tile_columns"], page["tile_rows"])
            if graphics_codec.serialize_4bpp_grid(
                    pixels, page["tile_columns"], page["tile_rows"]) != page_raw:
                raise ValueError(f"tile group {record['index']} raster round-trip differs")
            graphics_codec.write_index_png(
                output_dir / page["file"], page["tile_columns"] * 8,
                page["tile_rows"] * 8, pixels)
    manifest = {
        "status": "structured_candidate",
        "reference_sha256": ROM_SHA256,
        "descriptor_start": DESCRIPTOR_START,
        "descriptor_end": DESCRIPTOR_END,
        "descriptor_count": DESCRIPTOR_COUNT,
        "data_start": DATA_START,
        "data_end": DATA_END,
        "source_bytes": DATA_END - DATA_START,
        "tile_format_inference": "4bpp 8x8 tiles (32 bytes per tile), supported by 32-byte tile-index stride; BG display-control mode remains unverified.",
        "record_fields": "Cumulative source offset, byte length, map pointer, tile pixels, and map low-10-bit index evidence; graphics and map field semantics remain neutral.",
        "records": records,
    }
    if encode_descriptor_table(manifest) != rom[DESCRIPTOR_START:DESCRIPTOR_END]:
        raise ValueError("descriptor table does not re-encode exactly")
    if encode_tile_bank(manifest, tile_dir, graphics_codec) != rom[DATA_START:DATA_END]:
        raise ValueError("editable tile pixels do not re-encode the source bank")
    (output_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def validate_export(rom, output_dir, graphics_codec):
    import tempfile

    output_dir = Path(output_dir)
    manifest = json.loads((output_dir / "manifest.json").read_text())
    original_table = rom[DESCRIPTOR_START:DESCRIPTOR_END]
    original_data = rom[DATA_START:DATA_END]
    encoded_table = encode_descriptor_table(manifest)
    encoded_data = encode_tile_bank(manifest, output_dir / "tiles", graphics_codec)
    if encoded_table != original_table or encoded_data != original_data:
        raise ValueError("primary export does not round-trip exactly")

    transfer_checks = []
    previous_offset = 0
    for record in manifest["records"]:
        length = record["length_bytes"]
        chunk_bytes = length // 4
        word_count = length // 16
        chunks = record["transfer_chunks"]
        if (record["cumulative_source_offset"] != previous_offset or
                len(chunks) != 4 or length % 16 or word_count * 4 != chunk_bytes):
            raise ValueError(f"descriptor {record['index']} transfer arithmetic differs")
        for chunk_index, chunk in enumerate(chunks):
            expected_source = record["source_start"] + chunk_index * chunk_bytes
            expected_destination = VRAM_DESTINATION + chunk_index * chunk_bytes
            if (chunk["source_start"] != expected_source or
                    chunk["source_end_exclusive"] != expected_source + chunk_bytes or
                    chunk["destination_start"] != expected_destination or
                    chunk["destination_end_exclusive"] != expected_destination + chunk_bytes or
                    chunk["word_count_u32"] != word_count or
                    chunk["transfer_bytes"] != chunk_bytes):
                raise ValueError(f"descriptor {record['index']} chunk {chunk_index} differs")
        if (chunks[0]["source_start"] != DATA_START + previous_offset or
                chunks[-1]["source_end_exclusive"] != DATA_START + previous_offset + length or
                chunks[0]["destination_start"] != VRAM_DESTINATION or
                chunks[-1]["destination_end_exclusive"] != VRAM_DESTINATION + length):
            raise ValueError(f"descriptor {record['index']} chunks do not cover intervals")
        transfer_checks.append({
            "descriptor_index": record["index"],
            "descriptor_rom_offset": record["descriptor_rom_offset"],
            "descriptor_length_bytes": length,
            "source_interval": [record["source_start"], record["source_end_exclusive"]],
            "destination_interval_per_selected_group": [
                VRAM_DESTINATION, VRAM_DESTINATION + length],
            "chunk_bytes": chunk_bytes,
            "word_count_u32_per_chunk": word_count,
            "chunks": chunks,
            "passed": True,
        })
        previous_offset += length
    if previous_offset != DATA_END - DATA_START:
        raise ValueError("descriptor lengths do not cover the entire selected source bank")

    # A second clean export uses a separate temporary directory and a fresh parse.
    with tempfile.TemporaryDirectory(prefix="indexed-transfer-clean-",
                                     dir=str(output_dir.parent)) as temp_name:
        second_dir = Path(temp_name)
        second = export(rom, second_dir, graphics_codec)
        second_table = encode_descriptor_table(second)
        second_data = encode_tile_bank(second, second_dir / "tiles", graphics_codec)
        if second_table != encoded_table or second_data != encoded_data:
            raise ValueError("two clean export/encode runs differ")

    first_record = manifest["records"][0]
    first_page = first_record["tile_pages"][0]
    image_path = output_dir / first_page["file"]
    width, height, pixels = graphics_codec.read_index_png(image_path)
    changed_pixels = bytearray(pixels)
    changed_pixels[0] ^= 1
    negative_dir = output_dir / "validation"
    negative_dir.mkdir(exist_ok=True)
    negative_png = negative_dir / "first-pixel-bit-flip.png"
    graphics_codec.write_index_png(negative_png, width, height, changed_pixels)
    _, _, reread_pixels = graphics_codec.read_index_png(negative_png)
    mutated_page = graphics_codec.serialize_4bpp_grid(
        reread_pixels, first_page["tile_columns"], first_page["tile_rows"])
    original_page = original_data[:len(mutated_page)]
    page_diffs = [i for i, (before, after) in enumerate(zip(original_page, mutated_page))
                  if before != after]
    expected_pixel_offset = first_record["source_start"]
    if (page_diffs != [0] or
            (original_page[0] ^ mutated_page[0]) != 0x01):
        raise ValueError("single-pixel edit did not map to the expected low nibble")

    report = {
        "status": "structured_candidate",
        "reference_sha256": ROM_SHA256,
        "descriptor_table": {
            "start": DESCRIPTOR_START,
            "end_exclusive": DESCRIPTOR_END,
            "bytes": len(original_table),
            "sha256": sha256(original_table),
            "exact_roundtrip": encoded_table == original_table,
        },
        "tile_bank": {
            "start": DATA_START,
            "end_exclusive": DATA_END,
            "bytes": len(original_data),
            "tile_count": sum(r["tile_count_4bpp_8x8"] for r in manifest["records"]),
            "groups": len(manifest["records"]),
            "exact_roundtrip": encoded_data == original_data,
            "source_sha256": sha256(original_data),
        },
        "two_independent_clean_export_encodes_equal": True,
        "dma_validation": {
            "loader_call_site": "0x0812be5a",
            "callee": "0x08000adc QueueDmaCopy32",
            "calls_per_descriptor": DMA_CALLS_PER_DESCRIPTOR,
            "instruction_evidence": {
                "state_descriptor_pointer_load": "0x0812be32: ldr r2,[r6,#4]",
                "descriptor_offset_load": "0x0812be34: ldr r1,[r2]",
                "source_base_literal_add": "0x0812be36..0x0812be3a",
                "length_load_and_chunk_bytes": "0x0812be40..0x0812be44: length/4",
                "word_count": "0x0812be44..0x0812be58: length/16",
                "four_call_loop": "0x0812be50..0x0812be6c; counter initialized to 3 and loops while nonnegative",
                "source_and_destination_advance": "0x0812be5e..0x0812be66; both advance by length/4",
                "table_start_literal_rom_offset": TABLE_START_LITERAL,
                "table_start_literal_value": ROM_BASE + DESCRIPTOR_START,
                "table_end_literal_rom_offset": TABLE_END_LITERAL,
                "table_end_literal_value": ROM_BASE + DESCRIPTOR_END,
                "source_base_literal_rom_offset": SOURCE_BASE_LITERAL,
                "source_base_literal_value": ROM_BASE + DATA_START,
                "destination_literal_rom_offset": DESTINATION_LITERAL,
                "destination_literal_value": VRAM_DESTINATION,
            },
            "total_call_records_checked": sum(len(x["chunks"]) for x in transfer_checks),
            "per_descriptor": transfer_checks,
            "all_descriptor_source_ranges_contiguous": True,
            "final_source_end_exclusive": DATA_END,
        },
        "single_pixel_negative": {
            "group": 0,
            "page": 0,
            "pixel_xy": [0, 0],
            "original_index": pixels[0],
            "mutated_index": changed_pixels[0],
            "nibble": "low",
            "bit_mask": "0x01",
            "changed_serialized_byte_offsets_within_page": page_diffs,
            "changed_rom_offset": expected_pixel_offset,
            "passed": True,
        },
        "open_evidence_gates": {
            "4bpp_display_mode_hardware_register_proven": False,
            "integration_status": "structured_candidate_not_ready",
        },
    }
    (output_dir / "validation.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--graphics-codec", type=Path,
                        default=Path(__file__).resolve().parent / "indexed_graphics_codec.py",
                        help="path to tools/indexed_graphics_codec.py")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output == root or root in output.parents:
        parser.error("extracted tiles must be outside the source tree")
    codec = load_graphics_codec(args.graphics_codec)
    manifest = export(args.rom.read_bytes(), args.output_dir, codec)
    report = validate_export(args.rom.read_bytes(), args.output_dir, codec)
    print(json.dumps({"groups": len(manifest["records"]),
                      "tiles": sum(r["tile_count_4bpp_8x8"] for r in manifest["records"]),
                      "source_bytes": manifest["source_bytes"],
                      "status": manifest["status"],
                      "exact_roundtrip": report["tile_bank"]["exact_roundtrip"],
                      "transfer_chunks_checked": report["dma_validation"]["total_call_records_checked"]}))


if __name__ == "__main__":
    main()
