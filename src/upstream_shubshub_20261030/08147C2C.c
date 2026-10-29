/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147C2C.c
 * Original SHA-256: 75e85833977bf389f686a98e0a99dc633f6ac17566e28c23e30696426ff85181
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry;

typedef struct PaletteTransition PaletteTransition;

extern u16 data_03003860[];
extern PaletteEntry data_03003E68[];
extern u16 func_081483EC(u16 color, u16 red, u16 green, u16 blue);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x08147C2C..0x08147CC0 - 148 bytes including literal pool. */
PaletteTransition *func_08147C2C(u16 start, u16 count, u16 duration,
                                u16 red, u16 green, u16 blue)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_081483EC(data_03003860[index], red, green, blue);

    return func_08146E54(start, end, duration, 0);
}
