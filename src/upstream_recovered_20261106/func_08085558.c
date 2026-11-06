/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08085558.c
 * Original SHA-256: 6c01fc226454c349ad17c348a2c0c9a5cb2c00f0991a2e261e13738c12af9f17
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *unknown_08;
    u16 *unknown_0C;
    u8 unknown_10[5];
    u8 unknown_15;
    u8 unknown_16;
    u8 unknown_17;
    s16 unknown_18;
    u8 unknown_1A[4];
    u8 unknown_1E;
} State08085558;

extern u16 func_08017B50(State08085558 *state);
extern s32 func_08142950(s32 first, s32 second);
extern void func_0814186C(const void *source, void *destination, u32 count);

/* Complete target [0x08085558, 0x080855C8), 112 bytes:
 * f0b557464e464546e0b4061c09040c0c92f7f2fa4004717d8846b768050c002d1dd0c146114b9a46f17d4900201cbdf0e3f90004040c414661434900f0684018391c4a4653461a40bcf064f9b07f40003f18013d601c0004040c002de4d138bc9846a146aa46f0bc01bc0047ffff1f00
 */
void func_08085558(State08085558 *state, u16 index)
{
    u16 rows = func_08017B50(state) * 2;
    int width = state->unknown_15;
    u16 *destination = state->unknown_08;
    u32 remaining = rows;

    while (remaining != 0) {
        index = (u16)func_08142950(index, state->unknown_17 * 2);
        func_0814186C(state->unknown_0C + width * index,
                      destination, ((u32)(width * sizeof(u16)) >> 1) & 0x001FFFFF);
        destination += state->unknown_1E;
        remaining--;
        index++;
    }
}
