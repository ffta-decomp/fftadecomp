/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D3FF8.c
 * Original SHA-256: ba327167d7c68ffd4f0ad94f0c89774cadf87e702d72dcbabbaecbf35b45d1d3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 flags;
} State;

extern State *func_08005BFC(void *object);

void func_080D3FF8(void *object, u8 enabled)
{
    State *state = func_08005BFC(object);

    if (enabled)
        state->flags |= 0x80;
    else
        state->flags &= ~0x80;
}
