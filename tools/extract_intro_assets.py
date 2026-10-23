#!/usr/bin/env python3
"""Extract intro/attract assets observed at the retail custom-LZSS entry.

The input is a machine-readable mGBA call trace produced with a fixed clean
save state.  This keeps the runtime evidence separate from the ROM-derived
asset files and prevents guessing a title asset from a tile heuristic alone.
"""

import argparse
import hashlib
import json
import struct
from pathlib import Path

from extract_map_graphics import decode_lzss, encode_lzss_plan

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
CUSTOM_LZSS_ENTRY = 0x0800543C
PALETTE_BUFFER = 0x03003864


def digest(data):
    return hashlib.sha256(data).hexdigest()


def pointer_sites(rom, value):
    needle = struct.pack("<I", value)
    return [offset for offset in range(0, len(rom) - 3, 4)
            if rom[offset:offset + 4] == needle]


def export(rom, trace, palette_trace, output):
    output = output.resolve()
    root = Path(__file__).resolve().parents[1]
    if output.is_relative_to(root):
        raise ValueError("intro resource output must be outside the source tree")
    if digest(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    calls = []
    for line in trace.read_text().splitlines():
        if not line.strip():
            continue
        row = json.loads(line)
        if row.get("entry") == CUSTOM_LZSS_ENTRY:
            calls.append(row)
    if not calls:
        raise SystemExit("Trace contains no calls to the custom LZSS entry")

    assets = {}
    for call in calls:
        source = call["r"][1]
        if not ROM_BASE <= source < ROM_BASE + len(rom):
            raise SystemExit(f"Trace source is outside ROM: 0x{source:08x}")
        if source not in assets:
            offset = source - ROM_BASE
            raw, consumed, token_plan = decode_lzss(rom, offset, capture_plan=True)
            if encode_lzss_plan(raw, token_plan) != rom[offset:offset + consumed]:
                raise ValueError("intro LZSS plan does not rebuild retail stream")
            assets[source] = {"source_address": source, "rom_offset": offset,
                              "decoded_bytes": len(raw), "consumed_bytes": consumed,
                              "decoded_sha256": digest(raw),
                              "retail_stream_sha256": digest(rom[offset:offset + consumed]),
                              "token_plan": token_plan,
                              "pointer_sites": pointer_sites(rom, source),
                              "raw": raw, "calls": []}
        assets[source]["calls"].append({
            "index": call["index"], "entry_frame": call["entry_frame"],
            "exit_frame": call["exit_frame"], "destination": call["r"][0],
            "argument2": call["r"][2], "argument3": call["r"][3],
            "decoded_return": call["return_r0"]})

    graphics_dir = output / "decoded"
    graphics_dir.mkdir(parents=True, exist_ok=True)
    manifest_assets = []
    for asset in sorted(assets.values(), key=lambda item: item["rom_offset"]):
        file_name = f"intro-0x{asset['rom_offset']:06x}.bin"
        asset["file"] = file_name
        graphics_dir.joinpath(file_name).write_bytes(asset["raw"])
        manifest_assets.append({key: value for key, value in asset.items()
                                if key != "raw"})

    report = {
        "reference_sha256": ROM_SHA256,
        "trace_sha256": digest(trace.read_bytes()),
        "custom_lzss_entry": CUSTOM_LZSS_ENTRY,
        "call_count": len(calls),
        "unique_stream_count": len(manifest_assets),
        "decoded_bytes": sum(item["decoded_bytes"] for item in manifest_assets),
        "assets": manifest_assets,
        "palette_status": "not supplied; decoded tile bytes are not a palette",
        "audio_status": "No audio byte is inferred from graphics calls; the separate catalog_audio.py scan records the retail song-table reference.",
        "boundary": "Only streams actually passed to the custom decoder in the fixed trace are included. This does not claim complete title or attract-mode coverage.",
    }
    if palette_trace:
        palette_events = []
        for line in palette_trace.read_text().splitlines():
            if not line.strip():
                continue
            event = json.loads(line)
            if event.get("address") != PALETTE_BUFFER:
                continue
            registers = event.get("r", [])
            if len(registers) < 3:
                continue
            source, byte_count = registers[1], registers[2]
            # The fixed probe also observes animation fade writes to the same
            # IWRAM byte.  They do not carry a ROM source/count ABI, so keep
            # only bounded copies whose source and extent are inside ROM.
            if not (ROM_BASE <= source < ROM_BASE + len(rom)
                    and 0 < byte_count <= 0x400
                    and source + byte_count <= ROM_BASE + len(rom)):
                continue
            row = {
                "frame": event.get("frame"), "pc": event.get("pc"),
                "source_address": source, "byte_count": byte_count,
                "destination_address": PALETTE_BUFFER,
            }
            source_offset = source - ROM_BASE
            palette = rom[source_offset:source_offset + byte_count]
            row.update({
                "source_rom_offset": source_offset,
                "source_sha256": digest(palette),
                "colors_bgr555": [int.from_bytes(palette[index:index + 2], "little")
                                  for index in range(0, len(palette), 2)],
            })
            palette_events.append(row)
        report["palette_trace_sha256"] = digest(palette_trace.read_bytes())
        report["palette_buffer_address"] = PALETTE_BUFFER
        report["palette_events"] = palette_events
        report["palette_status"] = (
            "Observed writes to an IWRAM palette buffer; ROM source bytes are "
            "recorded when the trace supplies a ROM source pointer. This is "
            "not a complete title/attract palette inventory.")
    output.joinpath("manifest.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--trace", required=True, type=Path)
    parser.add_argument(
        "--palette-trace", type=Path,
        help="Optional JSONL memory-write trace for the observed palette buffer.")
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    report = export(args.rom.read_bytes(), args.trace, args.palette_trace,
                    args.output_dir)
    print(json.dumps({key: report[key] for key in (
        "call_count", "unique_stream_count", "decoded_bytes")}))


def intro_stream_entry(manifest, offset):
    matches = [asset for asset in manifest["assets"] if asset["rom_offset"] == offset]
    if len(matches) != 1:
        raise ValueError(f"intro stream 0x{offset:08x} is not unique")
    return matches[0]


def reconstruct_intro_stream(manifest, source_dir, offset):
    asset = intro_stream_entry(manifest, offset)
    file_name = f"intro-0x{offset:06x}.bin"
    if asset["file"] != file_name:
        raise ValueError("intro decoded filename differs from source offset")
    raw = (source_dir / "decoded" / file_name).read_bytes()
    if len(raw) != asset["decoded_bytes"] or digest(raw) != asset["decoded_sha256"]:
        raise ValueError(f"intro decoded bytes differ at 0x{offset:08x}")
    encoded = encode_lzss_plan(raw, asset["token_plan"])
    if (len(encoded) != asset["consumed_bytes"] or
            digest(encoded) != asset["retail_stream_sha256"]):
        raise ValueError(f"intro encoded stream differs at 0x{offset:08x}")
    return encoded


def reconstruct_intro_palette(manifest, offset):
    matches = [event for event in manifest.get("palette_events", [])
               if event["source_rom_offset"] == offset]
    if len(matches) != 1:
        raise ValueError(f"intro palette 0x{offset:08x} is not unique")
    event = matches[0]
    colors = event["colors_bgr555"]
    if len(colors) * 2 != event["byte_count"] or any(
            type(color) is not int or not 0 <= color <= 0xffff for color in colors):
        raise ValueError("intro palette has invalid BGR555 colors")
    encoded = b"".join(color.to_bytes(2, "little") for color in colors)
    if digest(encoded) != event["source_sha256"]:
        raise ValueError(f"intro palette differs at 0x{offset:08x}")
    return encoded


if __name__ == "__main__":
    main()
