/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C5774.c
 * Original SHA-256: 553820629a1e2c71ebb8a20cf0103870efd18be3fa9ae48cf62e46f333ad9d0c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080C5774..0x080C586C: 248 bytes, including literal pools. */
typedef struct {
    u8 unknown_00[0x1C];
} Transfer;

typedef struct {
    u8 frame;
    u8 flags;
    u8 index;
    u8 unknown_03[9];
    s16 timer;
    u16 unknown_0E;
    Transfer first;
    Transfer second;
    u16 state;
} Animation;

extern u8 data_030028A0;
typedef struct {
    u16 first;
    u16 second;
} TilePair;

extern const TilePair data_0839471C[];
extern const TilePair data_08394734[];
extern const u8 data_084199E0[][32];
extern u8 data_06013800[];
extern u8 data_06013840[];

extern void func_08000A98(Transfer *transfer, const void *source,
                          void *destination, u32 size);

void func_080C5774(Animation *animation)
{
    switch (animation->state) {
    case 1: {
        s32 index = animation->index - 4;
        if (data_030028A0 & 8) {
            func_08000A98(&animation->first,
                          data_084199E0[data_0839471C[index].first],
                          data_06013800, 32);
            func_08000A98(&animation->second,
                          data_084199E0[data_0839471C[index].second],
                          data_06013840, 32);
        } else {
            func_08000A98(&animation->first,
                          data_084199E0[data_08394734[index].first],
                          data_06013800, 32);
            func_08000A98(&animation->second,
                          data_084199E0[data_08394734[index].second],
                          data_06013840, 32);
        }
        animation->flags |= 8;
        animation->state = 2;
        break;
    }
    case 2: {
        if (animation->flags & 8) {
            animation->flags |= 2;
            animation->flags &= ~8;
            animation->flags |= 1;
        }
        if (animation->timer <= 3) {
            animation->timer++;
        } else {
            animation->timer = 0;
            animation->frame++;
            if (animation->frame > 3)
                animation->frame = 0;
        }
        break;
    }
    }
}
