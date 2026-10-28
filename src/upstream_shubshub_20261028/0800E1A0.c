/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800E1A0.c
 * Original SHA-256: bae7a1825fb3baf0d9a77786e1011c55b2cbffd7f43d118a20eafcb194510e1f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} Range;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    Range ranges[160];
    const u8 *data;
    u16 frame;
    u16 unknown_28E;
    u8 unknown_290[1];
} State;

void func_0800F480(const u8 *data, u32 width, s32 x, s32 y,
                  Range *ranges, u32 mode, const void *extra);
void func_0800F308(const u8 *data, u32 width, s32 x, s32 y,
                  Range *ranges, u32 mode);

typedef struct __attribute__((packed)) {
    u16 width;
    s16 frame_count;
} FrameHeader;

/* Complete target: [0x0800E1A0, 0x0800E268), 200 bytes. */
void func_0800E1A0(State *state)
{
    u16 start = 245;
    u16 end = 250;
    Range *range = state->ranges;
    s32 i;
    const u8 *data;
    s16 frame_count;
    u32 width;
    const u8 *frame_data;

    for (i = 159; i >= 0; i--) {
        range->start = start;
        range->end = end;
        range++;
    }

    data = state->data;
    frame_count = ((const FrameHeader *)data)->frame_count;
    width = ((const FrameHeader *)data)->width;
    frame_data = data + 4;
    frame_data += state->frame * width * 4;
    if (state->flags & 4) {
        func_0800F480(frame_data, width, state->x, state->y,
                      state->ranges, 1, state->unknown_290);
    } else {
        func_0800F308(frame_data, width, state->x, state->y,
                      state->ranges, 1);
    }

    state->frame++;
    if (state->frame == frame_count) {
        if (state->flags & 2) {
            state->frame = 0;
        } else {
            state->frame--;
            state->flags |= 0x8000;
        }
    }
}
