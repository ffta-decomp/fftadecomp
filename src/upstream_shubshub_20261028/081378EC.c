/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081378EC.c
 * Original SHA-256: d4d1ce55788a90e53ad97d50d77c88f2e34cefcaa5db51e9840d64f0bccb1843
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x081378EC, 0x0813790A): 30 bytes, 13 instructions. */
typedef struct {
    void *resource;
    u8 enabled;
} ResourceState;

extern u32 func_0814846C(void *resource);
extern void func_08148498(void *resource);

void func_081378EC(ResourceState *state)
{
    state->enabled = 0;
    if (func_0814846C(state->resource))
        func_08148498(state->resource);
}
