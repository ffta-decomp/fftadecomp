/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801E700.c
 * Original SHA-256: 413aeff396381677c86cb673ecb638ed9ef994bc7d249934e9122063a590bde9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 x;
    u16 y;
} State_02007F40;

extern State_02007F40 g_state_02007F40;

/* 0x0801E700: 16 bytes, including the referenced state literal. */
void func_0801E700(u16 *x, u16 *y)
{
    *x = g_state_02007F40.x;
    *y = g_state_02007F40.y;
}
