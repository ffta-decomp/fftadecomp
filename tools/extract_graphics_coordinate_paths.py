#!/usr/bin/env python3
"""Export the pointer-indexed signed coordinate paths used by graphics code."""

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE = 0x08000000
POINTS_START = 0x392098
DIRECTORY_START = 0x3931B0
DIRECTORY_END = 0x393318
PATH_COUNT = 45
DIRECTORY_LITERALS = (0x30160, 0x4BD48, 0x4BD74)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def validate_manifest(manifest):
    if (manifest["reference_sha256"] != ROM_SHA256 or
            manifest["points_start"] != POINTS_START or
            manifest["points_end"] != DIRECTORY_START or
            manifest["directory_start"] != DIRECTORY_START or
            manifest["directory_end"] != DIRECTORY_END or
            len(manifest["paths"]) != PATH_COUNT):
        raise ValueError("coordinate path revision, boundary, or count differs")


def encode_points(manifest, verify_hash=True):
    validate_manifest(manifest)
    output = bytearray()
    cursor = POINTS_START
    for index, path in enumerate(manifest["paths"]):
        points = path["points"]
        if (path["index"] != index or path["start"] != cursor or
                path["point_count"] != len(points) or not 1 <= len(points) <= 255 or
                path["end"] != cursor + 2 * len(points)):
            raise ValueError("coordinate path count or boundary differs")
        encoded = bytearray()
        for point in points:
            if (set(point) != {"x", "y"} or
                    any(type(point[axis]) is not int or not -128 <= point[axis] <= 127
                        for axis in ("x", "y"))):
                raise ValueError("coordinate path point is not a signed byte pair")
            encoded += struct.pack("<bb", point["x"], point["y"])
        if verify_hash and sha256(encoded) != path["source_sha256"]:
            raise ValueError(f"coordinate path {index} differs from retail")
        output += encoded
        cursor = path["end"]
    if cursor != DIRECTORY_START or (verify_hash and
            sha256(output) != manifest["points_sha256"]):
        raise ValueError("coordinate point bank differs from retail")
    return bytes(output)


def encode_directory(manifest, verify_hash=True):
    validate_manifest(manifest)
    cursor = POINTS_START
    output = bytearray()
    for index, path in enumerate(manifest["paths"]):
        if (path["index"] != index or path["start"] != cursor or
                path["point_count"] != len(path["points"])):
            raise ValueError("coordinate directory and point bank disagree")
        output += struct.pack("<II", path["point_count"], ROM_BASE + cursor)
        cursor += 2 * path["point_count"]
    if (cursor != DIRECTORY_START or len(output) != DIRECTORY_END - DIRECTORY_START or
            (verify_hash and sha256(output) != manifest["directory_sha256"])):
        raise ValueError("coordinate path directory differs from retail")
    return bytes(output)


def export(rom, output):
    if sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    output = output.resolve()
    if output.is_relative_to(Path(__file__).resolve().parents[1]):
        raise ValueError("coordinate path output must be outside the source tree")
    if any(struct.unpack_from("<I", rom, site)[0] != ROM_BASE + DIRECTORY_START
           for site in DIRECTORY_LITERALS):
        raise ValueError("coordinate directory caller literal differs")
    if DIRECTORY_END - DIRECTORY_START != 8 * PATH_COUNT:
        raise ValueError("coordinate directory size differs")
    paths = []
    cursor = POINTS_START
    for index in range(PATH_COUNT):
        directory_offset = DIRECTORY_START + 8 * index
        count, pointer = struct.unpack_from("<II", rom, directory_offset)
        if (not 1 <= count <= 255 or pointer != ROM_BASE + cursor or
                cursor + 2 * count > DIRECTORY_START):
            raise ValueError(f"coordinate path {index} escapes its ordered bank")
        data = rom[cursor:cursor + 2 * count]
        points = [{"x": x, "y": y} for x, y in struct.iter_unpack("<bb", data)]
        paths.append({"index": index, "start": cursor,
                      "end": cursor + len(data), "point_count": count,
                      "source_sha256": sha256(data), "points": points})
        cursor += len(data)
    if cursor != DIRECTORY_START:
        raise ValueError("coordinate paths do not fill the bank")
    manifest = {"reference_sha256": ROM_SHA256,
                "points_start": POINTS_START, "points_end": DIRECTORY_START,
                "directory_start": DIRECTORY_START, "directory_end": DIRECTORY_END,
                "directory_literal_sites": list(DIRECTORY_LITERALS),
                "path_count": PATH_COUNT,
                "point_count": sum(path["point_count"] for path in paths),
                "points_sha256": sha256(rom[POINTS_START:DIRECTORY_START]),
                "directory_sha256": sha256(rom[DIRECTORY_START:DIRECTORY_END]),
                "paths": paths,
                "scope_note": "Retail reads the directory count and signed x/y bytes. The paths' on-screen object assignment and timing remain unknown."}
    if (encode_points(manifest) != rom[POINTS_START:DIRECTORY_START] or
            encode_directory(manifest) != rom[DIRECTORY_START:DIRECTORY_END]):
        raise ValueError("coordinate paths do not round-trip")
    output.mkdir(parents=True, exist_ok=True)
    path = output / "manifest.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n")
    return {"paths": PATH_COUNT, "points": manifest["point_count"],
            "source_bytes": DIRECTORY_END - POINTS_START,
            "manifest_sha256": sha256(path.read_bytes())}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(export(args.rom.read_bytes(), args.output_dir)))


if __name__ == "__main__":
    main()
