/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806F0DC.c
 * Original SHA-256: 5ad93c077b142f44d472a4aeacc4001462edaf785ebe746d556f06c834e432b2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0806F0DC, 0x0806F1EC): 272 bytes, 126 instructions. */
typedef struct {
    s8 x;
    s8 y;
    u8 active;
    u8 unknown_03;
    u16 entry;
} ValueDisplay;

extern s32 func_080CA7A4(u16, u8);
extern void func_0806F568(s16, s16, u8, u16);

void func_0806F0DC(ValueDisplay *state)
{
    if (state->active) {
        func_0806F568(state->x * 8 + 80, state->y * 8 + 4, 3,
                      func_080CA7A4(state->entry, 10));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 16, 3,
                      func_080CA7A4(state->entry, 11));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 28, 3,
                      func_080CA7A4(state->entry, 12));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 40, 3,
                      func_080CA7A4(state->entry, 13));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 52, 3,
                      func_080CA7A4(state->entry, 14));
    }
}
