/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08145608.c
 * Original SHA-256: 05d4ed013782a6113b86e90a170a6bb372a96f88edc8c83c569a1bf87eaa0feb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 rate_index;
    u8 unknown_09[2];
    u8 samples_per_tick;
    u8 unknown_0c[4];
    s32 rate;
    s32 sample_rate;
    s32 period;
} AudioState;

extern AudioState *data_03007FF0;
extern const u16 data_0836D20C[];
extern void func_081457FC(void);

/* Complete [0x08145608, 0x081456AC), 164 bytes. */
void func_08145608(u32 mode)
{
    AudioState *state = data_03007FF0;
    s32 rate;
    s32 sample_rate;

    mode = (mode & 0xf0000) >> 16;
    state->rate_index = mode;
    rate = data_0836D20C[mode - 1];
    state->rate = rate;
    state->samples_per_tick = 1584 / rate;
    sample_rate = (597275 * rate + 5000) / 10000;
    state->sample_rate = sample_rate;
    state->period = ((16777216 / sample_rate) + 1) >> 1;
    /* plausible: mapped timer control is a physical halfword register. */
    *(volatile u16 *)0x04000102 = 0;
    /* plausible: mapped timer reload is a physical halfword register. */
    *(volatile u16 *)0x04000100 = -(280896 / rate);
    func_081457FC();
    /* plausible: mapped VCOUNT at 0x04000006 must be polled as hardware. */
    while (*(volatile u8 *)0x04000006 == 159)
        ;
    /* plausible: mapped VCOUNT at 0x04000006 must be polled as hardware. */
    while (159 != *(volatile u8 *)0x04000006)
        ;
    /* plausible: mapped timer control is a physical halfword register. */
    *(volatile u16 *)0x04000102 = 0x80;
}
