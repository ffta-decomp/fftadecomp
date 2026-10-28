/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801E620.c
 * Original SHA-256: fed2ff0f805612d133815b82176d751d83c3df8075c003c6f7a252eb3ce74cd5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 g_state_02007F40[];

/* 0x0801E620..0x0801E630: 16 bytes. */
void func_0801E620(u8 *first, u8 *second)
{
    *first = g_state_02007F40[2];
    *second = g_state_02007F40[3];
}
