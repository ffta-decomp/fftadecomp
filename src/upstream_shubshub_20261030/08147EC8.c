/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147EC8.c
 * Original SHA-256: 4c1b79d8b0f4556d8f52bae72a57e9a7f4ed10b8d207f284b804308bd387d48c
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
extern u16 func_081478DC(u16 color, u8 amount);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x08147EC8..0x08147F50 - 136 bytes, 59 instructions including literal pool. */
PaletteTransition *func_08147EC8(u16 start, u16 count, u16 duration, u8 amount)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_081478DC(data_03003860[index], amount);

    return func_08146E54(start, end, duration, 0);
}
