/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08096FD8.c
 * Original SHA-256: af3bde067c1fba7e8bf65ed52e249bd68e2c37acf9cce6b22dfaac5f5ad15343
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 selector;
    s8 selection;
    u8 unknown_06[0x4E];
} State08096FD8;

typedef void (*BufferInitializer08096FD8)(void *destination, u32 size);

extern BufferInitializer08096FD8 const g_callbacks_0836D4B8[];
extern State08096FD8 data_0200F6A0;

/* Complete [0x08096FD8, 0x08097000): 40 bytes, 15 instructions. */
void func_08096FD8(void)
{
    BufferInitializer08096FD8 const *callbacks = g_callbacks_0836D4B8;
    State08096FD8 *state = &data_0200F6A0;

    callbacks[0](state, sizeof(*state));
    state->selector = 0xFF;
    state->selection = -1;
}
