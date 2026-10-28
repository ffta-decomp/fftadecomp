/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801BCF8.c
 * Original SHA-256: 7e33975f1933ce650db73e6631a6cdc81c42b5ed4b157f77a77045d6c1ecdad2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_0801E5E0(u32 x, s16 y);
extern u16 func_0801B938(s16 x, s16 y);

/* 0801BCF8..0801BD2C: 52 bytes. */
u16 func_0801BCF8(s16 x, s16 y, u16 target_x, u16 target_y)
{
    func_0801E5E0(x, y);
    return func_0801B938((s16)target_x, (s16)target_y);
}
