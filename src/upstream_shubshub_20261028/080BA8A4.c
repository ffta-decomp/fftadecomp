/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BA8A4.c
 * Original SHA-256: bb6fec77b6ec7164b3a014f95593e3b2d7da12611b2fd4b7f24de6cd061f99d7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080BA8A4..0x080BA8E2: 62 bytes. */
typedef struct {
    void *resource;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_0C[0xE];
    u16 attributes;
    u8 style;
} Object;

void func_08001F34(void *resource, s32 x, s32 y, u32 mode,
                   u32 argument5, u32 argument6, u32 argument7, u32 argument8,
                   u16 attributes, u32 argument10, u8 style);

void func_080BA8A4(const Object *object)
{
    func_08001F34(object->resource,
                  object->x + object->offset_x,
                  object->y + object->offset_y,
                  0, 0, 0, 0, 0, object->attributes, 0, object->style);
}
