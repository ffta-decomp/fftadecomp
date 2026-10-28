/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D46C4.c
 * Original SHA-256: 5cd1d1c92b40b5268bdc00a59f3bf1b620fe76f4791d44c3efe7ff998949fc1e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D46C4..0x080D4704: 64 bytes / 29 instructions. */
typedef struct {
    u8 unknown_00;
    u8 width;
    u16 entries[1];
} PackedRows;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);
extern BufferCopier const data_0836D4BC[];

void func_080D46C4(const PackedRows *rows, u8 row, u8 column, u8 count,
                   void *destination)
{
    const u16 *source = rows->entries;
    u8 index;

    for (index = 0; index < row; index++)
        source += rows->width;
    source += column;
    data_0836D4BC[0](destination, source, count * sizeof(u16));
}
