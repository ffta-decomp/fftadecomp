/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08142A94.c
 * Original SHA-256: cfdce268ccdab55c3500b9513198f5c7ed471070eaec573fbb45d4590e9cae9f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

union DoubleWord {
    long long value;
    struct {
        u32 low;
        u32 high;
    } words;
};

long long func_08142A94(long long value)
{
    union DoubleWord input;
    union DoubleWord result;

    input.value = value;
    result.words.low = -input.words.low;
    result.words.high = -input.words.high - (result.words.low != 0);
    return result.value;
}
