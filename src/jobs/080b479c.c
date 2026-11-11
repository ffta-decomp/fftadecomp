/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080B479C.c
 * Original SHA-256: a8f58277bdaef2293e5f3cd1f7b03a1ae97af39e94b2a83290ddac6aea348769
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

struct Position080B479C {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown03;
};

extern u32 func_080C92F0(void *context, u32 selector);
extern u8 func_080B7C94(u16 action, u16 parameter, s32 mode);
extern s32 func_080A0014(void *context, u8 from_x, u8 from_y,
                       u8 to_x, u8 to_y, u16 action, u16 parameter, u8 flags);
extern s32 func_080A0254(void *context, u8 from_x, u8 from_y,
                       u8 to_x, u8 to_y, u16 action, u16 parameter, u8 flags);
extern u8 func_0801CC18(u8 x, u8 y);

static inline u8 range_080B479C(void *context, u16 action, u16 parameter, s32 mode)
{
    if (context && (func_080C92F0(context, 0x28) & 4)) {
        if (mode == 0)
            return 4;
        else
            return 1;
    }
    return func_080B7C94(action, parameter, mode);
}

/* Complete [0x080B479C, 0x080B48CC): 304 bytes, 147 instructions. */
s32 func_080B479C(void *context, s8 x, s8 y, s8 dx, s8 dy,
                  u16 action, u16 parameter, s32 mode,
                  struct Position080B479C *output)
{
    s32 range;
    s8 current_x;
    s8 current_y;
    s32 count;
    s32 i;

    range = range_080B479C(context, action, parameter, mode);
    current_x = x;
    current_y = y;
    count = 0;
    for (i = 0; i < range; i++) {
        s32 accepted;

        current_x = (s8)current_x + (s8)dx;
        current_y = (s8)current_y + (s8)dy;
        if (mode == 0)
            accepted = func_080A0014(context, x, y, current_x, current_y,
                                     action, parameter, 0);
        else
            accepted = func_080A0254(context, x, y, current_x, current_y,
                                     action, parameter, 0);

        if (accepted) {
            count++;
            output->x = current_x;
            output->height = func_0801CC18(current_x, current_y);
            output->y = current_y;
            output++;
        }
    }

    return count;
}
