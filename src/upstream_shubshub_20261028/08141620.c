/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08141620.c
 * Original SHA-256: aae5230b4eb258e8f17d1c72e5c5d51e982dfc4d13430f07462e1ff735ad3cf0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_020084D8;
extern u8 data_0200F2E0[];
extern u8 data_0200F320[];
extern void func_08145990(void *player);

/* Target: [0x08141620, 0x0814164C), 44 bytes, 13 instructions. */
void func_08141620(void)
{
    if (data_020084D8 & 2) {
        func_08145990(data_0200F2E0);
        func_08145990(data_0200F320);
    }
}
