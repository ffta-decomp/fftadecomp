/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813C0C4.c
 * Original SHA-256: 5543e80b7dbe4b5b05caf75267f60aa2d90be1c0a1d64c4094c96268557300c7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813C0C4..0x0813C0D8: 20 bytes, 7 instructions. */
extern void *data_0200F3BC;
extern void *func_08007138(void *owner, u32 bytes);

void *func_0813C0C4(u32 bytes)
{
    return func_08007138(data_0200F3BC, bytes);
}
