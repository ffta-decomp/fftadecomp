/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08147E28.c
 * Original SHA-256: a020bba50b23b838476873e4147344742176e74027fa725131dc74d5c01b0951
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147E28;

typedef struct PaletteTransition PaletteTransition;
extern PaletteEntry08147E28 data_03003E68[];
extern u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Complete [0x08147E28, 0x08147EC8): 160 bytes, 73 instructions. */
PaletteTransition *func_08147E28(u16 start, u16 count, u16 duration,
                                const u16 *source, u16 reference,
                                u8 amount, u8 mode)
{
    u16 end = start + count - 1;
    u16 index;
    u16 source_index;

    if (end > 511)
        end = 511;

    for (index = start, source_index = 0; index <= end; index++, source_index++)
        data_03003E68[index].color = func_08147830(source[source_index],
                                                 reference, amount, mode);

    return func_08146E54(start, end, duration, 0);
}
