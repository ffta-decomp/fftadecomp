/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0813785C.c
 * Original SHA-256: 3e24ad4f662c29d904940440bc760b8075e4574962df21b5c30879027b7a3064
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct PaletteEffect0813785C PaletteEffect0813785C;

typedef struct {
    PaletteEffect0813785C *effect;
    u8 enabled;
    u8 palette;
    u8 alternate;
    u8 unknown_07;
    u16 timer;
    u16 period;
    u16 unknown_0C;
    u16 first_colors[16];
    u16 second_colors[16];
} PaletteCycle0813785C;

extern u32 func_0814846C(const PaletteEffect0813785C *effect);
extern void func_08148498(PaletteEffect0813785C *effect);
extern PaletteEffect0813785C *func_08147D2C(u16 first, u16 count,
                                           u16 duration, const u16 *colors);
extern void func_081486C8(PaletteEffect0813785C *effect, u8 enabled, u8 flag40);

/* 0x0813785C..0x081378EC - 144 bytes including literal pools. */
void func_0813785C(PaletteCycle0813785C *state)
{
    if (state->enabled != 0 && func_0814846C(state->effect) != 0) {
        if (state->timer > state->period) {
            func_08148498(state->effect);
            state->alternate = state->alternate != 1;
            if (state->alternate != 0) {
                state->effect = func_08147D2C((state->palette << 4) + 0x101,
                                              7, state->period >> 1,
                                              state->second_colors);
            } else {
                state->effect = func_08147D2C((state->palette << 4) + 0x101,
                                              7, state->period >> 1,
                                              state->first_colors);
            }
            func_081486C8(state->effect, 1, 0);
            func_081486C8(state->effect, 1, 1);
            state->timer = 0;
        }
        state->timer++;
    }
}
