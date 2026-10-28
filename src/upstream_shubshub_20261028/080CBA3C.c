/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CBA3C.c
 * Original SHA-256: 031e112f5466296eca7af8cdb435f2f2a907a4c1487e5e153daba578c19f5505
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2FC2];
    unsigned mode : 2;
} State080CBA3C;

extern State080CBA3C g_state_02000000;
extern const u8 data_08419D60[];
extern const u8 data_0841A860[];
extern const u8 data_0841B340[];

/* Complete [0x080CBA3C, 0x080CBA84): 72 bytes, 24 instructions. */
const u8 *func_080CBA3C(u8 index)
{
    s32 mode = g_state_02000000.mode;
    u32 offset;
    u32 base;

    switch (mode) {
    case 2:
        offset = index * 32;
        base = (u32)data_0841A860;
        break;
    case 1:
        offset = index * 32;
        base = (u32)data_0841B340;
        break;
    default:
        offset = index * 32;
        base = (u32)data_08419D60;
        break;
    }
    return (const u8 *)(offset + base);
}
