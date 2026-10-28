/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804CAB0.c
 * Original SHA-256: 2ae5f60132313836a0011748040dfe3d27caf314fcf7a331d1ddb8b985202c43
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 *data_0201F540;

/* 0804CAB0..0804CABC: 12 bytes, including the referenced pointer literal. */
u8 *func_0804CAB0(void)
{
    return data_0201F540 + 4;
}
