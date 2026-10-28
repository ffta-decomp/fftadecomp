/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801D890.c
 * Original SHA-256: c1e9a13811b0f98aebb0127025e49eceda1ed57d2be53cbf54ca55d04ec84d90
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801D890..0x0801D8B8: 40 bytes. */
typedef struct {
    u8 unknown_00[0x228];
    u8 enabled;
} OutputState;

extern OutputState g_state_02007F40;

void func_0801D890(u8 *first, u8 *second)
{
    if (g_state_02007F40.enabled == 0) {
        *first = 0xFF;
        *second = 0xFF;
    } else {
        *first = 1;
        *second = 0;
    }
}
