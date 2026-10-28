/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CA5C4.c
 * Original SHA-256: 973cb1a7e5743af22ac5ed27ea6c6f6735fb7b9618733b3f427b408ac8e1be5b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2A];
    u16 entries[5];
} EntryObject;

u32 func_080C92F0(void *object, u32 selector);
s32 func_080CA7A4(u16 entry, u8 selector);

s32 func_080CA5C4(void *object)
{
    s16 base = func_080C92F0(object, 0x20);
    s32 sum = 0;
    s32 index;
    s32 result;

    for (index = 0; index < 5; index++) {
        if (((EntryObject *)object)->entries[index] != 0)
            sum += func_080CA7A4(((EntryObject *)object)->entries[index], 0x0F);
    }
    result = (s16)(base + sum);
    if (result < 0)
        result = 0;
    else if (result > 100)
        result = 100;
    return result;
}
