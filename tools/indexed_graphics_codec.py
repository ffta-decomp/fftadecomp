"""Shared reader for the observed FFTA A7 indexed graphics archives."""

import hashlib
import struct
import zlib


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def be16(data, offset):
    return int.from_bytes(data[offset:offset + 2], "big")


def be32(data, offset):
    return int.from_bytes(data[offset:offset + 4], "big")


def parse_archive(rom, base):
    if base + 8 > len(rom) or rom[base:base + 2] != bytes.fromhex("4137"):
        raise ValueError("indexed graphics archive header is not the observed A7 form")
    declared_count = be16(rom, base + 2)
    table_offset = be32(rom, base + 4)
    table = base + table_offset
    if table + 4 > len(rom):
        raise ValueError("indexed graphics dictionary table is outside the ROM")
    mode, bit_width = rom[table], rom[table + 1]
    if mode > 2 or bit_width == 0 or bit_width > 7:
        raise ValueError("unsupported indexed graphics dictionary mode")
    decoded_bytes = be16(rom, table + 2)
    dictionary_base = 4 if mode <= 2 else 2
    mask = 0xffff >> (bit_width + 1)
    dictionary_max_end = table + dictionary_base

    offsets = []
    cursor = base + 8
    while cursor + 4 <= table:
        entry_offset = be32(rom, cursor)
        if not (0 < entry_offset < table_offset):
            break
        if offsets and entry_offset <= offsets[-1]:
            raise ValueError("indexed graphics archive entry offsets are not increasing")
        offsets.append(entry_offset)
        cursor += 4
    if len(offsets) != declared_count or offsets[0] != 8 + declared_count * 4:
        raise ValueError("indexed graphics archive offset table does not match its header")

    def decode_entry(index):
        nonlocal dictionary_max_end
        stream = base + offsets[index]
        output = bytearray()
        while len(output) < decoded_bytes:
            if stream >= table:
                raise ValueError(f"indexed graphics entry {index} exceeds its archive span")
            command = rom[stream]
            stream += 1
            if command & 0x80:
                count = (command & 0x7f) + 1
                if stream + count > table:
                    raise ValueError(f"indexed graphics entry {index} literal exceeds archive")
                output.extend(rom[stream:stream + count])
                stream += count
            else:
                if stream >= table:
                    raise ValueError(f"indexed graphics entry {index} back-reference is truncated")
                count = ((command << 1) >> (8 - bit_width)) + 3
                dictionary_offset = ((command << 8) | rom[stream]) & mask
                stream += 1
                start = table + dictionary_base + dictionary_offset
                end = start + count
                if end > len(rom):
                    raise ValueError(f"indexed graphics entry {index} dictionary reference is out of ROM")
                dictionary_max_end = max(dictionary_max_end, end)
                output.extend(rom[start:end])
            if len(output) > decoded_bytes:
                raise ValueError(f"indexed graphics entry {index} exceeds decoded size")
        expected_end = base + (offsets[index + 1] if index + 1 < len(offsets) else table_offset)
        if stream != expected_end:
            raise ValueError(f"indexed graphics entry {index} does not end at its next offset")
        return bytes(output), stream

    entries = []
    for index in range(len(offsets)):
        raw, end = decode_entry(index)
        entries.append({
            "entry": index,
            "source_offset": base + offsets[index],
            "source_end": end,
            "compressed_bytes": end - (base + offsets[index]),
            "decoded_bytes": len(raw),
            "sha256": sha256(raw),
            "raw": raw,
        })
    return {
        "table_offset": table_offset,
        "table_file_offset": table,
        "mode": mode,
        "bit_width": bit_width,
        "decoded_bytes_per_entry": decoded_bytes,
        "dictionary_base": dictionary_base,
        "dictionary_used_end": dictionary_max_end,
        "offsets": offsets,
        "entries": entries,
    }


def archive_token_plan(rom, entry, table, bit_width, dictionary_base):
    """Decode one A7 command stream into a reversible token description."""
    cursor = entry["source_offset"]
    decoded = entry["raw"]
    position = 0
    mask = 0xffff >> (bit_width + 1)
    tokens = []
    while position < len(decoded):
        command = rom[cursor]
        cursor += 1
        if command & 0x80:
            length = (command & 0x7f) + 1
            if rom[cursor:cursor + length] != decoded[position:position + length]:
                raise ValueError("A7 literal does not match decoded pixels")
            tokens.append({"kind": "literal", "length": length})
            cursor += length
        else:
            length = (command >> (7 - bit_width)) + 3
            offset = ((command << 8) | rom[cursor]) & mask
            cursor += 1
            start = table + dictionary_base + offset
            if rom[start:start + length] != decoded[position:position + length]:
                raise ValueError("A7 dictionary token does not match decoded pixels")
            tokens.append({"kind": "dictionary", "length": length,
                           "offset": offset})
        position += length
    if position != len(decoded) or cursor != entry["source_end"]:
        raise ValueError("A7 token plan does not cover the source entry")
    return tokens


