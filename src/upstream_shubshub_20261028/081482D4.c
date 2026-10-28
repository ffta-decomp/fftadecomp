/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081482D4.c
 * Original SHA-256: 5f4b46927144371e8c77481342d4e6a2aa7ad2b2b0f1eeef44f60f2c06708af9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x081482D4..0x08148316: 66 bytes. */
extern u16 func_081478DC(u16, u8);

void func_081482D4(const u16 *source, u16 *destination, u16 count, u8 mode)
{
    u16 i;

    for (i = 0; i < count; ++i)
        destination[i] = func_081478DC(source[i], mode);
}
