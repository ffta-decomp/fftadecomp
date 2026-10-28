/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08099C34.c
 * Original SHA-256: 7ffea6ed64f8cdae6dc4a298ccd25ea00641df069554e20567f3d8317542362f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08099C34..0x08099C64: 48 bytes. */
typedef struct {
    u8 unknown_00[0x44];
    u32 fallback;
    u32 unknown_48;
    u32 values[2];
} ValueState;

s32 func_08021C3C(u32 value);

s32 func_08099C34(ValueState *state)
{
    s32 index;
    u32 value;
    s32 result;

    for (index = 0; index < 2; ++index) {
        value = state->values[index];
        if (value != 0) {
            result = func_08021C3C(value);
            if (result < 0)
                return -1;
            return result;
        }
    }

    value = state->fallback;
    if (value == 0)
        return -1;
    result = func_08021C3C(value);
    if (result < 0)
        return -1;
    return result;
}
