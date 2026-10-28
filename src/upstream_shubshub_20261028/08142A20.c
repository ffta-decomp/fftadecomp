/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08142A20.c
 * Original SHA-256: d432526af19a2616f52056531d812ae1d7d1ee2815dd2a297708b685cacd2fde
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef long long s64;

typedef union {
    struct {
        s32 low;
        s32 high;
    } words;
    s64 value;
} Wide08142A20;

#define MULTIPLY_HALVES(high, low, first, second)                          \
    do {                                                                 \
        u32 low_product, middle_first, middle_second, high_product;       \
        u32 left_low, right_low, left_high, right_high;                   \
        left_low = (u32)(first) % 0x10000L;                              \
        left_high = (u32)(first) / 0x10000L;                              \
        right_low = (u32)(second) % 0x10000L;                             \
        right_high = (u32)(second) / 0x10000L;                            \
        low_product = left_low * right_low;                              \
        middle_first = left_low * right_high;                            \
        middle_second = left_high * right_low;                           \
        high_product = left_high * right_high;                           \
        middle_first += low_product / 0x10000L;                          \
        middle_first += middle_second;                                  \
        if (middle_first < middle_second)                                \
            high_product += 0x10000;                                    \
        (high) = high_product + middle_first / 0x10000L;                   \
        (low) = (middle_first % 0x10000L) * 0x10000L                     \
              + low_product % 0x10000L;                                  \
    } while (0)

#define MULTIPLY_WORDS(first, second)                                      \
    ({                                                                   \
        Wide08142A20 product;                                            \
        MULTIPLY_HALVES(product.words.high, product.words.low, first, second); \
        product.value;                                                   \
    })

/* 0x08142A20 - 116 bytes, including the literal pool. */
s64 func_08142A20(s64 first, s64 second)
{
    Wide08142A20 result;
    Wide08142A20 left;
    Wide08142A20 right;

    left.value = first;
    right.value = second;
    result.value = MULTIPLY_WORDS(left.words.low, right.words.low);
    result.words.high += (u32)left.words.low * (u32)right.words.high
                       + (u32)left.words.high * (u32)right.words.low;
    return result.value;
}
