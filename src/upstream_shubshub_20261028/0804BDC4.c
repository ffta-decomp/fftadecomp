/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804BDC4.c
 * Original SHA-256: 12fcd74035ae6e138d059b565d2fb55e78fa495a46ac9b8cd4016c5a7d093be8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete target: 0x0804BDC4..0x0804BDDA, 22 bytes. */
u8 func_0804BDC4(u8 first, u8 second)
{
    return first < second ? first : second;
}
