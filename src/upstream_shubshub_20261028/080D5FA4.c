/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D5FA4.c
 * Original SHA-256: 5c1f4fdc6df1e958c3e2d20b7e9dc0aaf050c38ee608ccef7cd4c070ad041923
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D5FA4..0x080D5FD8: 52 bytes, 26 instructions. */
s32 func_080D5FA4(const u32 *entries, u16 count)
{
    s16 i;

    for (i = 0; i < count; i++) {
        if (entries[i] == 0) {
            return i;
        }
    }
    return -1;
}
