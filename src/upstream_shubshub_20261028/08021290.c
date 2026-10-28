/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08021290.c
 * Original SHA-256: 64f32b477093977ec83ed3b5a13730dc2358e36afcc7bccab54a8ce22f85cde8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00[2];
    u8 duration;
    u8 unknown_09[0xB];
} AnimationFrame;

typedef struct {
    u32 flags;
    u8 unknown_04[6];
    s16 timer;
    s16 frame_index;
    s16 frame_count;
    u8 unknown_10;
    s8 half_speed_timer;
    u8 unknown_12[0xC];
    u8 changed;
    u8 unknown_1F[0x15];
    const AnimationFrame *first_frame;
    const AnimationFrame *current_frame;
} Animation;

void func_080210E4(Animation *animation, void *context);

/* Complete target: [0x08021290, 0x08021378), 232 bytes. */
void func_08021290(Animation *animation, void *context)
{
    if (animation->flags & 0x20000) {
        animation->flags = (animation->flags & ~0x20080) | 0x90000;
    }
    animation->changed = 0;
    if ((animation->flags & 1) && animation->current_frame != 0) {
        if (!(animation->flags & 0x100)) {
            if (animation->flags & 0x1000) {
                animation->timer--;
            }
            if (animation->flags & 0x4000) {
                animation->half_speed_timer--;
                if (animation->half_speed_timer <= 0) {
                    animation->timer--;
                    animation->half_speed_timer = 2;
                }
            } else {
                animation->timer--;
            }
            if (animation->flags & 0x2000) {
                animation->timer = 0;
            }
        }
        if (animation->timer <= 0) {
            if (animation->frame_index >= animation->frame_count) {
                animation->timer = 0;
                if (!(animation->flags & 2)) {
                    return;
                }
                animation->current_frame = animation->first_frame;
                animation->frame_index = 0;
            }
            animation->timer = animation->current_frame->duration;
            func_080210E4(animation, context);
            if (animation->timer != 0) {
                animation->frame_index++;
                if (animation->frame_index >= animation->frame_count) {
                    animation->frame_index = animation->frame_count;
                } else {
                    animation->current_frame++;
                }
            }
        }
    }
}
