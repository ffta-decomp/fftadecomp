/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BD24.c
 * Original SHA-256: e106b9bbb8d7e23fd8a2c5e908abca42d45ed51e0d99ff500633c979a4b60991
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BD24 .. 0x0800BD68: 68 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x16];
} Record0800BD24;

extern Record0800BD24 g_records_02009000[];

void func_0800BD24(u8 index, u8 enabled)
{
    if (enabled)
        g_records_02009000[index].flags |= 0x20;
    else
        g_records_02009000[index].flags &= 0xFFDF;
}
