/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813E030.c
 * Original SHA-256: cdfc77994c9109332b033dd66ee63abb069cdf08e729ad490441c8fa8905df75
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0813E030, 0x0813E1DC), 428 bytes. */
typedef struct {
    u16 image_index;
    u16 duration;
} Frame0813E030;

typedef struct {
    u16 count;
    u16 unknown_02;
    const Frame0813E030 *frames;
} Track0813E030;

typedef struct {
    const u32 *resource;
    u32 unknown_04;
    Track0813E030 tracks[10];
    u16 count;
    u16 timers[10];
    u16 frame_indices[10];
    u8 finished[10];
    u8 playback_mode;
} Animation0813E030;

extern void func_08001CF0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);
extern void func_08001E18(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);

void func_0813E030(Animation0813E030 *animation, s16 x, s16 y,
                   u8 priority, u16 tile_base, u8 palette, u8 draw_mode,
                   u8 flags)
{
    const u32 *resource;
    const void *image;
    u8 i;

    for (i = 0; i < animation->count; i++) {
        if (animation->playback_mode == 3 && animation->finished[i])
            continue;

        resource = animation->resource;
        image = (const u8 *)resource +
            resource[animation->tracks[i].frames[
                animation->frame_indices[i]].image_index];
        switch (draw_mode) {
        case 0:
            func_08001CF0(image, x, y, priority, 0, 0, 0, 0,
                          tile_base, palette, flags);
            break;
        case 1:
            func_08001E18(image, x, y, priority, 0, 0, 0, 0,
                          tile_base, palette, flags);
            break;
        case 2:
            func_08001F34(image, x, y, priority, 0, 0, 0, 0,
                          tile_base, palette, flags);
            break;
        }
    }

    if (animation->playback_mode != 1) {
        for (i = 0; i < animation->count; i++) {
            animation->timers[i]++;
            if (animation->tracks[i].frames[animation->frame_indices[i]].duration <
                animation->timers[i]) {
                animation->timers[i] = 0;
                animation->frame_indices[i]++;
                if (animation->frame_indices[i] >= animation->tracks[i].count) {
                    if (animation->playback_mode == 0)
                        animation->frame_indices[i] = 0;
                    else {
                        animation->frame_indices[i] =
                            animation->tracks[i].count - 1;
                        animation->finished[i] = 1;
                    }
                }
            }
        }
    }
}
