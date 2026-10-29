/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147CC0.c
 * Original SHA-256: f684614a6526dc6ddc0d43fa9b5d9e18357ba7722674eea47dc85a7f4c805365
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry;

extern PaletteEntry data_03003E68[];
typedef struct PaletteTransition PaletteTransition;
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x08147CC0..0x08147D2C - 108 bytes including literal pool. */
PaletteTransition *func_08147CC0(u16 start, u16 count, u16 duration,
                                u16 red, u16 green, u16 blue)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = (green << 5) | red | (blue << 10);

    return func_08146E54(start, end, duration, 0);
}
