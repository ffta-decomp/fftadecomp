/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08141780.c
 * Original SHA-256: 4b60595b70bfd865e41a4e6b8a4885a91d24e9e4515d5b1de9f50802fcd1a406
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08141780, 0x081417E8): 104 bytes, 32 instructions. */
extern u8 data_020084D8;
extern u8 data_0200F2A0[];
extern void func_08146120(void *, u16, u16);

void func_08141780(float volume)
{
    if (volume < 0.0156)
        volume = 0.0156f;

    if (data_020084D8 & 1) {
        u16 scaled = (u32)(volume * 256.0f);

        func_08146120(data_0200F2A0, 0xFFFF, scaled ? scaled : 1);
    }
}
