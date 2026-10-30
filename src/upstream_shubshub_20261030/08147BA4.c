/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147BA4.c
 * Original SHA-256: 7055d179083a43407e2308efafa128b8271f87679700d4128b4de87643a9d044
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147BA4;

typedef struct PaletteTransition PaletteTransition;

extern u16 data_03003860[];
extern PaletteEntry08147BA4 data_03003E68[];
extern u16 func_081483EC(u16 color, u16 red, u16 green, u16 blue);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Target: complete [0x08147BA4, 0x08147C2C), 136 bytes, 57 instructions. */
PaletteTransition *func_08147BA4(u16 start, u16 count, u16 duration)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_081483EC(data_03003860[index],
                                                  294, 273, 204);

    return func_08146E54(start, end, duration, 0);
}
