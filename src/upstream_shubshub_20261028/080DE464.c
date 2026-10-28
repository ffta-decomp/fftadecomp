/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DE464.c
 * Original SHA-256: 63174d92b68922f2149748e181327780a054dc159bcf2276911da1798e4dc9d4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DE464..0x080DE486: 34 bytes. */
extern void func_0809A570(int index, u32 clear_mask, u32 set_mask);

void func_080DE464(int index, u8 enabled)
{
    if (enabled)
        func_0809A570(index, 0, 0x1000);
    else
        func_0809A570(index, 0x1000, 0);
}
