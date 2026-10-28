/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081439C8.c
 * Original SHA-256: 97c2b726f1f8dd4fdbe0ccc0b758a298a1b01ace218162a05065ed41ff156f64
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x081439C8..0x08143A84: 188 bytes, including the literal pool. */
typedef enum {
    FP_SNAN,
    FP_QNAN,
    FP_ZERO,
    FP_NUMBER,
    FP_INFINITY
} FloatClass;

typedef struct {
    FloatClass classification;
    u32 sign;
    s32 exponent;
    u32 fraction;
} UnpackedFloat;

typedef union {
    float value;
    struct {
        u32 fraction : 23;
        u32 exponent : 8;
        u32 sign : 1;
    } bits;
} PackedFloat;

static inline int is_nan(const UnpackedFloat *number)
{
    return number->classification == FP_SNAN || number->classification == FP_QNAN;
}

static inline int is_infinity(const UnpackedFloat *number)
{
    return number->classification == FP_INFINITY;
}

static inline int is_zero(const UnpackedFloat *number)
{
    return number->classification == FP_ZERO;
}

float func_081439C8(const UnpackedFloat *number)
{
    u32 fraction = number->fraction;
    u32 sign = number->sign;
    u32 exponent = 0;
    PackedFloat packed;

    if (is_nan(number)) {
        exponent = 255;
        fraction |= 0x100000;
    } else if (is_infinity(number)) {
        exponent = 255;
        fraction = 0;
    } else if (is_zero(number)) {
        fraction = 0;
    } else if (fraction != 0) {
        s32 value = number->exponent;

        if (value < -126) {
            s32 shift = -126 - value;
            if (shift > 25)
                fraction = 0;
            else
                fraction >>= shift;
        } else if (value > 127) {
            exponent = 255;
            fraction = 0;
            goto pack;
        } else {
            exponent = value + 127;
            if ((fraction & 0x7F) == 0x40) {
                if (fraction & 0x80)
                    fraction += 0x40;
            } else {
                fraction += 0x3F;
            }
            if ((s32)fraction < 0) {
                fraction >>= 1;
                ++exponent;
            }
        }
        fraction >>= 7;
    }
pack:
    packed.bits.fraction = fraction;
    packed.bits.exponent = exponent;
    packed.bits.sign = sign;
    return packed.value;
}
