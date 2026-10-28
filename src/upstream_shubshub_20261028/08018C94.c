/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018C94.c
 * Original SHA-256: edb15fc41bf351bf4a363185c889edcf77cecbc81fffb1749e98313c1308d54f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08018C94..08018CB6: 34 bytes. */
u16 func_08018C94(u8 *destination, u8 value)
{
    destination[0] = 0x40;
    destination[1] = 0x6C;
    if (value == 3)
        destination[2] = 3;
    else
        destination[2] = 0;
    return 3;
}