def indexed_entry_source_files(manifest, source_dir):
    archive = manifest["archive"]
    image_format = archive.get("tile_input_format", "raw-4bpp")
    if image_format not in ("raw-4bpp", "indexed-png"):
        raise ValueError("A7 decoded image format is invalid")
    directory = archive.get("tile_directory", "tiles")
    stem = archive.get("tile_stem", "icon")
    width = archive.get("tile_index_width", 3)
    if directory not in ("tiles", "entries", "indexed-previews") or \
            stem not in ("icon", "entry") or width not in (2, 3):
        raise ValueError("A7 decoded-tile filename format is invalid")
    if image_format == "indexed-png" and directory != "indexed-previews":
        raise ValueError("indexed A7 PNGs must use the preview directory")
    for index in range(archive["entry_count"]):
        suffix = ".png" if image_format == "indexed-png" else ".4bpp"
        yield source_dir / directory / f"{stem}-{index:0{width}d}{suffix}"


def encode_indexed_archive(manifest, source_dir, verify_retail=True):
    """Re-encode an A7 archive from decoded tiles, token choices, and dictionary."""
    archive = manifest["archive"]
    entries = manifest["entries"]
    count = archive["entry_count"]
    bit_width = archive["bit_width"]
    if (count != len(entries) or not 0 < count <= 65535 or
            not 0 < bit_width <= 7 or archive["mode"] > 2):
        raise ValueError("A7 archive header is invalid")
    dictionary = (source_dir / "dictionary.bin").read_bytes()
    if sha256(dictionary) != archive["dictionary_sha256"]:
        raise ValueError("A7 dictionary differs from the exported source")
    offsets = []
    streams = bytearray()
    for index, (entry, tile_source) in enumerate(zip(
            entries, indexed_entry_source_files(manifest, source_dir))):
        if entry["entry"] != index:
            raise ValueError("A7 entries are not in index order")
        if archive.get("tile_input_format") == "indexed-png":
            columns = archive["tile_columns"]
            rows = archive["tile_rows"]
            if columns * rows * 32 != archive["decoded_bytes_per_entry"]:
                raise ValueError("A7 PNG tile dimensions differ from decoded bytes")
            width, height, pixels = read_index_png(tile_source)
            if (width, height) != (columns * 8, rows * 8):
                raise ValueError(f"A7 entry {index} PNG dimensions differ")
            raw = serialize_4bpp_grid(pixels, columns, rows)
        else:
            raw = tile_source.read_bytes()
        if (len(raw) != archive["decoded_bytes_per_entry"] or
                (verify_retail and sha256(raw) != entry["sha256"])):
            raise ValueError(f"A7 entry {index} decoded pixels differ from export")
        offsets.append(8 + count * 4 + len(streams))
        position = 0
        stream = bytearray()
        for token in entry["tokens"]:
            length = token["length"]
            if token["kind"] == "literal":
                if not 1 <= length <= 128:
                    raise ValueError("A7 literal length is invalid")
                stream.append(0x80 | (length - 1))
                stream.extend(raw[position:position + length])
            elif token["kind"] == "dictionary":
                offset = token["offset"]
                shift = 7 - bit_width
                if (not 3 <= length <= (1 << bit_width) + 2 or
                        not 0 <= offset < 1 << (15 - bit_width) or
                        dictionary[offset:offset + length] != raw[position:position + length]):
                    raise ValueError(f"A7 entry {index} dictionary token differs from pixels")
                command = ((length - 3) << shift) | (offset >> 8)
                if command >= 0x80:
                    raise ValueError("A7 dictionary command exceeds its bit field")
                stream.extend((command, offset & 0xff))
            else:
                raise ValueError("A7 token kind is invalid")
            position += length
        if position != len(raw) or (verify_retail and
                                   sha256(stream) != entry["source_sha256"]):
            raise ValueError(f"A7 entry {index} does not re-encode its source stream")
        streams.extend(stream)
    table_offset = 8 + count * 4 + len(streams)
    if table_offset != archive["table_offset"] or offsets != archive["offsets"]:
        raise ValueError("A7 archive entry offsets differ from retail")
    result = (b"A7" + count.to_bytes(2, "big") + table_offset.to_bytes(4, "big") +
              b"".join(value.to_bytes(4, "big") for value in offsets) + streams +
              bytes((archive["mode"], bit_width)) +
              archive["decoded_bytes_per_entry"].to_bytes(2, "big") + dictionary)
    if len(result) != archive["source_span_bytes"] or (verify_retail and
            sha256(result) != archive["source_span_sha256"]):
        raise ValueError("A7 archive does not match the retail source span")
    return result


def write_index_png(path, width, height, pixels):
    """A grayscale index preview; no unsupported retail palette is implied."""
    def chunk(kind, payload):
        body = kind + payload
        return struct.pack(">I", len(payload)) + body + struct.pack(">I", zlib.crc32(body))

    rows = b"".join(b"\0" + bytes(value * 17 for value in pixels[y * width:(y + 1) * width])
                    for y in range(height))
    path.write_bytes(
        b"\x89PNG\r\n\x1a\n"
        + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 0, 0, 0, 0))
        + chunk(b"IDAT", zlib.compress(rows, level=9))
        + chunk(b"IEND", b"")
    )


