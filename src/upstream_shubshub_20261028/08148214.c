/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148214.c
 * Original SHA-256: 6fe201f4536f672126f14c1be3a76ea8f5c054fc93fce242d056da4af883de87
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_081483EC(u16 value, u16 first, u16 second, u16 third);

/* Complete [0x08148214, 0x08148272): 94 bytes, 46 instructions. */
void func_08148214(const u16 *source, u16 *destination, u16 count,
                   u16 first, u16 second, u16 third)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_081483EC(source[index], first, second, third);
}
