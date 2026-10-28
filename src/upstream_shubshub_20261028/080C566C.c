/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C566C.c
 * Original SHA-256: d025aee2206669c6dad8b3c5a43889eba84d9acfe5054f4a1283a22dc0ef8bfd
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
} Animation080C566C;

extern const u8 data_08419C60[];
extern u8 data_06013800[];
extern void func_08000A98(void *sprite, const void *image, void *destination,
                         u16 count);

/* Complete [0x080C566C, 0x080C56E8): 124 bytes, 57 instructions. */
void func_080C566C(Animation080C566C *animation)
{
    switch (animation->state) {
    case 1:
        func_08000A98(animation->sprite, data_08419C60, data_06013800, 0x40);
        animation->flags |= 8;
        animation->state = 2;
        break;
    case 2:
        if (animation->flags & 8) {
            animation->flags |= 2;
            animation->flags &= ~8;
            animation->flags |= 1;
        }
        if (animation->ticks < 6) {
            animation->ticks++;
        } else {
            animation->ticks = 0;
            if (++animation->frame > 3)
                animation->frame = 0;
        }
        break;
    }
}
