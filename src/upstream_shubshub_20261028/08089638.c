/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089638.c
 * Original SHA-256: 477bfc112115ae9c08d0d1df58a51c5b165735b6fed4723f9f6f58baf4033d0c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

void func_08089638(u16 *destination, u16 value, u16 width)
{
    s32 column;

    for (column = 0; column < width; column++, destination++) {
        destination[0] = value;
        destination[width] = value;
    }
}
