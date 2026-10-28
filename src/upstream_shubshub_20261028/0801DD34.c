/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DD34.c
 * Original SHA-256: b0275140bf80b6d05302026d847964e2474d49212d8fbb53a99edd1bd5ac1c9a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct ParameterState0801DD34 {
    u8 unknown_00[2];
    u16 selector;
    u16 first;
    u8 unknown_06[6];
    u16 second;
    u16 third;
    u32 fourth;
    u32 derived;
} ParameterState0801DD34;

extern ParameterState0801DD34 data_02007F20;

/* Complete [0x0801DD34, 0x0801DD68): 52 bytes, 23 instructions. */
void func_0801DD34(u16 first, u16 second, u16 third, u32 fourth)
{
    ParameterState0801DD34 *state = &data_02007F20;

    if (state->selector != 0xFF) {
        state->first = first;
        state->second = second;
        state->third = third;
        state->fourth = fourth;
        state->derived = fourth + state->first - 160;
    }
}
