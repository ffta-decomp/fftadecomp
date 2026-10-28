/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806F3C8.c
 * Original SHA-256: ede2376a7ba15092000da4379b7452ace37ac501a44e432f3293cd5b74bcc7f3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s8 x;
    s8 y;
    u8 active;
    u8 unknown_03;
    u16 item;
} State0806F3C8;

extern u16 func_080CA7A4(u16, u8);
extern void func_0806F568(s16, s16, u8, u16);

/* Complete [0x0806F3C8, 0x0806F46C): 164 bytes, 76 instructions. */
void func_0806F3C8(State0806F3C8 *state)
{
    if (state->active) {
        func_0806F568(state->x * 8 + 48, state->y * 8, 1,
                      func_080CA7A4(state->item, 16));
        func_0806F568(state->x * 8 + 48, state->y * 8 + 12, 1,
                      func_080CA7A4(state->item, 17));
        func_0806F568(state->x * 8 + 96, state->y * 8 + 12, 2,
                      func_080CA7A4(state->item, 15));
    }
}
