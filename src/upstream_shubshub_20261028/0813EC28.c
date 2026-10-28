/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EC28.c
 * Original SHA-256: f0224add0270929e31d753a5bc68c374aa41b3235e156244788cb5d4da0c037b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 active;
    u8 kind;
    u8 unknown_02[2];
    u8 first[0x10];
    u8 second[8];
    u32 field_1C;
    u32 field_20;
} State;

extern void func_0814186C(const void *source, void *destination, u32 count);

/* Complete [0x0813EC28, 0x0813EC5A): 50 bytes, 23 instructions. */
void func_0813EC28(State *state, const void *source, u32 value)
{
    if (source != 0) {
        func_0814186C(source, state->first, 4);
        func_0814186C(source, state->second, 4);
    }
    state->field_1C = 0;
    state->field_20 = value;
    state->active = 1;
}
