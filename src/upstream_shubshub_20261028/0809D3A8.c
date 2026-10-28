/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809D3A8.c
 * Original SHA-256: 79166886b496fbc60f47b695d17e0ad534a02b64fa3227936bcb0d98a1edadde
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0809D3A8..0x0809D426: 126 bytes. */
typedef struct {
    u8 unknown_00[0x1F];
    s8 direction;
} DirectionUnit;

typedef struct {
    DirectionUnit *unit;
    u8 target;
    s8 delay;
    s8 ticks;
} TurnState;

u16 func_08002804(void);
s32 abs(s32 value);

u32 func_0809D3A8(TurnState *state)
{
    u32 target;
    s32 current;
    s32 difference;
    u16 random;

    if (state->target == state->unit->direction)
        return 0;

    ++state->ticks;
    if (state->ticks >= state->delay) {
        state->ticks = 0;
        target = state->target;
        current = state->unit->direction;
        difference = target - current;
        if (abs(difference) > 2)
            difference = 1;
        if (abs(difference) == 1) {
            state->unit->direction = target;
            return 0;
        }

        random = func_08002804();
        if (random & 1)
            difference = current - 1;
        else
            difference = current + 1;
        if (difference < 0)
            difference += 4;
        if (difference > 3)
            difference -= 4;
        state->unit->direction = difference;
    }
    return 1;
}
