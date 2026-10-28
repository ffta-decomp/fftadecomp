/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DDB4.c
 * Original SHA-256: d1fecf3aedc72bc3a0c638044f90ef2406323d57b7ddad376913a854a71d2d16
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801DDB4..0x0801DE20: 108 bytes. */
struct Parameters0801DDB4 {
    u8 value0;
    u8 value1;
    u8 value2;
    u8 unknown_03;
};

struct State0801DDB4 {
    struct Parameters0801DDB4 first;
    struct Parameters0801DDB4 second;
    u8 current[2];
    u8 active[2];
    u16 counters[2];
};

struct Control0801DDB4 {
    u8 unknown_00[0x2C];
    u16 flags;
};

extern struct State0801DDB4 data_02008158;
extern struct Parameters0801DDB4 data_0200815C;
extern struct Control0801DDB4 g_state_02007F40;

void func_0801DDB4(u8 mode, u8 value0, u8 value1, u8 value2)
{
    int changed = 0;
    struct State0801DDB4 *state = &data_02008158;

    if (mode == 1 || mode == 3) {
        state->first.value0 = value0;
        state->first.value1 = value1;
        state->first.value2 = value2;
        state->current[0] = value1;
        state->active[0] = 0;
        state->counters[0] = 0;
        changed = 1;
    }
    if (mode == 2 || mode == 3) {
        struct Parameters0801DDB4 *second = &data_0200815C;

        second->value0 = value0;
        second->value1 = value1;
        second->value2 = value2;
        state->current[1] = value1;
        state->active[1] = 0;
        state->counters[1] = 0;
        changed = 1;
    }
    if (changed)
        g_state_02007F40.flags |= 0x400;
}
