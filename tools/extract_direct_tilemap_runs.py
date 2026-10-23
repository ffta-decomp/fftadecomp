#!/usr/bin/env python3
"""Export directly copied tilemap runs as editable halfwords."""

import argparse
import hashlib
import json
from pathlib import Path

ROM_BASE = 0x08000000
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
CPU_SET = 0x0814186c
COPY_WITH_TILE_OFFSET = 0x08035578
COPIES = (
    (0x94f7dc, 192, 0x757e2, 0x758dc, 0x757f2, (0x22c0, 0x23fe)),
    (0x94f95c, 224, 0x8ba5e, 0x8bacc, 0x8ba68, (0x22e0, 0x23fe)),
    (0x94fb1c, 126, 0x7364a, 0x736f4, 0x73652, (0x227e,)),
    (0x94fc18, 126, 0x73656, 0x736f8, 0x73660, (0x227e,)),
    (0x94fd14, 288, 0x7542e, 0x7555c, 0x75438, (0x2290, 0x0052)),
    (0x94ff54, 26, 0x85bc8, 0x85c2c, 0x85bd8, (0x221a, 0x2332)),
    (0x94ff88, 30, 0x74738, 0x74758, 0x74746, (0x221e,)),
    (0x94ffc4, 30, 0x74760, 0x74788, 0x7476e, (0x330f, 0x221e)),
    (0x955250, 22, 0x3842a, 0x384d4, 0x38438, (0x2216, 0x2395)),
    (0x95527c, 30, 0x38418, 0x384cc, 0x38426, (0x221e, 0x2384)),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def halfword(rom, offset):
    return int.from_bytes(rom[offset:offset + 2], "little")


def thumb_bl_target(rom, site):
    first, second = halfword(rom, site), halfword(rom, site + 2)
    if first & 0xf800 != 0xf000 or second & 0xf800 != 0xf800:
        raise ValueError("tilemap caller no longer branches with Thumb BL")
    displacement = ((first & 0x7ff) << 12) | ((second & 0x7ff) << 1)
    if displacement & (1 << 22):
        displacement -= 1 << 23
    return ROM_BASE + site + 4 + displacement


def copy_entry(manifest, offset):
    matches = [entry for entry in manifest["copies"] if entry["start"] == offset]
    if len(matches) != 1:
        raise ValueError("tilemap copy source is not unique")
    return matches[0]


def encode_copy(manifest, offset):
    entry = copy_entry(manifest, offset)
    values = entry["halfwords"]
    if len(values) != entry["halfword_count"] or any(
            type(value) is not int or not 0 <= value <= 0xffff for value in values):
        raise ValueError("tilemap halfword count or value differs")
    encoded = b"".join(value.to_bytes(2, "little") for value in values)
    if sha256(encoded) != entry["source_sha256"]:
        raise ValueError("tilemap source differs from retail")
    return encoded


def export(rom):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    copies = []
    for start, count, load_site, literal, call_site, setup_ops in COPIES:
        load = halfword(rom, load_site)
        literal_target = ((ROM_BASE + load_site + 4) & ~3) + (load & 0xff) * 4
        callee = CPU_SET if start in (0x94fb1c, 0x94fc18, 0x94fd14) else COPY_WITH_TILE_OFFSET
        if (load & 0xf800 != 0x4800 or literal_target != ROM_BASE + literal or
                int.from_bytes(rom[literal:literal + 4], "little") != ROM_BASE + start or
                thumb_bl_target(rom, call_site) != callee):
            raise ValueError("tilemap caller or source literal differs")
        op_start = call_site - 2 * len(setup_ops)
        if tuple(halfword(rom, site) for site in range(op_start, call_site, 2)) != setup_ops:
            raise ValueError("tilemap helper call setup differs")
        data = rom[start:start + count * 2]
        copies.append({"start": start, "end": start + len(data), "halfword_count": count,
                       "literal": literal, "load_site": ROM_BASE + load_site,
                       "call_site": ROM_BASE + call_site, "callee": callee,
                       "halfwords": [halfword(data, index) for index in range(0, len(data), 2)],
                       "source_sha256": sha256(data)})
    manifest = {"reference_sha256": ROM_SHA256, "copies": copies,
                "callers": {"copy_with_tile_offset": COPY_WITH_TILE_OFFSET, "bios_cpu_set": CPU_SET},
                "caveat": "These are directly copied tilemap halfwords from UI and map callers; final composition and palette assignment remain unverified."}
    for entry in copies:
        if encode_copy(manifest, entry["start"]) != rom[entry["start"]:entry["end"]]:
            raise ValueError("tilemap export does not round-trip")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output_dir.resolve()
    if output.is_relative_to(root):
        raise SystemExit("tilemap export must be outside the source tree")
    manifest = export(args.rom.read_bytes())
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"copies": len(manifest["copies"]),
                      "source_bytes": sum(entry["end"] - entry["start"] for entry in manifest["copies"]),
                      "manifest_sha256": sha256(path.read_bytes())}))


if __name__ == "__main__":
    main()
