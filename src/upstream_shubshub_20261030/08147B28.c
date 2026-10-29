/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147B28.c
 * Original SHA-256: ee1c437eb77baf6d847684d2c401a0a6fef943bf0f19986c2611fe39fe8039fb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147B28;

typedef struct PaletteTransition PaletteTransition;

extern u16 data_03003860[];
extern PaletteEntry08147B28 data_03003E68[];
extern u16 func_081477DC(u16 color);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Target: complete [0x08147B28, 0x08147BA4), 124 bytes, 53 instructions. */
PaletteTransition *func_08147B28(u16 start, u16 count, u16 duration)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_081477DC(data_03003860[index]);

    return func_08146E54(start, end, duration, 0);
}
