/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011710.c
 * Original SHA-256: 66783658f0dafa87d965063f8322fe496170bc5a631e26038a00c52799e8186b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08011710..08011744: 52 bytes. */
s16 func_08011710(void *const *entries, u16 count)
{
    s16 index;

    for (index = 0; index < count; index++) {
        if (entries[index] == 0)
            return index;
    }
    return -1;
}