def read_index_png(path):
    """Read an 8-bit grayscale PNG whose samples encode 4-bit indices * 17."""
    source = path.read_bytes()
    if not source.startswith(b"\x89PNG\r\n\x1a\n"):
        raise ValueError("indexed tile grid is not a PNG")
    cursor = 8
    dimensions = None
    compressed = bytearray()
    ended = False
    while cursor + 12 <= len(source):
        length = struct.unpack_from(">I", source, cursor)[0]
        end = cursor + 12 + length
        if end > len(source):
            raise ValueError("indexed PNG chunk exceeds file")
        kind = source[cursor + 4:cursor + 8]
        payload = source[cursor + 8:cursor + 8 + length]
        checksum = struct.unpack_from(">I", source, cursor + 8 + length)[0]
        if zlib.crc32(kind + payload) != checksum:
            raise ValueError("indexed PNG chunk checksum differs")
        if kind == b"IHDR":
            if dimensions is not None or length != 13:
                raise ValueError("indexed PNG has an invalid header")
            width, height, depth, color, compression, filtering, interlace = struct.unpack(
                ">IIBBBBB", payload)
            if (not 0 < width <= 512 or not 0 < height <= 512 or
                    (depth, color, compression, filtering, interlace) != (8, 0, 0, 0, 0)):
                raise ValueError("indexed PNG must be noninterlaced 8-bit grayscale")
            dimensions = (width, height)
        elif kind == b"IDAT":
            if dimensions is None:
                raise ValueError("indexed PNG data precedes header")
            compressed.extend(payload)
        elif kind == b"IEND":
            if length or end != len(source):
                raise ValueError("indexed PNG has an invalid end")
            ended = True
            break
        elif kind[0] & 0x20 == 0:
            raise ValueError("indexed PNG has an unsupported critical chunk")
        cursor = end
    if not ended or dimensions is None:
        raise ValueError("indexed PNG is incomplete")
    width, height = dimensions
    try:
        filtered = zlib.decompress(bytes(compressed))
    except zlib.error as exc:
        raise ValueError("indexed PNG compressed data is invalid") from exc
    if len(filtered) != height * (width + 1):
        raise ValueError("indexed PNG row length differs")
    pixels = bytearray()
    previous = bytes(width)
    for row_index in range(height):
        start = row_index * (width + 1)
        filter_kind = filtered[start]
        encoded = filtered[start + 1:start + 1 + width]
        decoded = bytearray(width)
        for column, value in enumerate(encoded):
            left = decoded[column - 1] if column else 0
            above = previous[column]
            upper_left = previous[column - 1] if column else 0
            if filter_kind == 0:
                prediction = 0
            elif filter_kind == 1:
                prediction = left
            elif filter_kind == 2:
                prediction = above
            elif filter_kind == 3:
                prediction = (left + above) // 2
            elif filter_kind == 4:
                candidate = left + above - upper_left
                distances = (abs(candidate - left), abs(candidate - above),
                             abs(candidate - upper_left))
                prediction = (left, above, upper_left)[distances.index(min(distances))]
            else:
                raise ValueError("indexed PNG row filter is unsupported")
            decoded[column] = (value + prediction) & 0xff
        if any(value % 17 for value in decoded):
            raise ValueError("indexed PNG has a grayscale value outside 4-bit indices")
        pixels.extend(value // 17 for value in decoded)
        previous = decoded
    return width, height, bytes(pixels)


def rasterize_4bpp_grid(raw, tiles_x, tiles_y):
    if len(raw) != tiles_x * tiles_y * 32:
        raise ValueError("4bpp grid size does not match tile dimensions")
    width = tiles_x * 8
    pixels = bytearray(width * tiles_y * 8)
    for tile in range(tiles_x * tiles_y):
        for y in range(8):
            for x in range(8):
                packed = raw[tile * 32 + y * 4 + x // 2]
                value = (packed >> (4 * (x & 1))) & 15
                pixels[((tile // tiles_x) * 8 + y) * width
                       + (tile % tiles_x) * 8 + x] = value
    return bytes(pixels)


def serialize_4bpp_grid(pixels, tiles_x, tiles_y):
    width = tiles_x * 8
    if len(pixels) != width * tiles_y * 8 or any(value > 15 for value in pixels):
        raise ValueError("4bpp grid indices or dimensions are invalid")
    raw = bytearray(tiles_x * tiles_y * 32)
    for tile in range(tiles_x * tiles_y):
        for y in range(8):
            for x in range(8):
                value = pixels[((tile // tiles_x) * 8 + y) * width
                               + (tile % tiles_x) * 8 + x]
                raw[tile * 32 + y * 4 + x // 2] |= value << (4 * (x & 1))
    return bytes(raw)
