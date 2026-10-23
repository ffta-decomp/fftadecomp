#!/usr/bin/env python3
"""Export three pointer-backed BIOS-LZ77 VRAM graphics streams."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_map_layout import bios_lz77
from map_layout_source_codec import capture_lz77_plan, encode_lz77_plan

ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
STREAMS = (
    (0x951588, 0x384d8, 0x0803843c, 0x08038442, "4bpp_tiles"),
    (0x9542a0, 0x384e0, 0x0803845a, 0x08038462, "u16_tilemap"),
    (0x954b4c, 0x384e4, 0x08038478, 0x08038480, "u16_tilemap"),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def thumb_bl_target(rom, site):
    first = int.from_bytes(rom[site:site + 2], "little")
    second = int.from_bytes(rom[site + 2:site + 4], "little")
    if first & 0xf800 != 0xf000 or second & 0xf800 != 0xf800:
        raise ValueError("VRAM graphics caller does not make a Thumb BL")
    displacement = ((first & 0x7ff) << 12) | ((second & 0x7ff) << 1)
    if displacement & (1 << 22):
        displacement -= 1 << 23
    return ROM_BASE + site + 4 + displacement


def export_streams(rom, output):
    decoded_dir = output / "decoded"
    decoded_dir.mkdir(parents=True, exist_ok=True)
    entries = []
    for offset, pointer_site, call_site, bios_call_site, format_name in STREAMS:
        if int.from_bytes(rom[pointer_site:pointer_site + 4], "little") != ROM_BASE + offset:
            raise ValueError("VRAM graphics literal no longer points at stream")
        instruction = int.from_bytes(rom[call_site - ROM_BASE:call_site - ROM_BASE + 2], "little")
        literal_address = ((call_site + 4) & ~3) + (instruction & 0xff) * 4
        if (instruction & 0xff00 != 0x4800 or literal_address != ROM_BASE + pointer_site or
                thumb_bl_target(rom, bios_call_site - ROM_BASE) != 0x0814188c):
            raise ValueError("VRAM graphics caller no longer loads the observed BIOS source")
        declared_size = int.from_bytes(rom[offset + 1:offset + 4], "little")
        if rom[offset] != 0x10:
            raise ValueError("VRAM graphics stream is not BIOS LZ77")
        decoded, consumed = bios_lz77(rom, offset)
        decoded_again, plan = capture_lz77_plan(rom[offset:offset + consumed])
        if decoded_again != decoded:
            raise ValueError("VRAM graphics LZ77 plan differs from decode")
        if len(decoded) != declared_size or len(decoded) % 32:
            raise ValueError("VRAM graphics decode does not fit whole tile units")
        encoded = encode_lz77_plan(decoded, plan)
        if encoded != rom[offset:offset + consumed]:
            raise ValueError("VRAM graphics token plan does not match retail")
        name = f"vram-0x{offset:06x}.4bpp" if format_name == "4bpp_tiles" else f"vram-0x{offset:06x}.json"
        if format_name == "4bpp_tiles":
            (decoded_dir / name).write_bytes(decoded)
            unit_count = len(decoded) // 32
        else:
            values = [int.from_bytes(decoded[index:index + 2], "little")
                      for index in range(0, len(decoded), 2)]
            (decoded_dir / name).write_text(json.dumps({"halfwords": values}, indent=2) + "\n")
            unit_count = len(values)
        entries.append({"rom_offset": offset, "pointer_site": pointer_site,
                        "call_site": call_site, "bios_call_site": bios_call_site,
                        "bios_callee": 0x0814188c,
                        "format": format_name, "file": name,
                        "unit_count": unit_count, "decoded_bytes": len(decoded),
                        "encoded_bytes": consumed, "decoded_sha256": sha256(decoded),
                        "encoded_sha256": sha256(encoded), "token_plan": plan})
    return {"reference_sha256": ROM_SHA256, "stream_count": len(entries),
            "entries": entries,
            "evidence": "Literal loads at each call site feed BIOS SVC 0x12 through 0x0814188c; exact scene placement and palette assignments remain unproven."}


def stream_entry(manifest, offset):
    matches = [entry for entry in manifest["entries"] if entry["rom_offset"] == offset]
    if len(matches) != 1:
        raise ValueError(f"VRAM graphics stream 0x{offset:08x} is not unique")
    return matches[0]


def reconstruct_stream(manifest, source_dir, offset):
    entry = stream_entry(manifest, offset)
    file_path = source_dir / "decoded" / entry["file"]
    if entry["format"] == "4bpp_tiles":
        if entry["file"] != f"vram-0x{offset:06x}.4bpp":
            raise ValueError("VRAM graphics tile filename differs")
        decoded = file_path.read_bytes()
        if len(decoded) // 32 != entry["unit_count"]:
            raise ValueError("VRAM graphics tile count differs")
    elif entry["format"] == "u16_tilemap":
        if entry["file"] != f"vram-0x{offset:06x}.json":
            raise ValueError("VRAM graphics tilemap filename differs")
        values = json.loads(file_path.read_text())["halfwords"]
        if len(values) != entry["unit_count"] or any(
                type(value) is not int or not 0 <= value <= 0xffff for value in values):
            raise ValueError("VRAM graphics tilemap halfwords differ")
        decoded = b"".join(value.to_bytes(2, "little") for value in values)
    else:
        raise ValueError("unknown VRAM graphics decoded format")
    if len(decoded) != entry["decoded_bytes"] or sha256(decoded) != entry["decoded_sha256"]:
        raise ValueError(f"VRAM graphics decode differs at 0x{offset:08x}")
    encoded = encode_lz77_plan(decoded, entry["token_plan"])
    if len(encoded) != entry["encoded_bytes"] or sha256(encoded) != entry["encoded_sha256"]:
        raise ValueError(f"VRAM graphics source differs at 0x{offset:08x}")
    return encoded


def export(rom, output):
    root = Path(__file__).resolve().parents[1]
    output = output.resolve()
    if output.is_relative_to(root):
        raise ValueError("VRAM graphics export must be outside the source tree")
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    manifest = export_streams(rom, output)
    for entry in manifest["entries"]:
        rebuilt = reconstruct_stream(manifest, output, entry["rom_offset"])
        if rebuilt != rom[entry["rom_offset"]:entry["rom_offset"] + entry["encoded_bytes"]]:
            raise ValueError("VRAM graphics stream does not round-trip")
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    manifest = export(args.rom.read_bytes(), args.output_dir)
    print(json.dumps({"stream_count": len(manifest["entries"]),
                      "source_bytes": sum(entry["encoded_bytes"] for entry in manifest["entries"])}))


if __name__ == "__main__":
    main()
