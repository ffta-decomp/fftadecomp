/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A9C80.c
 * Original SHA-256: 00ee49a9a2b309c70769a5b04f39096b6c710c411885d9442e80501afd0f23e0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1e];
    u8 mode;
    u8 unknown_1f[0x21];
    void *position;
    void *animation;
} Owner080A9C80;

typedef struct {
    u8 unknown_00[0x58];
} Effect080A9C80;

typedef struct {
    Owner080A9C80 *owner;
    u8 unknown_04[0x20];
    s16 x[3];
    s16 y[3];
    s16 timers[3];
    u8 unknown_36[0xa];
    u8 flags;
    u8 unknown_41[3];
    Effect080A9C80 effects[2];
} State080A9C80;

extern void func_080A9BB8(Effect080A9C80 *effect);
extern void func_08021E64(void *animation, u8 mode);
extern void func_08021F18(void *position, s32 x, s32 y, s32 arg3,
                        s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                        s32 arg8, s32 arg9);

/* Complete [0x080A9C80, 0x080A9D16): 150 bytes, 72 instructions. */
void func_080A9C80(State080A9C80 *state)
{
    s32 i;

    if (state->flags & 2) {
        if (state->flags & 4) {
            for (i = 0; i < 2; i++)
                func_080A9BB8(&state->effects[i]);
        }
        for (i = 0; i < 3; i++) {
            if (state->timers[i] > 0) {
                state->timers[i]--;
                func_08021E64(state->owner->animation, state->owner->mode);
                func_08021F18(state->owner->position, state->x[i], state->y[i],
                              0, 0, 0, 0, 0, 0, 0);
            }
        }
    }
}
