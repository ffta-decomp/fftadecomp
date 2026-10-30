/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0813EAD4.c
 * Original SHA-256: 77310c40d0e01364a53b2d7c9c9eb6b71be54e1dcff28d99f0a47f1dee63b67a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PaletteTransition PaletteTransition;

typedef struct {
    PaletteTransition *transition;
    u8 active;
    u8 palette;
    u8 direction;
    u8 unknown_07;
    u16 elapsed;
    u16 duration;
    u16 first[16];
    u16 second[16];
} PaletteState;

extern u32 func_0814846C(const PaletteTransition *transition);
extern void func_08148498(PaletteTransition *transition);
extern PaletteTransition *func_08147D2C(u16 first, u16 count, u16 duration,
                                       const u16 *colors);
extern void func_081486C8(PaletteTransition *transition, u8 enabled, u8 flag40);

/* 0x0813EAD4..0x0813EB64: 144 bytes, 62 instructions. */
void func_0813EAD4(PaletteState *state)
{
    if (state->active && func_0814846C(state->transition)) {
        if (state->elapsed > state->duration) {
            func_08148498(state->transition);
            state->direction = state->direction != 1;
            if (state->direction) {
                state->transition = func_08147D2C(
                    (u16)(0x101 + state->palette * 16), 10,
                    state->duration / 2, &state->second[1]);
            } else {
                state->transition = func_08147D2C(
                    (u16)(0x101 + state->palette * 16), 10,
                    state->duration / 2, &state->first[1]);
            }
            func_081486C8(state->transition, 1, 0);
            func_081486C8(state->transition, 1, 1);
            state->elapsed = 0;
        }
        state->elapsed++;
    }
}
