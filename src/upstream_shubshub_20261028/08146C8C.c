/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08146C8C.c
 * Original SHA-256: 7712f739ad51ca05ce5b25da8405ee453eab2117503841a77adc72540f157990
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct PaletteState08146C8C {
    const u8 *data;
    u16 offset;
    u16 frame_count;
    u16 frames_remaining;
    u16 duration_index;
    u16 duration_count;
    u16 unknown_0e;
    const u16 *durations;
    u16 fixed_duration;
    u16 timer;
};

struct PaletteAnimation08146C8C {
    u16 active;
    u16 flags;
    u16 unknown_04;
    u16 first_color;
    u16 last_color;
    u16 unknown_0a;
    struct PaletteState08146C8C state;
};

extern u16 data_03003860[];

/* Target: [0x08146C8C, 0x08146D38), 172 bytes, 83 instructions. */
void func_08146C8C(struct PaletteAnimation08146C8C *animation)
{
    struct PaletteState08146C8C *state = &animation->state;
    const u8 *data = state->data;
    const u16 *colors = (const u16 *)(data + state->offset);

    if (--state->timer == 0) {
        u16 color = animation->first_color;
        u16 i = 0;
        u16 color_count;

        for (; color <= animation->last_color; color++, i++)
            data_03003860[color] = colors[i];
        color_count = animation->last_color - animation->first_color + 1;
        state->offset += color_count * 2;
        if (state->fixed_duration == 0) {
            state->duration_index++;
            if (state->duration_index >= state->duration_count)
                state->duration_index = 0;
            state->timer = state->durations[state->duration_index];
        } else {
            state->timer = state->fixed_duration;
        }
        state->frames_remaining--;
    }
    if (state->frames_remaining == 0) {
        if ((u16)(animation->flags & 4)) {
            state->frames_remaining = state->frame_count;
            state->offset = 0;
        } else {
            animation->active = 0;
        }
    }
}
