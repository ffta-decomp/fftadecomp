/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013800.c
 * Original SHA-256: 29466dc36a219942bdc464bd271623ed8619a08eb313be83bfdb7a5af4e69b15
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct MatrixState {
    u8 unknown_00[0x10];
    u32 cells[16][8];
} MatrixState;

/* 08013800..08013856: 86 bytes, 43 instructions. */
void func_08013800(MatrixState *state, u32 column)
{
    u32 *cell = &state->cells[0][column];

    cell[0] = 0;
    cell[8] = 0;
    cell[16] = 0;
    cell[24] = 0;
    cell[32] = 0;
    cell[40] = 0;
    cell[48] = 0;
    cell[56] = 0;
    cell[64] = 0;
    cell[72] = 0;
    cell[80] = 0;
    cell[88] = 0;
    cell[96] = 0;
    cell[104] = 0;
    cell[112] = 0;
    cell[120] = 0;
}
