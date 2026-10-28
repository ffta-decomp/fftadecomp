/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A9484.c
 * Original SHA-256: 36201fc858872ae1f8839e4792c4e3721ee991cb0e359c1d0d1122574318f8c7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern const u8 data_0839454C[];

extern void func_08001CF0(const void *data, s32 x, s32 y, u32 argument3,
                         u32 argument4, u32 argument5, u32 argument6,
                         u32 argument7, u32 argument8, u32 flags,
                         u32 argument10);

/* Complete [0x080A9484, 0x080A94B8): 52 bytes, 23 instructions. */
void func_080A9484(u32 unused, s16 x, s16 y, u8 flags)
{
    func_08001CF0(data_0839454C, x, y, 0, 0, 0, 0, 0, 0, flags, 0);
}
