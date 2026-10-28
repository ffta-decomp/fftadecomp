/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802EAE0.c
 * Original SHA-256: 703fc7de2a5ab8d5d586d417080d7ed9156497ce0f0ddb572ddac19e258ff267
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern BufferCopier data_0836D4BC[];

/* 0802EAE0..0802EB58: 120 bytes. */
void func_0802EAE0(u8 *destination, const u8 *source)
{
    s32 group;
    s32 row;

    for (group = 0; group < 3; group++) {
        for (row = 0; row < 4; row++) {
            data_0836D4BC[0](destination + row * 32, source + row * 64, 32);
            data_0836D4BC[0](destination + 128 + row * 32,
                             source + 32 + row * 64, 32);
        }
        source += 256;
        destination += 256;
    }
}
