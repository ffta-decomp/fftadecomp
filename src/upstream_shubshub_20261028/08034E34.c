/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08034E34.c
 * Original SHA-256: c72a0228751ae5c1702bca45901df36acd6cb4b9889cc951d1a924c07c5eb11f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 mode : 3;
    u8 active : 1;
    u8 next : 3;
    u8 unknown : 1;
} __attribute__((packed)) AnimationFlags;

typedef struct {
    u8 unknown_00[0x9A];
    AnimationFlags first;
    u8 unknown_9B[0x32];
    s8 first_position;
    u8 unknown_CE[0x18];
    AnimationFlags second;
    u8 unknown_E7[0x32];
    s8 second_position;
} AnimationState;

extern AnimationState data_030009E0;

/* 08034E34..08034E88: 84 bytes, 38 reachable instructions. */
void func_08034E34(void)
{
    data_030009E0.first_position = 17;
    data_030009E0.second_position = 18;
    data_030009E0.first.active = 0;
    data_030009E0.first.next = 5;
    data_030009E0.first.mode = 0;
    data_030009E0.second.active = 0;
    data_030009E0.second.next = 5;
    data_030009E0.second.mode = 0;
}
