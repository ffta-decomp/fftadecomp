#!/usr/bin/env python3
"""Extract the retail map layout, terrain, clipping, and palette blocks.

Map records point at table-relative wrappers.  This tool resolves redirects,
decodes only the observed BIOS-LZ77/raw wrapper forms, and emits compact JSON
metadata outside the source tree.  It does not render a bitmap or claim names
for unresolved tile bits.
"""

import argparse
import bisect
import hashlib
import json
from pathlib import Path
from map_layout_source_codec import capture_lz77_plan

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
MAP_TABLE = 0x08569104 - ROM_BASE
MAP_STRIDE = 0x58
MAP_COUNT = 162
FIELDS = {"arrangement": 0x04, "clipping": 0x08, "palette": 0x0C,
          "terrain": 0x10}
SPARSE_RAM_TARGETS = {"terrain": (0x02007CB0, 0x200),
                      "clipping": (0x0200D1A0, 0x2000)}
ARRANGEMENT_RAM_BASE = 0x020091A0
ARRANGEMENT_BANK_BYTES = 0x2000
ARRANGEMENT_ROW_BYTES = 0x80


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "little")


def u24(data, offset):
    return int.from_bytes(data[offset:offset + 3], "little")


def u32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "little")


def bios_lz77(rom, offset):
    if rom[offset] != 0x10:
        raise ValueError(f"expected BIOS LZ77 at 0x{offset:x}")
    size = u24(rom, offset + 1)
    cursor = offset + 4
    output = bytearray()
    while len(output) < size:
        if cursor >= len(rom):
            raise ValueError("truncated BIOS LZ77 flags")
        flags = rom[cursor]
        cursor += 1
        for bit in range(7, -1, -1):
            if len(output) >= size:
                break
            if flags & (1 << bit):
                if cursor + 2 > len(rom):
                    raise ValueError("truncated BIOS LZ77 back-reference")
                first, second = rom[cursor], rom[cursor + 1]
                cursor += 2
                count = (first >> 4) + 3
                distance = ((first & 0x0F) << 8) | second
                start = len(output) - distance - 1
                if start < 0 or len(output) + count > size:
                    raise ValueError("invalid BIOS LZ77 back-reference")
                for _ in range(count):
                    output.append(output[start])
                    start += 1
            else:
                if cursor >= len(rom):
                    raise ValueError("truncated BIOS LZ77 literal")
                output.append(rom[cursor])
                cursor += 1
    return bytes(output), cursor - offset


def table_pointer(rom, map_id, field):
    record = MAP_TABLE + map_id * MAP_STRIDE
    return MAP_TABLE + u32(rom, record + field)


def block_info(rom, map_id, field, stack=()):
    pointer = table_pointer(rom, map_id, field)
    if map_id in stack:
        raise ValueError("map block redirect cycle")
    kind = rom[pointer]
    tag = u24(rom, pointer + 1)
    if kind in (0x01, 0x11) and tag != 0xFFFFFF:
        if tag >= MAP_COUNT:
            raise ValueError(f"map {map_id} redirect out of range: {tag}")
        resolved = block_info(rom, tag, field, stack + (map_id,))
        return {**resolved, "logical_map": map_id, "redirect_map": tag,
                "wrapper_offset": pointer, "wrapper_type": kind,
                "wrapper_bytes": rom[pointer:pointer + 4]}
    if kind == 0x11:
        payload, consumed = bios_lz77(rom, pointer + 4)
        source_end = pointer + 4 + consumed
    elif kind == 0x01:
        # The packed stream has its own zero terminator; parsers below bound
        # the useful prefix and do not assume a following block is padding.
        payload = rom[pointer + 4:pointer + 4 + 0x10000]
        source_end = None
    elif field == FIELDS["palette"] and kind == 0x10:
        payload, consumed = bios_lz77(rom, pointer)
        source_end = pointer + consumed
    elif field == FIELDS["palette"] and kind == 0x00:
        size = u24(rom, pointer + 1)
        payload = rom[pointer + 4:pointer + 4 + size]
        if len(payload) != size:
            raise ValueError("truncated raw palette")
        source_end = pointer + 4 + size
    else:
        raise ValueError(f"unsupported map {map_id} field 0x{field:x} wrapper 0x{kind:02x}")
    return {
        "logical_map": map_id, "source_map": map_id, "redirect_map": None,
        "wrapper_offset": pointer, "wrapper_type": kind,
        "wrapper_bytes": rom[pointer:pointer + 4], "payload": payload,
        "payload_sha256": sha256(payload), "payload_bytes": len(payload),
        "source_end": source_end,
    }


