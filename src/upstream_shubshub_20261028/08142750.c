/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08142750.c
 * Original SHA-256: b3e6aca510107a6ac121caa4b164da938d1190be7fb556feb6e319cb4b1f34a8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08142750, 0x0814278A): 58 bytes, 20 instructions. */
extern long long __fixunsdfdi(double value);

long long func_08142750(double value)
{
    if (value < 0)
        return -__fixunsdfdi(-value);
    return __fixunsdfdi(value);
}
