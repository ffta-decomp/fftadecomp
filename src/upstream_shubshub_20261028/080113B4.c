/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080113B4.c
 * Original SHA-256: ca77dc772b34d2962d9cede6bf16ead9eb0044cd3570518efb426fef057ca71a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080113B4..0x08011428: 116 bytes. */
extern u32 func_0801093C(u8, u32, u32, u16, u8,
                         s16, s16, s16, s16, s16, u16);

u32 func_080113B4(u8 arg0, u32 arg1, u32 arg2, u16 arg3, u8 arg4,
                  s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                  u16 arg10)
{
    return func_0801093C(arg0, arg1, arg2, arg3, arg4,
                         arg5, arg6, arg7, arg8, arg9, arg10);
}
