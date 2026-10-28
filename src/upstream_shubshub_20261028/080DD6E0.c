/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD6E0.c
 * Original SHA-256: 6cf50aba20f4f58b83029f04895baf8991f4a7d9641672d7303851d4d81c67e7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Owner080DD6E0 {
    const void *object;
};

extern s32 func_080C7EA4(const void *object, u32 selector);

u16 func_080DD6E0(const struct Owner080DD6E0 *owner)
{
    return func_080C7EA4(owner->object, 1);
}
