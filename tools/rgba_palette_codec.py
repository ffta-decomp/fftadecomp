"""Losslessly map RGBA PNG pixels through an explicit GBA 16-color palette."""

import struct
import zlib


PNG_SIGNATURE = b"\x89PNG\r\n\x1a\n"


def _chunk(kind, payload):
    body = kind + payload
    return struct.pack(">I", len(payload)) + body + struct.pack(">I", zlib.crc32(body))


def write_rgba_png(path, width, height, rgba):
    if len(rgba) != width * height * 4:
        raise ValueError("RGBA image size differs")
    rows = b"".join(b"\0" + rgba[row * width * 4:(row + 1) * width * 4]
                    for row in range(height))
    path.write_bytes(PNG_SIGNATURE +
                     _chunk(b"IHDR", struct.pack(">IIBBBBB", width, height,
                                                   8, 6, 0, 0, 0)) +
                     _chunk(b"IDAT", zlib.compress(rows, level=9)) +
                     _chunk(b"IEND", b""))


def read_rgba_png(path):
    source = path.read_bytes()
    if not source.startswith(PNG_SIGNATURE):
        raise ValueError("RGBA asset is not a PNG")
    cursor = len(PNG_SIGNATURE)
    dimensions = None
    compressed = bytearray()
    ended = False
    while cursor + 12 <= len(source):
        length = struct.unpack_from(">I", source, cursor)[0]
        end = cursor + 12 + length
        if end > len(source):
            raise ValueError("RGBA PNG chunk exceeds file")
        kind = source[cursor + 4:cursor + 8]
        payload = source[cursor + 8:cursor + 8 + length]
        if zlib.crc32(kind + payload) != struct.unpack_from(">I", source, cursor + 8 + length)[0]:
            raise ValueError("RGBA PNG chunk checksum differs")
        if kind == b"IHDR":
            if dimensions is not None or length != 13:
                raise ValueError("RGBA PNG header is invalid")
            width, height, depth, color, compression, filtering, interlace = struct.unpack(
                ">IIBBBBB", payload)
            if (not 0 < width <= 512 or not 0 < height <= 512 or
                    (depth, color, compression, filtering, interlace) != (8, 6, 0, 0, 0)):
                raise ValueError("RGBA PNG must be noninterlaced 8-bit RGBA")
            dimensions = (width, height)
        elif kind == b"IDAT":
            if dimensions is None:
                raise ValueError("RGBA PNG data precedes header")
            compressed.extend(payload)
        elif kind == b"IEND":
            if length or end != len(source):
                raise ValueError("RGBA PNG end is invalid")
            ended = True
            break
        elif kind[0] & 0x20 == 0:
            raise ValueError("RGBA PNG has an unsupported critical chunk")
        cursor = end
    if not ended or dimensions is None:
        raise ValueError("RGBA PNG is incomplete")
    width, height = dimensions
    try:
        filtered = zlib.decompress(bytes(compressed))
    except zlib.error as exc:
        raise ValueError("RGBA PNG compressed data is invalid") from exc
    stride = width * 4
    if len(filtered) != height * (stride + 1):
        raise ValueError("RGBA PNG row size differs")
    rgba = bytearray()
    previous = bytes(stride)
    for row in range(height):
        start = row * (stride + 1)
        filter_kind = filtered[start]
        encoded = filtered[start + 1:start + 1 + stride]
        decoded = bytearray(stride)
        for column, value in enumerate(encoded):
            left = decoded[column - 4] if column >= 4 else 0
            above = previous[column]
            upper_left = previous[column - 4] if column >= 4 else 0
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
                raise ValueError("RGBA PNG row filter is unsupported")
            decoded[column] = (value + prediction) & 0xff
        rgba.extend(decoded)
        previous = decoded
    return width, height, bytes(rgba)


def palette_rgba(bgr555):
    if len(bgr555) != 32:
        raise ValueError("GBA OBJ palette must contain 16 halfwords")
    colors = []
    for index, (word,) in enumerate(struct.iter_unpack("<H", bgr555)):
        word &= 0x7fff  # OBJ display ignores the source word's high bit.
        rgb = tuple(((word >> shift) & 31) * 255 // 31 for shift in (0, 5, 10))
        colors.append(bytes((*rgb, 0 if index == 0 else 255)))
    return colors


def indexed_to_rgba(indices, bgr555):
    colors = palette_rgba(bgr555)
    if any(index > 15 for index in indices):
        raise ValueError("pixel index is not 4-bit")
    return b"".join(colors[index] for index in indices)


def rgba_to_indices(rgba, bgr555, index_hint=None):
    """Use the indexed plane to retain identity when palette colors collide."""
    if len(rgba) % 4:
        raise ValueError("RGBA pixel buffer is incomplete")
    colors = palette_rgba(bgr555)
    indices = bytearray()
    if index_hint is not None and len(index_hint) != len(rgba) // 4:
        raise ValueError("palette index plane size differs from RGBA image")
    for position, (red, green, blue, alpha) in enumerate(struct.iter_unpack("BBBB", rgba)):
        if alpha == 0:
            indices.append(0)
            continue
        if alpha != 255:
            raise ValueError("semi-transparent pixel cannot be stored in 4bpp OBJ tiles")
        matches = [index for index in range(1, 16)
                   if colors[index][:3] == bytes((red, green, blue))]
        if len(matches) > 1 and index_hint is not None and index_hint[position] in matches:
            indices.append(index_hint[position])
            continue
        if len(matches) != 1:
            raise ValueError("RGBA pixel does not map uniquely to the selected palette")
        indices.append(matches[0])
    return bytes(indices)
