/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08061C24.c
 * Original SHA-256: 06aa9f0ccb170969dc0eda6cd64d736678ab5f133d93cb300fde594b2571158a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 sort_key;
} Item;

/* Complete target: [0x08061C24, 0x08061C30), 12 bytes, 6 instructions. */
s32 func_08061C24(const void *left, const void *right)
{
    const Item *a = *(const Item *const *)left;
    const Item *b = *(const Item *const *)right;

    return a->sort_key - b->sort_key;
}
