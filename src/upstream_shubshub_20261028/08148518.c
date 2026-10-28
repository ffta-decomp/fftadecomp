/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148518.c
 * Original SHA-256: 4345d999510f5e7831e88ab78abd28e7d31f60875e76efcf2bbddd2b9a6d8cf9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

void func_08148518(u16 *state)
{
    if (*state == 1)
        *state = 2;
}
