/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08137A9C.c
 * Original SHA-256: 6d1ef805b06a6d548aebaeab7d98feee7ecc54d0ff1da90a6b62478e0e758dc6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef void (*RegionCallback08137A9C)(void *region, u32 size);

extern RegionCallback08137A9C g_callbacks_0836D4B8[];
extern u8 data_0200F3C8[];
extern void *data_0201C3C8;
extern void *func_080070C8(void *region, u32 size);

/* 0x08137A9C: 52 bytes; initialize the region and retain its context. */
void func_08137A9C(void)
{
    g_callbacks_0836D4B8[0](data_0200F3C8, 0xD000);
    data_0201C3C8 = func_080070C8(data_0200F3C8, 0xD000);
}
