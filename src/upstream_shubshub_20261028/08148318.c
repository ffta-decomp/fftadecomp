/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148318.c
 * Original SHA-256: 8c5adf752ab7efb1978927592503106cbef503b9fc4d75f767c2b9ebc282cd7c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_08147958(u16 color, u8 amount);

/* Complete [0x08148318, 0x0814835A): 66 bytes, 32 instructions. */
void func_08148318(const u16 *source, u16 *destination, u16 count, u8 amount)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_08147958(source[index], amount);
}
