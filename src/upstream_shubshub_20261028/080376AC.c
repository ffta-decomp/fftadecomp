/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080376AC.c
 * Original SHA-256: dda1941f1bf34ac447261b4c34efa0cb3c74ca141da989554b256958c64d9022
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 *table;
} RecordContext080376AC;

extern RecordContext080376AC *g_state_03002810;

s32 func_080376AC(u8 start)
{
    s32 index;

    for (index = start; index < 30; index++) {
        u8 *flags = g_state_03002810->table + index * 12 + 0xB1;

        if ((*flags & 0x11) == 0x11) {
            *flags ^= 0x10;
            return index + 1;
        }
    }

    return 0;
}
