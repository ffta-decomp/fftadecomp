/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C56E8.c
 * Original SHA-256: 9acd5c35cd24af66799e83703b84d5443406348c38e09f7b0b72f697bb1814a2
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

extern const u8 data_08419CE0[];
extern u8 data_06013800[];
extern void func_08000A98(void *sprite, const void *image, void *destination,
                         u32 size);
extern u8 func_080C72E4(void);

void func_080C56E8(Animation *animation)
{
    switch (animation->state) {
    case 1:
        func_08000A98(animation->sprite, data_08419CE0, data_06013800, 0x40);
        animation->flags |= 8;
        animation->state = 2;
        break;
    case 2:
        if (animation->flags & 8) {
            animation->flags |= 2;
            animation->flags &= ~8;
            animation->flags |= 1;
        }
        if (func_080C72E4()) {
            animation->ticks = 0;
            if (++animation->frame > 7)
                animation->frame = 0;
        } else {
            animation->ticks = 0;
            if (++animation->frame > 18)
                animation->frame = 0;
        }
        break;
    }
}
