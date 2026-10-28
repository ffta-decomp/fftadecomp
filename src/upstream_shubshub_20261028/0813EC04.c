/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EC04.c
 * Original SHA-256: b99f0dd78650bd4e246e42020a00d9062e3482ac0f107ace3ea9a408b788e5ea
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813EC04..0x0813EC26: 34 bytes, 16 instructions. */
typedef struct {
    u8 mode;
    u8 unknown_01[0x0B];
    u8 destination[0x10];
    u32 field_1C;
    u32 field_20;
} State;

extern void func_0814186C(const void *source, void *destination, u32 count);

void func_0813EC04(State *state, const void *source, u32 value)
{
    func_0814186C(source, state->destination, 4);
    state->field_1C = 0;
    state->field_20 = value;
    state->mode = 2;
}
