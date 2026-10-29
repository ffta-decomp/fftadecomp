/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147D94.c
 * Original SHA-256: ee14ef1d39bc6be40b26aaceeb38c0adc62daf417eef390f0d3f8bb7d80283f5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147D94;

typedef struct PaletteTransition PaletteTransition;
extern u16 data_03003860[];
extern PaletteEntry08147D94 data_03003E68[];
extern u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Complete [0x08147D94, 0x08147E28): 148 bytes, 66 instructions. */
PaletteTransition *func_08147D94(u16 start, u16 count, u16 duration,
                                u16 reference, u8 amount, u8 mode)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_08147830(data_03003860[index],
                                                 reference, amount, mode);

    return func_08146E54(start, end, duration, 0);
}
