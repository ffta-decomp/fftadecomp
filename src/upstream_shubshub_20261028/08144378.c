/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08144378.c
 * Original SHA-256: 7c2c07ade4df70010b26f5e8a622eb56240ec6a4f20134f42efb23f88a349763
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

union DoubleWord {
    unsigned long long value;
    struct {
        u32 low;
        u32 high;
    } words;
};

unsigned long long func_08144378(unsigned long long value, s32 shift)
{
    union DoubleWord input;
    union DoubleWord result;
    s32 remaining;

    if (shift == 0)
        return value;

    input.value = value;
    remaining = 32 - shift;
    if (remaining <= 0) {
        result.words.high = 0;
        result.words.low = input.words.high >> -remaining;
    } else {
        u32 carry = input.words.high << remaining;

        result.words.high = input.words.high >> shift;
        result.words.low = (input.words.low >> shift) | carry;
    }
    return result.value;
}
