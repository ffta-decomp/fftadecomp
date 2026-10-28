/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812DB5C.c
 * Original SHA-256: 2ca3e80a2bdb75368440b8559aa51da82da48bc975fe93841dbd8de025a1f2ba
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0812DB5C, 0x0812DBA6), 74 bytes. */
typedef struct {
    u8 unknown_00[0xf6];
    s8 x;
    s8 y;
    s8 z;
} Position0812DB5C;

extern u32 func_0812D1DC(Position0812DB5C *, Position0812DB5C *,
                        s32, s32, s32, s32, s32, u32);

u32 func_0812DB5C(Position0812DB5C *source, Position0812DB5C *destination,
                   u32 mode)
{
    return func_0812D1DC(source, destination, source->x, source->y,
                          destination->x, destination->y, destination->z, mode);
}
