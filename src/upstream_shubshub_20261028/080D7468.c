/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D7468.c
 * Original SHA-256: e594cf1ee22b488c96bbb0545fc3a719a6e0d54e5ef2cef477a200ebb4483bcd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 x;
    u8 y;
} Position;

extern void func_08003508(s16 offset, u8 value);
extern void func_08003558(s16 offset, u8 value);

void func_080D7468(const Position *position, u8 value, u16 x, u16 y)
{
    u16 dx = position->x - x;
    u16 dy = position->y - y;

    func_08003508((s16)dx, value);
    func_08003558((s16)dy, value);
}
