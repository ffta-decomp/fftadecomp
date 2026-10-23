#!/usr/bin/env python3
"""Export pointer-backed custom-LZSS streams used by ROM decoder calls."""

import argparse
import hashlib
import json
from pathlib import Path

from extract_map_graphics import decode_lzss, encode_lzss_plan


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
DECODER_ENTRY = 0x0800543c
STREAM_STARTS = (
    0x3ad154, 0x3ad5f8, 0x3adb08, 0x3ae194, 0x3aec28, 0x3aeea4,
    0x3af504, 0x3af710, 0x3af8ac, 0x3afa70, 0x3b4214, 0x3b53a4,
    0x3bb7f0, 0x3bba38, 0x3bbc7c, 0x3bc6cc, 0x3be1f4, 0x3c11bc,
    0x3c2fe0, 0x3c3454, 0x3c3954, 0x3c4888, 0x3c4c14, 0x3c5024,
    0x3c52a8, 0x3c5c6c, 0x418f14,
)
EXPECTED_ENCODED_BYTES = 55225


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def u16(data, position):
    return int.from_bytes(data[position:position + 2], "little")


def thumb_bl_target(rom, position):
    first, second = u16(rom, position), u16(rom, position + 2)
    if first & 0xf800 != 0xf000 or second & 0xf800 != 0xf800:
        return None
    displacement = ((first & 0x7ff) << 12) | ((second & 0x7ff) << 1)
    if displacement & 0x400000:
        displacement -= 0x800000
    return ROM_BASE + position + 4 + displacement


def decoder_calls_for_literal(rom, literal_site):
    calls = []
    for load_pc in range(max(0, literal_site - 256), literal_site - 2, 2):
        instruction = u16(rom, load_pc)
        if (instruction & 0xf800 != 0x4800 or
                ((load_pc + 4) & ~3) + ((instruction & 255) << 2) != literal_site):
            continue
        # All observed direct calls follow the literal load immediately or
        # after one two-byte instruction. A wider window conflates later calls.
        for call_pc in (load_pc + 2, load_pc + 4):
            if thumb_bl_target(rom, call_pc) == DECODER_ENTRY:
                calls.append({"literal_site": literal_site, "load_pc": load_pc,
                              "call_pc": call_pc})
    return calls


def encode_stream(entry, source_dir):
    data = (source_dir / entry["file"]).read_bytes()
    if len(data) != entry["decoded_bytes"] or sha256(data) != entry["decoded_sha256"]:
        raise ValueError("custom-LZSS decoded asset differs")
    encoded = encode_lzss_plan(data, entry["token_plan"])
    if len(encoded) != entry["encoded_bytes"] or sha256(encoded) != entry["encoded_sha256"]:
        raise ValueError("custom-LZSS encoded stream differs from retail")
    return encoded


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("custom-LZSS output must be outside the source tree")
    output.mkdir(parents=True, exist_ok=True)
    decoded_dir = output / "decoded"
    decoded_dir.mkdir(exist_ok=True)
    pointer_sites = {start: [] for start in STREAM_STARTS}
    for site in range(0, len(rom) - 3, 4):
        target = int.from_bytes(rom[site:site + 4], "little") - ROM_BASE
        if target in pointer_sites:
            pointer_sites[target].append(site)
    entries = []
    for start in STREAM_STARTS:
        data, consumed, plan = decode_lzss(rom, start, capture_plan=True)
        if not data or len(data) % 32 or consumed < 8:
            raise ValueError("custom-LZSS output does not align to GBA tiles")
        encoded = rom[start:start + consumed]
        if encode_lzss_plan(data, plan) != encoded:
            raise ValueError("custom-LZSS stream does not round-trip")
        calls = [call for site in pointer_sites[start]
                 for call in decoder_calls_for_literal(rom, site)]
        if not calls:
            raise ValueError("custom-LZSS stream lacks a direct decoder caller")
        name = f"stream-0x{start:06x}.bin"
        (decoded_dir / name).write_bytes(data)
        entry = {"start": start, "end": start + consumed,
                 "encoded_bytes": consumed, "decoded_bytes": len(data),
                 "encoded_sha256": sha256(encoded), "decoded_sha256": sha256(data),
                 "pointer_sites": pointer_sites[start], "decoder_calls": calls,
                 "token_plan": plan, "file": f"decoded/{name}"}
        entries.append(entry)
        if encode_stream(entry, output) != encoded:
            raise ValueError("custom-LZSS export does not re-encode")
    if len(entries) != 27 or sum(entry["encoded_bytes"] for entry in entries) != EXPECTED_ENCODED_BYTES:
        raise ValueError("custom-LZSS stream inventory differs")
    if any(left["end"] > right["start"] for left, right in zip(entries, entries[1:])):
        raise ValueError("custom-LZSS stream ranges overlap")
    manifest = {"reference_sha256": ROM_SHA256, "decoder_entry": DECODER_ENTRY,
                "stream_count": len(entries), "encoded_bytes": EXPECTED_ENCODED_BYTES,
                "decoded_bytes": sum(entry["decoded_bytes"] for entry in entries),
                "entries": entries,
                "scope_note": "Each stream has a direct retail decoder call and tile-aligned output. Final visual placement is not established."}
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"streams": len(entries), "encoded_bytes": EXPECTED_ENCODED_BYTES,
            "decoded_bytes": manifest["decoded_bytes"],
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
