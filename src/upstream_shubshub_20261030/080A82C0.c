/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080A82C0.c
 * Original SHA-256: 41d3b6fe6d71a6a3eb23c4249f462defb4641bee6cf9ca043d78442edcb1d943
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

extern u8 g_state_02000000[];
extern u8 data_0200F8A8[];
extern s32 func_080A1BE8(void *context, u16 held, u16 pressed);

/* Complete [0x080A82C0, 0x080A8390): 208 bytes, 97 instructions. */
s32 func_080A82C0(u16 held, u16 pressed)
{
    u16 remapped_held;
    u16 remapped_pressed;

    if (g_state_02000000[0x2FC0] & 1) {
        remapped_held = held & 0xFF0F;
        if (held & 0x10)
            remapped_held |= 0x40;
        if (held & 0x40)
            remapped_held |= 0x20;
        if (held & 0x20)
            remapped_held |= 0x80;
        if (held & 0x80)
            remapped_held |= 0x10;
        held = remapped_held;

        remapped_pressed = pressed & 0xFF0F;
        if (pressed & 0x10)
            remapped_pressed |= 0x40;
        if (pressed & 0x40)
            remapped_pressed |= 0x20;
        if (pressed & 0x20)
            remapped_pressed |= 0x80;
        if (pressed & 0x80)
            remapped_pressed |= 0x10;
        pressed = remapped_pressed;
    }
    return func_080A1BE8(data_0200F8A8, held, pressed);
}
