/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148274.c
 * Original SHA-256: 207aa7d546e477cef48401bc913d9a8c29abe002824c34e9808492370f8a87fe
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode);

/* Complete [0x08148274, 0x081482D2): 94 bytes, 46 instructions. */
void func_08148274(const u16 *source, u16 *destination, u16 count,
                  u16 reference, u8 amount, u8 mode)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_08147830(source[index], reference, amount, mode);
}
