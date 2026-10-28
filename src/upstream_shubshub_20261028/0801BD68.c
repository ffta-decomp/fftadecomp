/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801BD68.c
 * Original SHA-256: ea8651a6be7574f824f187b4e83d5f0673e0bc51c571184ae796eccef0a8f86c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801BD68..0x0801BDA4: 60 bytes. */
extern void func_0801E5E0(s16 x, s16 y);
extern u16 func_0801BB0C(s16 x, s16 y, u16 duration);

u16 func_0801BD68(s16 x, s16 y, u16 target_x, u16 target_y, u16 duration)
{
    func_0801E5E0(x, y);
    return func_0801BB0C((s16)target_x, (s16)target_y, duration);
}
