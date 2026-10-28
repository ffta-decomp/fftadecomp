/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813E9F4.c
 * Original SHA-256: a4a501f10ab7d51bb55b819baf0b517dd619e3b96b7e966d44214ab0c7addd9e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} PaletteTransition;

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

extern u16 data_03003A60[][16];
extern void func_0814186C(const void *source, void *destination, u32 count);
extern PaletteTransition *func_08147D2C(u16 first, u16 count, u16 duration, const u16 *colors);
extern void func_081486C8(PaletteTransition *transition, u8 enabled, u8 flag40);

/* Complete target: [0x0813E9F4, 0x0813EAD4), 224 bytes. */
void func_0813E9F4(PaletteState *state, u8 palette,
                   const u16 *first, const u16 *second, u16 duration, u8 direction)
{
    state->active = 1;
    state->palette = palette;
    state->duration = duration;
    func_0814186C(first, state->first, 16);
    func_0814186C(second, state->second, 16);
    state->direction = direction;
    state->elapsed = 0;
    if (direction) {
        func_0814186C(state->first, data_03003A60[palette], 16);
        state->transition = func_08147D2C((u16)(0x101 + palette * 16), 10,
                                         state->duration / 2, &state->second[1]);
        func_081486C8(state->transition, 1, 0);
        func_081486C8(state->transition, 1, 1);
    } else {
        func_0814186C(state->second, data_03003A60[palette], 16);
        state->transition = func_08147D2C((u16)(0x101 + palette * 16), 10,
                                         state->duration / 2, &state->first[1]);
        func_081486C8(state->transition, 1, 0);
        func_081486C8(state->transition, 1, 1);
    }
}
