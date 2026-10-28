/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802B430.c
 * Original SHA-256: 4830be548d3a1fe31c7431c5d4b51f36d8426ed37e269613e55c66bcb152c652
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0802B430..0x0802B45E: 46 bytes. */
typedef struct {
    u8 unknown_00[8];
    u16 second;
    u8 unknown_0A[0xA];
    u16 first;
    u8 unknown_16[2];
    u16 third;
} ValueState;

u16 func_0802B430(const ValueState *state, u8 index)
{
    switch (index) {
    case 0:
        return state->first;
    case 1:
        return state->second;
    case 2:
        return state->third;
    default:
        return 0;
    }
}
