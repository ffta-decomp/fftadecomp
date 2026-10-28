/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C55D8.c
 * Original SHA-256: 1bb6646b31216abf3aebda8bfa68383305d5c7319091b76c5fb18cb891752310
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 frame;
    u8 flags;
    u8 unknown_02[0xA];
    s16 ticks;
    u8 unknown_0E[2];
    u8 sprite[0x38];
    u16 state;
} Animation;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
} AnimationContext;

extern AnimationContext data_030028A0;
extern const u8 data_08419BE0[];
extern u8 data_06013800[];
extern void func_08000A98(void *sprite, const void *image, void *destination,
                         u32 size);

void func_080C55D8(Animation *animation)
{
    switch (animation->state) {
    case 1:
        func_08000A98(animation->sprite, data_08419BE0, data_06013800, 0x40);
        animation->flags |= 8;
        animation->state = 2;
        break;
    case 2:
        if (animation->flags & 8) {
            animation->flags |= 2;
            animation->flags &= ~8;
            animation->flags |= 1;
        }
        if (data_030028A0.busy == 0 && data_030028A0.mode == 3) {
            if (animation->ticks <= 5) {
                animation->ticks++;
            } else {
                animation->ticks = 0;
                if (++animation->frame > 15)
                    animation->frame = 0;
            }
        }
        break;
    }
}
