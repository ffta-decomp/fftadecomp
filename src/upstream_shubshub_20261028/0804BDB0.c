/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804BDB0.c
 * Original SHA-256: 831ca86ad9ea7ad366f5127902d2c2e262e44f0110e4beba6c56b54b6b3a16e9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete target: 0x0804BDB0..0x0804BDC4, 20 bytes. */
u8 func_0804BDB0(u8 first, u8 second)
{
    u8 result = 0;

    if (first > second)
        result = 1;
    return result;
}
