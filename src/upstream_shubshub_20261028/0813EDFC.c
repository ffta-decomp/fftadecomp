/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EDFC.c
 * Original SHA-256: 4776b7b1806db16914a2e1468df99d4ea71cacfbb9f23821121ed754b0354791
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0813EDFC, 0x0813EE16): 26 bytes, 13 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 count;
    u8 unknown_0a[0x64];
    u16 current;
} SequenceState;

u32 func_0813EDFC(const SequenceState *state)
{
    if (state->current >= state->count - 1)
        return 1;
    return 0;
}
