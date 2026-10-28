/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E28A8.c
 * Original SHA-256: 25228ae7979097cce626fb1c43660465c5b12c34f96ec3b880e017d68e921b32
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E28A8..0x080E28C4: 28 bytes. */
extern u16 func_08005BAC(const void *object);

int func_080E28A8(const void *object)
{
    u16 value = func_08005BAC(object);

    if (value > 0xFF || value == 2)
        return 1;
    return 0;
}
