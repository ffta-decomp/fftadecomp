/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011EA4.c
 * Original SHA-256: 7866cc923ce2d926b64d3019201fabc96b70bfb3db53714331bfd24b03f3968a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 *data_0200918C;
extern u8 func_08017180(u8 *region);

/* 08011EA4..08011EBC: 24 bytes. */
u8 func_08011EA4(void)
{
    return func_08017180(data_0200918C + 0x44);
}
