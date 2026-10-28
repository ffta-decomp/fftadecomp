/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08021D0C.c
 * Original SHA-256: 6b45d6cae994452e17981122d9509f4658589de76404e1c0853014c8ee75fc8d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Position08021D0C {
    u8 unknown_00[0x30];
    u16 x;
    u16 y;
};

void func_08021D0C(struct Position08021D0C *object, u16 x, u16 y)
{
    object->x = x;
    object->y = y;
}
