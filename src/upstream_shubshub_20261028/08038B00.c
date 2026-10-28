/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08038B00.c
 * Original SHA-256: be0008fe62eff0ac4c2687eabf6f601ace6be7a389fa80b706d86bfea9ecba8f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern const u16 data_08955230[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_080355A0(const u16 *source, u16 *destination,
                         u32 height, u16 width, u16 stride);

/* Complete [0x08038B00, 0x08038B2C): 44 bytes, 17 instructions. */
void func_08038B00(void)
{
    u16 *destination = func_0808B8E4(0, 1, 24, 8);

    func_080355A0(data_08955230, destination, 4, 4, 32);
}
