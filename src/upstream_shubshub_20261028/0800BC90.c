/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BC90.c
 * Original SHA-256: bf10730918b82e4b5a9c191c97afa4c1680d7435abbd20f591e42343c63d3ce4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BC90 .. 0x0800BCE0: 80 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x0A];
    u8 value;
    u8 unknown_1D[0x0B];
} Record0800BC90;

extern Record0800BC90 g_records_02009000[];

void func_0800BC90(u8 index, u8 enabled, u8 value)
{
    if (enabled) {
        g_records_02009000[index].flags |= 4;
        g_records_02009000[index].value = value;
    } else {
        g_records_02009000[index].flags &= 0xFFFB;
        g_records_02009000[index].value = 0xFF;
    }
}
