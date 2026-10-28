/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08090214.c
 * Original SHA-256: 1d492d8b97685a5945e505f8423ddf043da20508d103c32757af93395c70f412
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 limit;
    s16 position;
    u8 unknown_0A[2];
    u16 state;
} Animation08090214;

extern void func_080901A8(Animation08090214 *animation);

/* 0x08090214..0x08090264: 80 bytes, 38 instructions. */
s32 func_08090214(Animation08090214 *animation)
{
    switch (animation->state) {
    case 1:
        animation->position++;
        func_080901A8(animation);
        if (animation->position >= animation->limit) {
            animation->state = 0;
        }
        break;
    case 2:
        animation->position--;
        if (animation->position <= 0) {
            animation->state = 0;
            animation->position = 0;
        }
        func_080901A8(animation);
        break;
    default:
        return 0;
    }
    return 1;
}
