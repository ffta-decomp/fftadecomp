/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813B9F8.c
 * Original SHA-256: 1b9efffd220cfb2b757b8e8528f4aff3a4b560db993a368a03ff63437a5726f9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813B9F8..0x0813BA5C: 100 bytes. */
extern const u16 g_table_08529EE4[];
extern u8 func_080C95D8(u16 id, void *context);
extern u8 func_0813B9B8(void *context);

u16 func_0813B9F8(void *context)
{
    s32 count = 0;
    s32 i;
    u16 id;

    for (i = 0; (id = g_table_08529EE4[i]) != 0xFFFF; ++i) {
        if (func_080C95D8(id + 0x2FF, context))
            ++count;
    }
    if (func_080C95D8(0x36, context))
        ++count;
    else if (func_0813B9B8(context))
        ++count;
    return count;
}
