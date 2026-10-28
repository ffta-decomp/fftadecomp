/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D61E4.c
 * Original SHA-256: e05ffe8e788fb72222fd3da9ea302800bd32753bbb2b58e40cbb08e76f3b1a2c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D61E4..0x080D620A: 38 bytes. */
typedef struct {
    u8 unknown_00[0x0E];
    u8 flags;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

void func_080D61E4(int index, u8 enabled)
{
    ObjectState *state = func_08005BFC(index);

    if (enabled)
        state->flags |= 8;
    else
        state->flags &= ~8;
}
