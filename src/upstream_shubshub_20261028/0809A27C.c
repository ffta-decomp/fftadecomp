/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809A27C.c
 * Original SHA-256: 22e5d7ef24d9bf41861a5b288e11c3228d9b362d98c38c02a2c4753eab79b5df
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 offset;
    u8 unknown_20[0x14];
    u16 x;
    u16 y;
    u8 unknown_38[0xC];
    void *sprite;
} Object0809A27C;

extern void func_0802158C(void *sprite, s32 x, s32 y, u32 flags);

/* 0x0809A27C..0x0809A298: 28 bytes, 13 instructions. */
void func_0809A27C(Object0809A27C *object, s32 offset)
{
    object->offset = offset;
    func_0802158C(object->sprite, object->x, object->y + offset, 0);
}
