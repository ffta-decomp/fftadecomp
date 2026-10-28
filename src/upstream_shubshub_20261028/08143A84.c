/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08143A84.c
 * Original SHA-256: 03111b48cd9152f49127a7fbbae109f539bb7e47eb1aba3aace6f06828face76
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct
{
    u32 significand : 23;
    u32 exponent : 8;
    u32 negative : 1;
} FloatRepresentation;

typedef struct
{
    u32 category;
    u32 negative;
    s32 exponent;
    u32 significand;
} FloatParts;

/* Complete target: 0x08143A84..0x08143B02, 126 bytes. */
void func_08143A84(const FloatRepresentation *representation, FloatParts *parts)
{
    u32 significand = representation->significand;
    u32 exponent = representation->exponent;

    parts->negative = representation->negative;
    if (exponent == 0)
    {
        if (significand == 0)
            parts->category = 2;
        else
        {
            parts->exponent = (s32)exponent - 126;
            significand <<= 7;
            parts->category = 3;
            while (significand < 0x40000000)
            {
                significand <<= 1;
                parts->exponent--;
            }
            parts->significand = significand;
        }
    }
    else if (exponent == 0xFF)
    {
        if (significand == 0)
            parts->category = 4;
        else
        {
            if (significand & 0x100000)
                parts->category = 1;
            else
                parts->category = 0;
            parts->significand = significand;
        }
    }
    else
    {
        parts->exponent = (s32)exponent - 127;
        parts->category = 3;
        parts->significand = (significand << 7) | 0x40000000;
    }
}
