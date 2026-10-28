/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08021D14.c
 * Original SHA-256: 629eaa2478e6359f51589c0e59cbe1081f26d3cc9f56f736117776414cfefde5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x2C];
    u16 first;
    u16 second;
} ValueState;

/* 08021D14..08021D40: 44 bytes. */
void func_08021D14(const ValueState *state, u16 *first, u16 *second)
{
    if ((state->flags & 0x800) == 0) {
        *first = *second = 0x100;
    } else {
        *first = state->first;
        *second = state->second;
    }
}
