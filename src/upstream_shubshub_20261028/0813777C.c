/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813777C.c
 * Original SHA-256: bf23520562ddba459a7f6d0e3b72cb3fe19fdc50bb71d8d728f49506843c6c59
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0813777C, 0x0813785C): 224 bytes, 92 instructions. */
typedef struct {
    void *effect;
    u8 active;
    u8 palette;
    u8 forward;
    u8 unknown_07;
    u16 elapsed;
    u16 duration;
    u16 first[16];
    u16 second[16];
} PaletteTransition0813777C;

extern u16 data_03003A60[];
extern void func_0814186C(const void *, void *, u32);
extern void *func_08147D2C(u16, u32, u32, const void *);
extern void func_081486C8(void *, u8, u8);

void func_0813777C(PaletteTransition0813777C *state, u8 palette,
                   const u16 *first, const u16 *second, u16 duration,
                   u8 forward)
{
    state->active = 1;
    state->palette = palette;
    state->duration = duration;
    func_0814186C(first, state->first, 16);
    func_0814186C(second, state->second, 16);
    state->forward = forward;
    state->elapsed = 0;
    if (forward) {
        func_0814186C(state->first, &data_03003A60[palette * 16], 16);
        state->effect = func_08147D2C(palette * 16 + 0x101, 7,
                                     state->duration / 2, &state->second[1]);
        func_081486C8(state->effect, 1, 0);
        func_081486C8(state->effect, 1, 1);
    } else {
        func_0814186C(state->second, &data_03003A60[palette * 16], 16);
        state->effect = func_08147D2C(palette * 16 + 0x101, 7,
                                     state->duration / 2, &state->first[1]);
        func_081486C8(state->effect, 1, 0);
        func_081486C8(state->effect, 1, 1);
    }
}