def parse_arrangement(payload):
    if len(payload) < 4:
        raise ValueError("short arrangement header")
    tile_format_offset = u16(payload, 0)
    flags = payload[3]
    ids_are_u16 = bool(flags & 0x40)
    cursor = 4
    runs = []
    placements = []
    serialized = bytearray(payload[:4])
    while True:
        if cursor + 2 > len(payload):
            raise ValueError("arrangement has no terminator")
        destination = u16(payload, cursor)
        if destination == 0:
            cursor += 2
            serialized.extend(payload[cursor - 2:cursor])
            break
        if cursor + 3 > len(payload):
            raise ValueError("truncated arrangement record")
        count = payload[cursor + 2]
        cursor += 3
        serialized.extend(payload[cursor - 3:cursor])
        ids = []
        for _ in range(count):
            if ids_are_u16:
                if cursor + 2 > len(payload):
                    raise ValueError("truncated 16-bit arrangement ids")
                tile_id = u16(payload, cursor)
                serialized.extend(payload[cursor:cursor + 2])
                cursor += 2
            else:
                if cursor >= len(payload):
                    raise ValueError("truncated 8-bit arrangement ids")
                tile_id = payload[cursor]
                serialized.append(tile_id)
                cursor += 1
            ids.append(tile_id)
            address = destination + len(ids[:-1]) * 4
            if address % 4 or address // 0x2000 > 1:
                raise ValueError("arrangement destination outside two layers")
            placements.append({
                "address": address, "layer": address // 0x2000,
                "x": (address % 0x80) // 4,
                "y": (address // 0x80) % 0x40, "tile_id": tile_id,
            })
        runs.append({"destination": destination, "count": count, "tile_ids": ids})
    encoded_prefix = payload[:cursor]
    if tile_format_offset > len(payload) or (len(payload) - tile_format_offset) % 2:
        raise ValueError("invalid arrangement tile-format offset")
    return {
        "tile_format_offset": tile_format_offset, "flags": flags,
        "ids_are_u16": ids_are_u16, "run_count": len(runs),
        "placement_count": len(placements), "max_tile_id": max(
            (item["tile_id"] for item in placements), default=0),
        "layer_counts": [sum(item["layer"] == layer for item in placements)
                         for layer in (0, 1)],
        "runs": runs, "roundtrip_prefix_sha256": sha256(encoded_prefix),
        "payload_prefix_bytes": cursor,
        "roundtrip_exact": bytes(serialized) == encoded_prefix,
    }


def parse_sparse_pairs(payload, kind):
    cursor = 0
    runs = []
    entry_count = 0
    serialized = bytearray()
    while True:
        if cursor + 4 > len(payload):
            raise ValueError(f"{kind} has no terminator")
        destination = u16(payload, cursor)
        byte_count = u16(payload, cursor + 2)
        serialized.extend(payload[cursor:cursor + 4])
        cursor += 4
        if destination == 0 and byte_count == 0:
            break
        if cursor + byte_count > len(payload):
            raise ValueError(f"truncated {kind} run")
        if byte_count % 2:
            raise ValueError(f"{kind} run is not halfword aligned")
        runs.append({"destination": destination, "byte_count": byte_count,
                     "data_sha256": sha256(payload[cursor:cursor + byte_count])})
        serialized.extend(payload[cursor:cursor + byte_count])
        entry_count += byte_count // 2
        cursor += byte_count
    encoded_prefix = payload[:cursor]
    return {"run_count": len(runs), "entry_count": entry_count,
            "payload_prefix_bytes": cursor,
            "roundtrip_prefix_sha256": sha256(encoded_prefix),
            "roundtrip_exact": bytes(serialized) == encoded_prefix,
            "runs": runs}


def parse_palette(info):
    payload = info["payload"]
    if len(payload) % 32:
        raise ValueError("palette payload is not whole 32-byte banks")
    return {"bank_count": len(payload) // 32, "bytes": len(payload),
            "sha256": sha256(payload)}


def map_source_boundaries(rom):
    """Find the next table-owned source after a raw arrangement wrapper."""
    boundaries = set()
    for map_id in range(MAP_COUNT):
        record = MAP_TABLE + map_id * MAP_STRIDE
        for field in (0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x18):
            relative = u32(rom, record + field)
            if relative:
                boundaries.add(MAP_TABLE + relative)
    return sorted(boundaries)


def redirect_overlay_source(rom, offset, kind, boundaries):
    """Bound the bytes consumed after a map redirect header."""
    if kind == 0x11:
        payload, consumed = bios_lz77(rom, offset + 4)
        return payload, offset + 4 + consumed
    if kind == 0x01:
        next_index = bisect.bisect_right(boundaries, offset)
        if next_index >= len(boundaries):
            raise ValueError("raw map redirect has no following table source")
        source_end = boundaries[next_index]
        return rom[offset + 4:source_end], source_end
    raise ValueError("unsupported map redirect wrapper")


def complete_source_info(rom, map_id, field, boundaries):
    info = block_info(rom, map_id, field)
    if info["redirect_map"] is not None:
        info = block_info(rom, info["source_map"], field)
    if info["source_end"] is None:
        wrapper = info["wrapper_offset"]
        next_index = bisect.bisect_right(boundaries, wrapper)
        if next_index >= len(boundaries):
            raise ValueError("raw map arrangement has no following table source")
        source_end = boundaries[next_index]
        info = {**info, "payload": rom[wrapper + 4:source_end],
                "source_end": source_end,
                "raw_boundary_method": "next_map_table_source"}
    else:
        info = {**info, "raw_boundary_method": None}
    info["payload_sha256"] = sha256(info["payload"])
    info["payload_bytes"] = len(info["payload"])
    return info


def structured_payload(name, payload):
    """Retain every decoded byte while exposing the editable observed fields."""
    if name == "arrangement":
        layout = parse_arrangement(payload)
        runs = []
        for run in layout["runs"]:
            destination = run["destination"]
            count = run["count"]
            if (destination & 3 or
                    destination + 4 * count > 2 * ARRANGEMENT_BANK_BYTES or
                    destination < ARRANGEMENT_BANK_BYTES < destination + 4 * count or
                    destination % ARRANGEMENT_ROW_BYTES + 4 * count > ARRANGEMENT_ROW_BYTES):
                raise ValueError("arrangement run crosses the observed RAM bank or row")
            runs.append({**run,
                         "ram_destination": ARRANGEMENT_RAM_BASE + destination,
                         "bank": destination // ARRANGEMENT_BANK_BYTES,
                         "row": (destination % ARRANGEMENT_BANK_BYTES) // ARRANGEMENT_ROW_BYTES,
                         "word_column": (destination % ARRANGEMENT_ROW_BYTES) // 4})
        return {
            "kind": name,
            "tile_format_offset": layout["tile_format_offset"],
            "header_byte_2": payload[2],
            "flags": layout["flags"],
            "target_ram_base": ARRANGEMENT_RAM_BASE,
            "target_bytes": 2 * ARRANGEMENT_BANK_BYTES,
            "write_unit_bytes": 4,
            "bank_bytes": ARRANGEMENT_BANK_BYTES,
            "row_bytes": ARRANGEMENT_ROW_BYTES,
            "runs": runs,
            "tail_hex": payload[layout["payload_prefix_bytes"]:].hex(),
        }
    if name in ("terrain", "clipping"):
        layout = parse_sparse_pairs(payload, name)
        ram_base, target_bytes = SPARSE_RAM_TARGETS[name]
        runs = []
        cursor = 0
        for run in layout["runs"]:
            cursor += 4
            byte_count = run["byte_count"]
            destination = run["destination"]
            if destination & 1 or destination + byte_count > target_bytes:
                raise ValueError(f"{name} sparse write exceeds observed RAM target")
            item = {"destination": destination,
                    "ram_destination": ram_base + destination,
                    "data_hex": payload[cursor:cursor + byte_count].hex()}
            if name == "clipping":
                if destination < 0x1000 < destination + byte_count:
                    raise ValueError("clipping sparse write crosses a RAM bank")
                if destination % 64 + byte_count > 64:
                    raise ValueError("clipping sparse write crosses a reader row")
                item["bank"] = destination // 0x1000
                item["row"] = (destination % 0x1000) // 64
                item["halfword_column"] = (destination % 64) // 2
            runs.append(item)
            cursor += byte_count
        return {"kind": name, "target_ram_base": ram_base,
                "target_bytes": target_bytes, "write_unit_bytes": 2,
                "runs": runs,
                "tail_hex": payload[layout["payload_prefix_bytes"]:].hex()}
    if name == "palette":
        parse_palette({"payload": payload})
        return {"kind": name,
                "banks_bgr555": [
                    [u16(payload, bank + color * 2) for color in range(16)]
                    for bank in range(0, len(payload), 32)
                ]}
    raise ValueError(f"unsupported map payload kind {name}")


def export_payloads(rom, output):
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("Map payload export must be outside the source tree")
    boundaries = map_source_boundaries(rom)
    assets = {}
    maps = []
    redirects = {}
    overlays = {}
    for map_id in range(MAP_COUNT):
        row = {"map": map_id}
        for name, field in FIELDS.items():
            logical = block_info(rom, map_id, field)
            source = complete_source_info(rom, map_id, field, boundaries)
            wrapper = source["wrapper_offset"]
            asset_name = f"{name}-{wrapper:06x}.json"
            if asset_name not in assets:
                payload = source["payload"]
                structure = structured_payload(name, payload)
                asset = {
                    "reference_sha256": ROM_SHA256,
                    "source_map": source["source_map"],
                    "wrapper_offset": wrapper,
                    "wrapper_type": source["wrapper_type"],
                    "wrapper_hex": source["wrapper_bytes"].hex(),
                    "source_end": source["source_end"],
                    "raw_boundary_method": source["raw_boundary_method"],
                    "source_sha256": sha256(rom[wrapper:source["source_end"]]),
                    "decoded_bytes": len(payload),
                    "decoded_sha256": sha256(payload),
                    "structure": structure,
                }
                if source["wrapper_type"] in (0x10, 0x11):
                    compressed = rom[wrapper + (4 if source["wrapper_type"] == 0x11 else 0):
                                     source["source_end"]]
                    decoded, asset["lz77_plan"] = capture_lz77_plan(compressed)
                    if decoded != payload:
                        raise ValueError("map LZ77 plan differs from decoded payload")
                assets[asset_name] = asset
            row[name] = {"asset": asset_name,
                         "redirect_map": logical["redirect_map"],
                         "source_map": source["source_map"]}
            if logical["redirect_map"] is not None:
                redirect = table_pointer(rom, map_id, field)
                overlay_name = f"overlay-{redirect:06x}.json"
                overlay_payload, overlay_end = redirect_overlay_source(
                    rom, redirect, logical["wrapper_type"], boundaries)
                overlay = {
                    "reference_sha256": ROM_SHA256,
                    "wrapper_offset": redirect,
                    "source_end": overlay_end,
                    "wrapper_type": logical["wrapper_type"],
                    "target_map": logical["redirect_map"],
                    "field": name,
                    "source_sha256": sha256(rom[redirect:overlay_end]),
                    "decoded_bytes": len(overlay_payload),
                    "decoded_sha256": sha256(overlay_payload),
                    "structure": structured_payload(name, overlay_payload),
                }
                if logical["wrapper_type"] == 0x11:
                    encoded = rom[redirect + 4:overlay_end]
                    decoded, overlay["lz77_plan"] = capture_lz77_plan(encoded)
                    if decoded != overlay_payload:
                        raise ValueError("map redirect LZ77 plan differs from payload")
                if overlay_name in overlays and overlays[overlay_name] != overlay:
                    raise ValueError("shared map redirect overlay differs")
                overlays[overlay_name] = overlay
                record = {"offset": redirect, "type": logical["wrapper_type"],
                          "target_map": logical["redirect_map"],
                          "field": name, "overlay_asset": overlay_name,
                          "source_end": overlay_end,
                          "header_sha256": sha256(rom[redirect:redirect + 4]),
                          "source_sha256": sha256(rom[redirect:overlay_end])}
                if redirect in redirects and redirects[redirect] != record:
                    raise ValueError("shared map redirect differs")
                redirects[redirect] = record
        maps.append(row)
    output.mkdir(parents=True, exist_ok=True)
    for name, asset in sorted(assets.items()):
        (output / name).write_text(json.dumps(asset, indent=2) + "\n")
    for name, overlay in sorted(overlays.items()):
        (output / name).write_text(json.dumps(overlay, indent=2) + "\n")
    spans = sorted({(offset, record["source_end"])
                    for offset, record in redirects.items()} | {
        (asset["wrapper_offset"], asset["source_end"])
        for asset in assets.values()
    })
    union = []
    for start, end in spans:
        if union and start <= union[-1][1]:
            union[-1] = (union[-1][0], max(union[-1][1], end))
        else:
            union.append((start, end))
    manifest = {"reference_sha256": ROM_SHA256,
                "map_table_file_offset": MAP_TABLE,
                "map_count": MAP_COUNT,
                "asset_count": len(assets),
                "overlay_count": len(overlays),
                "overlay_source_bytes": sum(record["source_end"] - offset
                                            for offset, record in redirects.items()),
                "source_span_union_bytes": sum(end - start for start, end in union),
                "redirect_wrapper_count": len(redirects),
                "redirect_wrappers": [redirects[offset] for offset in sorted(redirects)],
                "maps": maps,
                "source_encoder_status": "Retail BIOS-LZ77 token plans are exported for exact source re-encoding."}
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--export-dir", type=Path)
    args = parser.parse_args()
    output = args.output.resolve()
    root = Path(__file__).resolve().parents[1]
    if output.is_relative_to(root):
        raise SystemExit("Map layout output must be outside the source tree")
    rom = args.rom.read_bytes()
    if sha256(rom) != ROM_SHA256:
        raise SystemExit("Input is not the pinned US retail ROM")

    if args.export_dir is not None:
        export_payloads(rom, args.export_dir.resolve())

    maps = []
    all_spans = []
    boundaries = map_source_boundaries(rom)
    for map_id in range(MAP_COUNT):
        row = {"map": map_id}
        record = MAP_TABLE + map_id * MAP_STRIDE
        row["render_modes"] = [rom[record + 0x54], rom[record + 0x55]]
        row["shared_palette_index"] = rom[record + 0x56]
        row["reserved_byte"] = rom[record + 0x57]
        for name, field in FIELDS.items():
            info = block_info(rom, map_id, field)
            if info["source_end"] is None:
                completed = complete_source_info(rom, map_id, field, boundaries)
                info = {**info, "payload": completed["payload"],
                        "payload_bytes": completed["payload_bytes"],
                        "payload_sha256": completed["payload_sha256"],
                        "source_end": completed["source_end"],
                        "raw_boundary_method": completed["raw_boundary_method"]}
            item = {key: value for key, value in info.items()
                    if key not in ("payload", "wrapper_bytes")}
            item["wrapper_type"] = info["wrapper_type"]
            if name == "arrangement":
                item["layout"] = parse_arrangement(info["payload"])
            elif name in ("terrain", "clipping"):
                item["layout"] = parse_sparse_pairs(info["payload"], name)
            elif name == "palette":
                item["layout"] = parse_palette(info)
            if info["redirect_map"] is not None:
                overlay_payload, overlay_end = redirect_overlay_source(
                    rom, info["wrapper_offset"], info["wrapper_type"], boundaries)
                item["overlay_source_end"] = overlay_end
                item["overlay_decoded_bytes"] = len(overlay_payload)
                all_spans.append((info["wrapper_offset"], overlay_end))
            elif item["source_end"] is not None:
                all_spans.append((info["wrapper_offset"], item["source_end"]))
            row[name] = item
        maps.append(row)

    all_spans.sort()
    union = []
    for start, end in all_spans:
        if end is None:
            continue
        if union and start <= union[-1][1]:
            union[-1] = (union[-1][0], max(union[-1][1], end))
        else:
            union.append((start, end))
    report = {
        "reference_sha256": ROM_SHA256,
        "map_table_rom_offset": MAP_TABLE, "map_stride": MAP_STRIDE,
        "map_count": MAP_COUNT,
        "table_bytes": MAP_STRIDE * MAP_COUNT,
        "arrangement_placements": sum(m["arrangement"]["layout"]["placement_count"] for m in maps),
        "arrangement_runs": sum(m["arrangement"]["layout"]["run_count"] for m in maps),
        "terrain_entries": sum(m["terrain"]["layout"]["entry_count"] for m in maps),
        "clipping_entries": sum(m["clipping"]["layout"]["entry_count"] for m in maps),
        "palette_banks": sum(m["palette"]["layout"]["bank_count"] for m in maps),
        "source_span_union_bytes": sum(end - start for start, end in union),
        "source_spans": [{"start": start, "end": end, "bytes": end - start}
                         for start, end in union],
        "maps": maps,
        "caveat": "Layout IDs and palette banks are structurally decoded. Tile flip bits, palette-bit semantics, and rendered bitmap arrangement remain unassigned where no consumer trace proves them.",
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in (
        "map_count", "arrangement_placements", "terrain_entries",
        "clipping_entries", "palette_banks", "source_span_union_bytes")}))


if __name__ == "__main__":
    main()
