/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812F080.c
 * Original SHA-256: 6293c99a25c819c8a7c0f017e71e126497e99e01ded4bdb2f59d59ac5b164962
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Object Object;
extern s32 func_0812C8DC(const Object *source, const Object *target,
                         u32 mode, u32 option);

/* Complete [0x0812F080, 0x0812F090): 16 bytes, 7 instructions. */
s32 func_0812F080(const Object *source, const Object *target, u8 mode)
{
    return func_0812C8DC(source, target, mode, 0);
}
