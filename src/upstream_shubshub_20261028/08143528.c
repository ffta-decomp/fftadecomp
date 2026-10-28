/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08143528.c
 * Original SHA-256: f19aed6d7cdcb6ccad78996040a43e778fa3b9c05750a6c0e9d7603e8f55994f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08143528, 0x0814362A), 258 bytes, 129 instructions. */
typedef struct {
    u32 classification;
    u32 sign;
    s32 exponent;
    u32 fraction_low;
    u32 fraction_high;
} Number08143528;

static inline s32 number_is_nan(const Number08143528 *number)
{
    s32 result = 0;

    if (number->classification <= 1)
        result = 1;
    return result;
}

static inline s32 number_is_infinite(const Number08143528 *number)
{
    s32 result = 0;

    if (number->classification == 4)
        result = 1;
    return result;
}

static inline s32 number_is_zero(const Number08143528 *number)
{
    s32 result = 0;

    if (number->classification == 2)
        result = 1;
    return result;
}

s32 func_08143528(const Number08143528 *first, const Number08143528 *second)
{
    if (number_is_nan(first) || number_is_nan(second))
        return 1;
    if (number_is_infinite(first) && number_is_infinite(second))
        return second->sign - first->sign;
    if (number_is_infinite(first))
        return first->sign ? -1 : 1;
    if (number_is_infinite(second))
        return second->sign ? 1 : -1;
    if (number_is_zero(first) && number_is_zero(second))
        return 0;
    if (number_is_zero(first))
        return second->sign ? 1 : -1;
    if (number_is_zero(second))
        return first->sign ? -1 : 1;
    if (first->sign != second->sign)
        return first->sign ? -1 : 1;
    if (first->exponent > second->exponent)
        return first->sign ? -1 : 1;
    if (first->exponent < second->exponent)
        return first->sign ? 1 : -1;
    if (first->fraction_high > second->fraction_high ||
        (first->fraction_high == second->fraction_high &&
         first->fraction_low > second->fraction_low))
        return first->sign ? -1 : 1;
    if (second->fraction_high > first->fraction_high ||
        (second->fraction_high == first->fraction_high &&
         second->fraction_low > first->fraction_low))
        return first->sign ? 1 : -1;
    return 0;
}
