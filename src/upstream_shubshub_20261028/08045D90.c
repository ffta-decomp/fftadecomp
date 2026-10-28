/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08045D90.c
 * Original SHA-256: 97b68a388e213aab5f4dd72d6574f55e17880f4599b84795d81bb548a03e0afb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: 100 bytes / 45 instructions, 0x08045D90..0x08045DF4. */
typedef struct {
    u8 id;
    u8 unknown_01[0x23];
    u16 flags;
    u8 unknown_26[0xE2];
} Unit;

typedef struct {
    u8 unknown_00[0x84];
    Unit units[24];
} GameState;

extern GameState g_state_02000000;

s32 func_08045D90(u8 *output, s32 *special)
{
    s32 count = 0;
    s32 i;
    GameState *state;

    *special = -1;
    i = 0;
    state = &g_state_02000000;
    for (; i < 24; ++i) {
        if (!(state->units[i].flags & 0x18)) {
            if (state->units[i].flags & 0x80) {
                output[count] = i;
                ++count;
                if (state->units[i].id == 2 || state->units[i].id == 15)
                    *special = i;
            }
        }
        state->units[i].flags &= ~0x80;
    }
    return count;
}
