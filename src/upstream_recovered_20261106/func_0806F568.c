/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0806F568.c
 * Original SHA-256: 2597c6538055afb6fd2edd366587065cdd7362041e3a112f1f14516c7e569591
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

extern const u8 data_08393B4C[];
extern u32 func_08142B28(u32, u32);
extern u32 func_08142AB0(u32, u32);
extern void func_08001F34(const void *, s32, s32, u8,
                         u8, u8, u8, u8, u32, u8, const void *);

/* Complete [0x0806F568, 0x0806F5FC): 148 bytes, 68 instructions.
 * Addressed unsigned calls use the conditional structural native ABI only. */
void func_0806F568(u16 x, u16 y, u8 places, u16 number)
{
    u8 index;
    for (index = 0; index < places; index++) {
        s32 column;
        u16 digit = func_08142B28(number, 10);
        number = func_08142AB0(number, 10);
        column = places - 1;
        column -= index;
        func_08001F34(data_08393B4C,
                     (s16)x + column * 8, (s16)y,
                     0, 0, 0, 0, 0, digit * 2, 0, 0);
        if (number == 0)
            break;
    }
}
