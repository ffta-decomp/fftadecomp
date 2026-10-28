/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802DF10.c
 * Original SHA-256: edfcfa4ee51becf0194146e9a49edb30719562ddfb45516161cb5086c5356701
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 category : 4;
    u16 value : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} __attribute__((packed)) CategoryEntry;

extern CategoryEntry data_02003C3C[24];

/* 0802DF10..0802DF50: 64 bytes. */
u8 func_0802DF10(u8 category)
{
    s32 count = 0;
    CategoryEntry *entry = data_02003C3C;
    s32 index;

    for (index = 0; index < 24; index++, entry++) {
        if (entry->value == 0)
            return count;
        if (entry->category == category)
            count++;
    }
    return count;
}
