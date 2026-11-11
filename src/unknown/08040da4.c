/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08040DA4.c
 * Original SHA-256: 29695c0e9ed322639116add319b06b3a308fa4de8215de3c5941511603a11082
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    const u16 *source;
    u8 unknown_10[5];
    u8 width;
    u8 value_16;
    u8 factor;
    s16 limit;
    u16 frame;
    u8 unknown_1C[2];
    u8 step;
} AnimationState;

extern u16 func_08017B50(AnimationState *state);
extern s32 func_08142950(s32 value, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Target [0x08040DA4, 0x08040E14), 112 bytes:
 * f0b557464e464546e0b4061c09040c0cd6f7ccfe4004717d8846b768050c002d1dd0
 * c146114b9a46f17d4900201c01f1bdfd0004040c414661434900f0684018391c4a46
 * 53461a4000f13efdb07f40003f18013d601c0004040c002de4d138bc9846a146aa46
 * f0bc01bc0047ffff1f00
 */
void func_08040DA4(AnimationState *state, u16 frame)
{
    u16 count = func_08017B50(state) * 2;
    s32 width = state->width;
    u16 *destination = state->destination;
    s32 rows = count;

    if (rows != 0) {
        u32 copyHalfwords = width;

        do {
        frame = func_08142950(frame, state->factor * 2);
        func_0814186C(state->source + width * frame, destination,
                      copyHalfwords & 0x1FFFFF);
        destination += state->step;
        rows--;
        frame++;
        } while (rows != 0);
    }
}
