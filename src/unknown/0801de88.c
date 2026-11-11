/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0801DE88.c
 * Original SHA-256: c9e8311f2c4c4e9a8173c819d00d2bae29b508f5910c7f355f85b5ab4517d28f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* 0x0801DE88..0x0801DF8C: 260 bytes. */
struct Parameters0801DE88 {
    u8 value0;
    u8 value1;
    u8 value2;
    u8 unknown_03;
};

struct State0801DE88 {
    struct Parameters0801DE88 first;
    struct Parameters0801DE88 second;
    u8 current[2];
    u8 active[2];
    s16 counters[2];
};

struct Second0801DE88 {
    struct Parameters0801DE88 parameters;
    u8 unknown_04[6];
    s16 counter;
};

struct Control0801DE88 {
    u8 unknown_00[0x2C];
    u16 flags;
    u8 unknown_2E[0x1F6];
    s16 x;
    s16 y;
};

extern struct State0801DE88 data_02008158;
extern struct Second0801DE88 data_0200815C;
extern struct Control0801DE88 g_state_02007F40;
extern s16 func_08002804(void);

void func_0801DE88(void)
{
    struct State0801DE88 *state = &data_02008158;
    struct Parameters0801DE88 *first = &state->first;
    struct Second0801DE88 *second;

    if (first->value0 != 0 && --state->current[0] == 0) {
        if (state->active[0] == 0) {
            state->active[0] = 1;
            state->counters[0] = -first->value0;
        } else {
            state->active[0] = 0;
            state->counters[0] = first->value0;
        }
        if (first->value2 != 0) {
            int range = first->value2 * 2;
            u16 value = func_08002804() % (range + 1);
            s16 delta = value - first->value2;
            g_state_02007F40.x += delta;
        }
        state->current[0] = first->value1;
        g_state_02007F40.flags |= 0x200;
    }
    second = &data_0200815C;
    if (second->parameters.value0 != 0 && --state->current[1] == 0) {
        if (state->active[1] == 0) {
            state->active[1] = 1;
            second->counter = -second->parameters.value0;
        } else {
            state->active[1] = 0;
            second->counter = second->parameters.value0;
        }
        if (second->parameters.value2 != 0) {
            int range = second->parameters.value2 * 2;
            u16 value = func_08002804() % (range + 1);
            s16 delta = value - second->parameters.value2;
            g_state_02007F40.y += delta;
        }
        state->current[1] = second->parameters.value1;
        g_state_02007F40.flags |= 0x200;
    }
}
