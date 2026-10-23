"""Convert FFTA's 16x16 4bpp glyphs to and from a grayscale atlas."""

GLYPH_WIDTH = 16
GLYPH_HEIGHT = 16
GLYPH_BYTES = 128


def atlas_dimensions(glyph_count, columns):
    if glyph_count <= 0 or columns <= 0:
        raise ValueError("Glyph count and atlas columns must be positive")
    return columns * GLYPH_WIDTH, ((glyph_count + columns - 1) // columns) * GLYPH_HEIGHT


def decode_atlas(font, glyph_count, columns):
    if len(font) != glyph_count * GLYPH_BYTES:
        raise ValueError("Font length does not match glyph count")
    width, height = atlas_dimensions(glyph_count, columns)
    pixels = bytearray(width * height)
    for glyph in range(glyph_count):
        gx = glyph % columns * GLYPH_WIDTH
        gy = glyph // columns * GLYPH_HEIGHT
        raw = font[glyph * GLYPH_BYTES:(glyph + 1) * GLYPH_BYTES]
        for y in range(GLYPH_HEIGHT):
            for x in range(GLYPH_WIDTH):
                packed = raw[(x // 8) * 64 + y * 4 + (x % 8) // 2]
                pixels[(gy + y) * width + gx + x] = (packed >> (4 * (x % 2))) & 15
    return f"P5\n{width} {height}\n15\n".encode("ascii") + pixels


def encode_atlas(pgm, glyph_count, columns):
    width, height = atlas_dimensions(glyph_count, columns)
    header = f"P5\n{width} {height}\n15\n".encode("ascii")
    if not pgm.startswith(header) or len(pgm) != len(header) + width * height:
        raise ValueError("Atlas must be an exact P5 grayscale image with 4-bit pixels")
    pixels = pgm[len(header):]
    if any(value > 15 for value in pixels):
        raise ValueError("Atlas contains pixels outside the 4-bit palette")
    font = bytearray(glyph_count * GLYPH_BYTES)
    for glyph in range(glyph_count):
        gx = glyph % columns * GLYPH_WIDTH
        gy = glyph // columns * GLYPH_HEIGHT
        for y in range(GLYPH_HEIGHT):
            for x in range(GLYPH_WIDTH):
                value = pixels[(gy + y) * width + gx + x]
                index = glyph * GLYPH_BYTES + (x // 8) * 64 + y * 4 + (x % 8) // 2
                font[index] |= value << (4 * (x % 2))
    if any(pixels[(glyph // columns * GLYPH_HEIGHT + y) * width +
                  (glyph % columns * GLYPH_WIDTH + x)]
           for glyph in range(glyph_count, columns * (height // GLYPH_HEIGHT))
           for y in range(GLYPH_HEIGHT) for x in range(GLYPH_WIDTH)):
        raise ValueError("Unused atlas cells must be blank")
    return bytes(font)
