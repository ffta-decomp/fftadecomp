/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BA6E4.c
 * Original SHA-256: 7baa0db3f79318445e23b0cd552d6c2e5e83bd131e1bd7f96c30e1e76e3edbf6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Record080BA6E4 {
    u8 unknown00[0x108];
};

struct Context080BA6E4 {
    u8 unknown00[0x0C];
    struct Record080BA6E4 *entries[149];
    s8 count;
};

extern s32 func_080C7EA4(const void *object, u32 selector);

/* Complete [0x080BA6E4, 0x080BA728): 68 bytes, 33 instructions. */
void func_080BA6E4(void *data,
                   struct Record080BA6E4 *records, s32 count)
{
    struct Record080BA6E4 *record = records;
    struct Context080BA6E4 *context = data;
    s32 i;

    for (i = 0; i < count; i++, record++) {
        if (func_080C7EA4(record, 1)) {
            context->entries[context->count] = record;
            context->count++;
        }
    }
}
