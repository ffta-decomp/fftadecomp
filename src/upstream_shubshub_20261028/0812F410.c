/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812F410.c
 * Original SHA-256: 5cb8650cddf4aacc4aec66ffab55b1ecb03e7cf2d9e8dbba1fdcaf129cfad9bb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete 0x0812F410..0x0812F48A: 122 bytes, 53 instructions. */
extern s32 func_080C7EA4(void *actor, u16 attribute);
extern u8 func_080C95A8(u16 condition);
extern u8 func_080C8240(void *actor);
extern u8 func_080D2BF4(u16 modifier);

s32 func_0812F410(void *actor, u16 alternate)
{
    s16 value;

    if (alternate == 0) {
        value = func_080C7EA4(actor, 23);
        if (!func_080C95A8(13) && !func_080C8240(actor))
            value += value * func_080D2BF4(10) / 100;
    } else {
        value = func_080C7EA4(actor, 25);
        if (!func_080C95A8(13) && !func_080C8240(actor))
            value += value * func_080D2BF4(12) / 100;
    }
    return value;
}
