/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809AD6C.c
 * Original SHA-256: d4d60d70c996d0b7ecd218e7d25c6ec992a4ac91382876deeab6022802373564
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x5C];
    s16 counter;
} CounterObject;

/* 0809AD6C..0809AD92: 38 bytes. */
u32 func_0809AD6C(CounterObject *object, const CounterObject *excluded)
{
    if (object != excluded && object->counter >= 0) {
        if (object->counter > 97)
            object->counter = 98;
        object->counter++;
    }
    return 1;
}
