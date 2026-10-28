/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08066D98.c
 * Original SHA-256: ced066db31447ac804d9e8fa7da68b2b4ec45853bed63e5e6b60d02ef5623778
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 id;
    u8 flags;
} State08066D98;

extern u8 func_080099A4(u8);
extern void func_0806707C(State08066D98 *);

/* Complete [0x08066D98, 0x08066DC2): 42 bytes, 19 instructions. */
u8 func_08066D98(State08066D98 *state)
{
    u32 result;

    if (!func_080099A4(state->id)) {
        result = 0;
    } else {
        state->flags |= 4;
        func_0806707C(state);
        result = 1;
    }
    return result;
}
