"""Rebuild retail map layout sources from structured payloads and LZ77 plans."""

import hashlib

from serialize_map_layout import serialize_structure


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def capture_lz77_plan(source):
    """Record the retail BIOS-LZ77 token grouping without retaining literals."""
    if len(source) < 4 or source[0] != 0x10:
        raise ValueError("map source is not BIOS LZ77")
    decoded_size = int.from_bytes(source[1:4], "little")
    cursor = 4
    decoded = bytearray()
    groups = []
    while len(decoded) < decoded_size:
        if cursor >= len(source):
            raise ValueError("map LZ77 flag group is truncated")
        flags = source[cursor]
        cursor += 1
        tokens = []
        for bit in range(7, -1, -1):
            if len(decoded) == decoded_size:
                break
            if flags & (1 << bit):
                if cursor + 2 > len(source):
                    raise ValueError("map LZ77 reference is truncated")
                first, second = source[cursor:cursor + 2]
                cursor += 2
                length = (first >> 4) + 3
                distance = ((first & 15) << 8) | second
                distance += 1
                if distance > len(decoded) or len(decoded) + length > decoded_size:
                    raise ValueError("map LZ77 reference leaves decoded payload")
                for _ in range(length):
                    decoded.append(decoded[-distance])
                tokens.append({"kind": "reference", "length": length,
                               "distance": distance})
            else:
                if cursor >= len(source):
                    raise ValueError("map LZ77 literal is truncated")
                decoded.append(source[cursor])
                cursor += 1
                tokens.append({"kind": "literal"})
        groups.append({"flags": flags, "tokens": tokens})
    if cursor != len(source):
        raise ValueError("map LZ77 source has unassigned trailing bytes")
    return bytes(decoded), groups


def encode_lz77_plan(payload, groups):
    if len(payload) >= 1 << 24:
        raise ValueError("map decoded payload exceeds BIOS LZ77 header")
    encoded = bytearray(bytes((0x10,)) + len(payload).to_bytes(3, "little"))
    position = 0
    for group_index, group in enumerate(groups):
        flags = group["flags"]
        tokens = group["tokens"]
        if not 0 <= flags <= 255 or not 1 <= len(tokens) <= 8:
            raise ValueError("map LZ77 flag group is invalid")
        encoded.append(flags)
        for index, token in enumerate(tokens):
            referenced = bool(flags & (0x80 >> index))
            if token["kind"] == "literal" and not referenced:
                if position >= len(payload):
                    raise ValueError("map LZ77 literal leaves decoded payload")
                encoded.append(payload[position])
                position += 1
            elif token["kind"] == "reference" and referenced:
                length, distance = token["length"], token["distance"]
                if (not 3 <= length <= 18 or not 1 <= distance <= 4096 or
                        distance > position or position + length > len(payload)):
                    raise ValueError("map LZ77 reference is invalid")
                for copied in range(length):
                    if payload[position + copied] != payload[position + copied - distance]:
                        raise ValueError("map LZ77 reference differs from payload")
                value = distance - 1
                encoded.extend((((length - 3) << 4) | (value >> 8), value & 255))
                position += length
            else:
                raise ValueError("map LZ77 flags and token kinds differ")
        if position == len(payload) and group_index != len(groups) - 1:
            raise ValueError("map LZ77 plan has trailing flag groups")
    if position != len(payload):
        raise ValueError("map LZ77 plan does not cover decoded payload")
    decoded, _ = capture_lz77_plan(encoded)
    if decoded != payload:
        raise ValueError("map LZ77 plan does not round-trip")
    return bytes(encoded)


def encode_map_layout_source(asset):
    """Serialize one bounded map source without reading the retail ROM."""
    payload = serialize_structure(asset["structure"])
    if len(payload) != asset["decoded_bytes"] or sha256(payload) != asset["decoded_sha256"]:
        raise ValueError(f"map layout decoded payload differs at 0x{asset['wrapper_offset']:08x}")
    kind = asset["wrapper_type"]
    if kind == 0x11:
        source = b"\x11\xff\xff\xff" + encode_lz77_plan(payload, asset["lz77_plan"])
    elif kind == 0x10:
        source = encode_lz77_plan(payload, asset["lz77_plan"])
    elif kind == 0x01:
        source = b"\x01\xff\xff\xff" + payload
    elif kind == 0x00:
        if len(payload) >= 1 << 24:
            raise ValueError("raw map palette exceeds wrapper size")
        source = b"\0" + len(payload).to_bytes(3, "little") + payload
    else:
        raise ValueError("unsupported map layout source wrapper")
    if (len(source) != asset["source_end"] - asset["wrapper_offset"] or
            sha256(source) != asset["source_sha256"]):
        raise ValueError(f"map layout source differs at 0x{asset['wrapper_offset']:08x}")
    return source


def encode_map_layout_redirect(record):
    if record["type"] not in (0x01, 0x11) or not 0 <= record["target_map"] < 162:
        raise ValueError("map layout redirect is invalid")
    source = bytes((record["type"],)) + record["target_map"].to_bytes(3, "little")
    if sha256(source) != record.get("header_sha256", record["source_sha256"]):
        raise ValueError(f"map layout redirect differs at 0x{record['offset']:08x}")
    return source


def encode_map_layout_overlay(asset):
    """Rebuild a redirect header and its complete sparse overlay source."""
    target_map = asset["target_map"]
    if type(target_map) is not int or not 0 <= target_map < 162:
        raise ValueError("map redirect target is invalid")
    payload = serialize_structure(asset["structure"])
    if len(payload) != asset["decoded_bytes"] or sha256(payload) != asset["decoded_sha256"]:
        raise ValueError(f"map redirect decoded payload differs at 0x{asset['wrapper_offset']:08x}")
    kind = asset["wrapper_type"]
    if kind == 0x11:
        encoded_payload = encode_lz77_plan(payload, asset["lz77_plan"])
    elif kind == 0x01:
        encoded_payload = payload
    else:
        raise ValueError("unsupported map redirect source wrapper")
    source = bytes((kind,)) + target_map.to_bytes(3, "little") + encoded_payload
    if (len(source) != asset["source_end"] - asset["wrapper_offset"] or
            sha256(source) != asset["source_sha256"]):
        raise ValueError(f"map redirect source differs at 0x{asset['wrapper_offset']:08x}")
    return source
