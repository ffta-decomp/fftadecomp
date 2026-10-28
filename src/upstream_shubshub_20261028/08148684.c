/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148684.c
 * Original SHA-256: edd2dfbe0aa3f7419a3d21d58793cde826aa8cf8a81d17fcf14e33d2ac9861ce
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct ObjectState {
    u16 state;
    u16 flags;
};

enum {
    OBJECT_FLAG_10 = 0x10
};

void func_08148684(struct ObjectState *object, u8 mode)
{
    if (mode == 1)
        object->flags &= (u16)~OBJECT_FLAG_10;
    else
        object->flags |= OBJECT_FLAG_10;
}
