/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801BD2C.c
 * Original SHA-256: 6882fa99daf4074f185ea4a669d7abcb65b18dfbef0e5d32fc4c239a81ad9248
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801BD2C..0x0801BD68: 60 bytes. */
extern void func_0801E5E0(s16 x, s16 y);
extern u16 func_0801BA20(s16 x, s16 y, u16 speed);

u16 func_0801BD2C(s16 x, s16 y, u16 target_x, u16 target_y, u16 speed)
{
    func_0801E5E0(x, y);
    return func_0801BA20((s16)target_x, (s16)target_y, speed);
}
