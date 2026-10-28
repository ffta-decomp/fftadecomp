/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08035678.c
 * Original SHA-256: b2377bc413fb5405a061b46fabb10a5deb56b2aad954dfb2647a52e9df4c0002
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08035678..0x080356A0: 40 bytes / 20 instructions. */
void func_08035678(u16 value, u16 *destination, u32 count, u16 step)
{
    u32 index;

    for (index = 0; index < count; ++index) {
        *destination++ = value;
        value += step;
    }
}
