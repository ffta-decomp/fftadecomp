/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D45D0.c
 * Original SHA-256: 95d3c0345750637c20a92822a8a6a5478b0cccf2d71c4a61edfab3a9166dbdcd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct PaletteRows080D45D0 {
    u8 rows;
    u8 columns;
    u16 values[1];
} PaletteRows080D45D0;

extern u16 data_03003860[];
extern u16 data_03003A60[];
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);

/* Complete [0x080D45D0, 0x080D465C): 140 bytes, 62 instructions. */
void func_080D45D0(const PaletteRows080D45D0 *rows, u8 index, u8 bank,
                   u8 first_row, u8 count)
{
    u16 *destination;
    const u16 *source;
    u8 row;

    if (bank == 0)
        destination = data_03003860 + index * 16;
    else
        destination = data_03003A60 + index * 16;
    destination++;
    source = rows->values;
    for (row = 0; row < first_row; row++)
        source += rows->columns;
    for (row = 0; row < count; row++) {
        data_0836D4BC(destination, source, rows->columns * sizeof(u16));
        destination += 16;
        source += rows->columns;
    }
}
