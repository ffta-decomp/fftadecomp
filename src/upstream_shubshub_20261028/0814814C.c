/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0814814C.c
 * Original SHA-256: 7cfbf205ed01378d33e6c00a3e01253dddf027ade893c355b4957db480254eee
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_08148384(u16 value, u16 first, u16 second, u16 third);

/* Complete [0x0814814C, 0x081481AA): 94 bytes, 46 instructions. */
void func_0814814C(const u16 *source, u16 *destination, u16 count,
                   u16 first, u16 second, u16 third)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_08148384(source[index], first, second, third);
}
