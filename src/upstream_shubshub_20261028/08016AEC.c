/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08016AEC.c
 * Original SHA-256: 7af6b0b42859dadfdffe5c17f7873fee495f96f60b1dbbef2e652d9d876b46cc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Rectangle {
    u8 left;
    u8 top;
    u8 width;
    u8 height;
} Rectangle;

extern u16 func_080161A0(u8 x, u8 y, u8 stride);
extern void func_0814186C(const void *source, void *destination, u32 count);

/* 08016AEC..08016B4E: 98 bytes, 47 instructions. */
void func_08016AEC(u16 *destination, u8 destination_stride,
                   const u16 *source, Rectangle area, u8 source_stride)
{
    u16 *output = destination;
    const u16 *cursor;
    s32 remaining;

    cursor = source + func_080161A0(area.left, area.top, source_stride);
    remaining = area.height;
    while (remaining != 0) {
        func_0814186C(cursor, output, area.width);
        cursor += source_stride;
        output += destination_stride;
        remaining--;
    }
}
