/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147F50.c
 * Original SHA-256: d787f875dcbd4ec12af7d5cbe6fbc3479de806904c27089a561dc5118c041f9e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147F50;

typedef struct PaletteTransition PaletteTransition;
extern u16 data_03003860[];
extern PaletteEntry08147F50 data_03003E68[];
extern u16 func_08147958(u16 color, u8 amount);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Complete [0x08147F50, 0x08147FD8): 136 bytes, 59 instructions. */
PaletteTransition *func_08147F50(u16 start, u16 count, u16 duration, u8 amount)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_08147958(data_03003860[index], amount);

    return func_08146E54(start, end, duration, 0);
}
