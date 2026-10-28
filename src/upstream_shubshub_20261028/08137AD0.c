/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08137AD0.c
 * Original SHA-256: a0533638720a46fe1f3119572d155b37c0a6289c161b3933033378ebafe41f97
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08137AD0, 0x08137AEC): 28 bytes, 11 instructions. */
extern void *data_0201C3C8;
extern void func_0800718C(void *owner);

void func_08137AD0(void)
{
    if (data_0201C3C8 != 0) {
        func_0800718C(data_0201C3C8);
        data_0201C3C8 = 0;
    }
}
