/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DD00.c
 * Original SHA-256: b5f246d6a245c99fc0a619146ac05d979c58ea86b26848995eb9147c40010079
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801DD00..0x0801DD34: 52 bytes / 24 instructions. */
typedef struct {
    u8 unknown_00[2];
    u16 selector;
    u16 first;
    u8 unknown_06[6];
    u16 second;
    u16 third;
    u32 fourth;
} ParameterState;

extern ParameterState data_02007F20;

void func_0801DD00(u16 *first, u16 *second, u16 *third, u32 *fourth)
{
    ParameterState *state = &data_02007F20;

    *first = 0;
    *second = 0;
    *third = 0;
    *fourth = 0;
    if (state->selector != 0xFF) {
        *first = state->first;
        *second = state->second;
        *third = state->third;
        *fourth = state->fourth;
    }
}
