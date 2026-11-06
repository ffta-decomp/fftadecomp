/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080401F4.c
 * Original SHA-256: cca7221465f8668d798e0a86c21f1a900e6305a85bae728c634a554d21ba2bef
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* Complete 0x080401F4..0x08040264, 112 bytes, 51 instructions.
 * Target: f0b557464e464546e0b4061c09040c0cd7f7a4fc4004717d8846b768050c002d1dd0c146114b9a46f17d4900201c02f195fb0004040c414661434900f0684018391c4a4653461a4001f116fbb07f40003f18013d601c0004040c002de4d138bc9846a146aa46f0bc01bc0047ffff1f00
 */
typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *source;
    u8 unknown_10[5];
    u8 width;
    u8 value;
    u8 columns;
    s16 limit;
    u8 unknown_1A[4];
    u8 stride;
} CopyState;

/* Conditional ordinary ABI views from complete root and helper entries. */
extern u16 func_08017B50(CopyState *state);
extern s32 func_08142950(s32 dividend, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_080401F4(CopyState *state, u16 index)
{
    u16 rows = func_08017B50(state) * 2;
    s32 width = state->width;
    u16 *destination = state->destination;
    s32 count = rows;

    while (count) {
        index = func_08142950(index, state->columns * 2);
        func_0814186C(state->source + index * width,
            destination, ((u32)(width * 2) >> 1) & 0x001FFFFF);
        destination += state->stride;
        count--;
        index++;
    }
}
