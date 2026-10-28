/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D987C.c
 * Original SHA-256: 8654a821954c6d2d21036ccab55ce7af8c9b272b6703dd810d6344d49c0291ac
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 values[0];
} ObjectState;

extern ObjectState *func_08005BFC(void *object);

void func_080D987C(void *object, u8 index, u16 value)
{
    ObjectState *state = func_08005BFC(object);

    state->values[index] = value;
}
