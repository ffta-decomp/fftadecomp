/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08038B2C.c
 * Original SHA-256: e42114e7c0d5560e40dc93f2dd37d5abd847fa01dd9d101db2a432d10c91087b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern const u16 data_089551F4[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_080355A0(const u16 *source, u16 *destination,
                         u32 height, u16 width, u16 stride);

/* Complete [0x08038B2C, 0x08038B58): 44 bytes, 17 instructions. */
void func_08038B2C(void)
{
    u16 *destination = func_0808B8E4(0, 1, 4, 18);

    func_080355A0(data_089551F4, destination, 3, 10, 32);
}
