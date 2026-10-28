/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081415C0.c
 * Original SHA-256: 7f847fc8fb80fc39f991aff3f2d3bad5cb71d8928b2bedb995fe01167c8829ab
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x081415C0, 0x08141620): 96 bytes, 35 instructions. */
extern u8 data_020084D8;
extern u8 data_0200F2E0[];
extern u8 data_0200F320[];
extern void func_08146120(void *, u16, u16);

void func_081415C0(u16 selector, float volume)
{
    void *player = 0;

    if (data_020084D8 & 2) {
        switch (selector) {
        case 1:
            player = data_0200F2E0;
            break;
        case 2:
            player = data_0200F320;
            break;
        }
        if (player != 0)
            func_08146120(player, 0xFFFF, (u16)(volume * 256.0f));
    }
}
