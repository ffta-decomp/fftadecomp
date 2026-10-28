/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BC7AC.c
 * Original SHA-256: 515e2f7b780f8af908b663275c5a8a97918f8f358d752e5b4d49a80fe8c4f5df
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Record080BC7AC {
    u8 unknown00[0x21];
    u8 flag;
    u8 unknown22[6];
};

extern const struct Record080BC7AC g_table_0854CD54[];

/* Complete [0x080BC7AC, 0x080BC7D2): 38 bytes, 17 instructions. */
s32 func_080BC7AC(u16 index)
{
    const struct Record080BC7AC *record = &g_table_0854CD54[index];

    if (record->flag != 0)
        return 1;
    return 0;
}
