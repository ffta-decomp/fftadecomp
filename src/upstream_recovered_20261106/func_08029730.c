/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08029730.c
 * Original SHA-256: dc0ef1440f35e982b275de38820bf4f00e62123bf2e0251af9c32e138fdcedd5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

extern u32 func_08142AB0(u32, u32);
extern u32 func_08142B28(u32, u32);

/* Complete 08029730..0802979A: 106 bytes, 49 instructions. */
void func_08029730(u16 *buffer, u8 width, u16 value)
{
    s8 index;

    for (index = width - 1; index >= 0; --index) {
        u32 byte_offset = index * 2;
        u16 *digit = (u16 *)(byte_offset + (u32)buffer);
        s32 tile = func_08142B28(value, 10) + 30;
        *digit = tile | -0x4000;
        value = func_08142AB0(value, 10);
        if (value == 0) {
            for (--index; index >= 0; --index)
                buffer[index] = 0;
            break;
        }
    }
}
