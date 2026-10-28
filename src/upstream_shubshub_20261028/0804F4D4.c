/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804F4D4.c
 * Original SHA-256: 1769c6d42c609dad4380359b64000ff1e21630c031a78ebeac2086b6cce4110a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804F4D4..0x0804F5BC: 232 bytes, 105 instructions. */
typedef void (*BufferInitializer)(void *, u32);
extern BufferInitializer g_callbacks_0836D4B8[];
extern const u8 *data_085668B0[];
extern u16 func_08014778(const u8 *text);
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018C24(u8 *destination, const u8 *source);

u8 func_0804F4D4(u8 *buffer)
{
    u8 *cursor = buffer;
    u16 width;
    u8 alignment;

    g_callbacks_0836D4B8[0](buffer, 128);
    *cursor++ = 0x40;
    *cursor++ = 0x25;
    *cursor++ = 0x1f;
    *cursor++ = 0x40;
    *cursor++ = 0x25;
    *cursor++ = 3;
    *cursor = 0;
    width = func_08014778(buffer);
    alignment = 8 - (width % 8);
    width = (u16)(width + alignment) >> 3;
    if (width < 14) {
        cursor += func_08018CB8(cursor, (14 - width) * 8);
        width = 14;
    }
    if (width & 1) {
        cursor += func_08018CB8(cursor, 8);
        width++;
    }
    cursor += func_08018CB8(cursor, alignment + 8);
    cursor += func_08018C24(cursor, data_085668B0[40]);
    *cursor++ = 0x40;
    *cursor++ = 0x25;
    *cursor++ = 0x40;
    *cursor = 0;
    return width + 6;
}
