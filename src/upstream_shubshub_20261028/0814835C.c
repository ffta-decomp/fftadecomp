/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0814835C.c
 * Original SHA-256: 4ce36d6d08f722c0124e1d5eb373b7a74b165ee0c72bb649fabdc0b927fe9813
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0814835C..0x08148384: 40 bytes. */
void func_0814835C(u16 *destination, u16 value, u16 count)
{
    u16 i;

    for (i = 0; i < count; ++i)
        destination[i] = value;
}
