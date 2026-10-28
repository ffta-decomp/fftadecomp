/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D465C.c
 * Original SHA-256: cbb7cad4c045861b53a947b3b6add53c2f7d1e3ba71eddaf28e35d85415c264d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 rows;
    u8 columns;
    u16 values[1];
} Rows080D465C;

extern u16 data_03003860[];
extern u16 data_03003A60[];
extern void (*data_0836D4BC)(void *destination, const void *source, u32 length);

/* 0x080D465C: 104 bytes; copy rows into the selected halfword bank. */
void func_080D465C(const Rows080D465C *rows, u8 index, u8 bank)
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
    for (row = 0; row < rows->rows; row++) {
        data_0836D4BC(destination, source, rows->columns * 2);
        destination += 16;
        source += rows->columns;
    }
}
