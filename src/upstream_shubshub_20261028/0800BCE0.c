/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BCE0.c
 * Original SHA-256: 3f089a1e32521a47452102e0e051f121348231aea605ae56370f338a35e78139
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BCE0 .. 0x0800BD24: 68 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x16];
} Record0800BCE0;

extern Record0800BCE0 g_records_02009000[];

void func_0800BCE0(u8 index, u8 enabled)
{
    if (enabled)
        g_records_02009000[index].flags |= 8;
    else
        g_records_02009000[index].flags &= 0xFFF7;
}
