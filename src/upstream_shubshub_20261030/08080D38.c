/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08080D38.c
 * Original SHA-256: e3762db6df12912a7d29b03f01efc296defd67b551d851130a4392e359490c20
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xd6];
    u16 value;
} DisplayValue08080D38;

extern u16 *func_0808B8E4(u32 window, u32 plane, s32 x, s32 y);

/* Complete target [0x08080D38, 0x08080D74): 60 bytes, 25 instructions. */
u32 func_08080D38(const DisplayValue08080D38 *object)
{
    u32 result;

    if (object->value < 10) {
        *func_0808B8E4(2, 1, 26, 5) = 0;
        result = 0;
    } else {
        *func_0808B8E4(2, 1, 26, 5) = 0xd090;
        result = 1;
    }
    return result;
}
