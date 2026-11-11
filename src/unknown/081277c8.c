/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 1a8ef98ec0da7580594f2600c08727d82376610c
 * Original file: src/081277C8.c
 * Original SHA-256: 82ab950c6990c6eb905b19278dd5e23e958b34d18f50745ccbd04fd2630382a2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef signed long long s64;

typedef struct {
    u8 unknown_00[0x0A];
    s16 height;
    u8 unknown_0C[0x2A];
    u16 value_36;
} Output081277C8;

typedef struct {
    u32 unknown_00;
    Output081277C8 *output;
    u8 unknown_08[6];
    s8 value_0E;
    u8 mode;
    u8 unknown_10[0x38];
    s64 step;
    s64 position;
    s64 limit;
    s64 controls[3];
    u8 unknown_78[8];
    s64 points[3];
    u8 unknown_98[8];
    u8 coefficients[0x20];
    u16 frames[0];
} State081277C8;

extern void func_0809836C(void *, u16, s8, u16);
extern s32 func_08127380(State081277C8 *);
extern void func_0809A570(void *, u32, u32);
extern void func_0809A530(void *, u32);
extern u8 *func_08121B64(u32);
extern void func_08121B78(u8 *);
extern void func_08008480(u32, s64 *, s64 *, void *, void *);
extern s64 func_080086D0(s64, u32, s64 *, s64 *, void *);
extern u32 func_08127C94(State081277C8 *);

/* Complete [0x081277C8, 0x08127990): 456 bytes, 205 instructions. */
void func_081277C8(State081277C8 *state, s32 height)
{
    s32 mode;
    u8 *scratch;
    u32 index;

    if (state->output->value_36 != 4)
        func_0809836C(state->output, 1, state->value_0E, 0);
    mode = func_08127380(state);
    if (mode != state->mode)
        state->mode = mode;
    func_0809A570(state->output, 0, 0x100);
    switch (state->mode) {
    case 0:
    case 1:
        state->mode = 2;
        break;
    case 2:
    case 3:
        state->mode = 0;
        break;
    }
    func_0809A530(state->output, state->mode);
    state->controls[0] = 0;
    state->controls[1] = 0x100000;
    state->controls[2] = 0x200000;
    state->points[0] = (s64)state->output->height << 16;
    if (state->step > 0x10000) {
        if (state->output->height < height)
            state->points[1] = (s64)(height + 8) << 16;
        else
            state->points[1] = (s64)(state->output->height + 8) << 16;
    } else {
        if (state->output->height > height)
            state->points[1] = (s64)state->output->height << 16;
        else
            state->points[1] = (s64)height << 16;
    }
    state->points[2] = (s64)(height + 8) << 16;
    scratch = func_08121B64(0x40);
    func_08008480(3, state->controls, state->points, state->coefficients, scratch);
    state->position = 0;
    state->limit = 0x200000;
    index = 0;
    for (;;) {
        state->frames[index] = func_080086D0(state->position, 3, state->controls,
                               state->points, state->coefficients) >> 16;
        index++;
        state->position += state->step;
        if (state->position >= state->limit)
            break;
    }
    func_08121B78(scratch);
    state->position = 0;
    func_08127C94(state);
}
