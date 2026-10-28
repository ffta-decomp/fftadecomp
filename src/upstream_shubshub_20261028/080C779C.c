/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C779C.c
 * Original SHA-256: bd3a6b643c47c6a2ca4959836deaeaed17701dabc3762a63e563d65202e73cc5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[0x46];
} State080C779C;

typedef void (*BufferInitializer080C779C)(void *destination, u32 size);

extern BufferInitializer080C779C const g_callbacks_0836D4B8[];
extern State080C779C data_02015970;

/* Complete [0x080C779C, 0x080C77C0): 36 bytes, 12 instructions. */
void func_080C779C(void)
{
    BufferInitializer080C779C const *callbacks = g_callbacks_0836D4B8;
    State080C779C *state = &data_02015970;

    callbacks[0](state, sizeof(*state));
    state->phase = 0;
}
