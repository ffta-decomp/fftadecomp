/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08029864.c
 * Original SHA-256: 3290c63dc4ea7a290668044039685feaee699b8eb2efb4aa65f3e0547a557cc6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u32 value;
} Resource08029864;

typedef struct {
    u8 unknown_00[0x1084];
    u8 value_1084;
    u8 value_1085;
    u8 value_1086;
    u8 value_1087;
    u8 value_1088;
    u8 value_1089;
    u8 value_108a;
    u8 value_108b;
} State08029864;

extern Resource08029864 data_030008B0;
extern Resource08029864 data_03000990;
extern void func_08017424(void *, u32, u32, u8, u8, u8, u8,
                          u16, u8, u16, u16, u8);
extern void func_08016C90(void *, u8);

/* Complete [0x08029864, 0x0802995C): 248 bytes, 111 instructions. */
void func_08029864(State08029864 *state, u8 a, u8 b, u8 c,
                   u8 d, u8 e, u8 f, u8 g, u8 h, u8 i)
{
    func_08017424(state, data_030008B0.value, data_03000990.value,
                   a, b, 6, c, 0x800, 0x20, 13, 3, 11);
    func_08016C90(state, 1);
    state->value_108b = c;
    state->value_1085 = e;
    state->value_1086 = f;
    state->value_1088 = i;
    state->value_108a = d;
    state->value_1087 = g;
    state->value_1084 = h;
    state->value_1089 = 0;
}
