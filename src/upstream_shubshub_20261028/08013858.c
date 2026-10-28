/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013858.c
 * Original SHA-256: 49ad99acda2c5a834c048f67d6e1b5323cc9698d0c8f880adfe9d7e8df927c8a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08013858..0x08013890: 56 bytes. */
typedef struct MatrixState MatrixState;
extern void func_08013800(MatrixState *state, u32 column);

void func_08013858(MatrixState *state, s32 first, s32 count)
{
    s32 column;

    if (count == 0) {
        for (column = 0; column < 6; column++) {
            func_08013800(state, column);
        }
    } else {
        for (column = first; column < first + count; column++) {
            func_08013800(state, column);
        }
    }
}
