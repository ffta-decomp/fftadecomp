/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D6D0C.c
 * Original SHA-256: c6665a5deab22a694eb7788616b0d70b390dbd4fa7c4f0721e9fc34f40f7bf8e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D6D0C..0x080D6E2E: 290 bytes. */
typedef struct {
    u8 width;
    u8 height;
    u8 unknown_02[2];
    u8 mode;
    u8 flags;
    u8 data[1];
} TilePattern;

extern void func_080D6950(u16 *destination, s16 x, s16 y, const u8 *data,
                          u8 width, u8 height, u16 base, u8 flags);

void func_080D6D0C(u16 *destination, const TilePattern *pattern, u16 base)
{
    u16 i;
    u16 j;

    switch (pattern->mode) {
    case 1:
        func_080D6950(destination, 0, 0, pattern->data,
                      pattern->width, pattern->height, base, pattern->flags & 2);
        break;
    case 2:
        for (i = 0; i < 32; i += pattern->width) {
            func_080D6950(destination, (s16)i, 0, pattern->data,
                          pattern->width, pattern->height, base, pattern->flags & 2);
        }
        break;
    case 3:
        for (i = 0; i < 32; i += pattern->height) {
            func_080D6950(destination, 0, (s16)i, pattern->data,
                          pattern->width, pattern->height, base, pattern->flags & 2);
        }
        break;
    case 4:
        for (j = 0; j < 32; j += pattern->height) {
            for (i = 0; i < 32; i += pattern->width) {
                func_080D6950(destination, (s16)i, (s16)j, pattern->data,
                              pattern->width, pattern->height, base, pattern->flags & 2);
            }
        }
        break;
    }
}
