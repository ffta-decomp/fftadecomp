/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080D7220.c
 * Original SHA-256: 48d2c7f4f0a227e53be7c1fa0bc3764322dee7bb494cd88d6fca11092b071f19
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* Target: complete [0x080D7220, 0x080D72C8), 168 bytes. */
typedef struct {
    u8 unknown_00[2];
    u8 x;
    u8 y;
} Position;

extern u16 g_control_flags_03000940;
extern const u32 data_083954C0[];
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern u32 func_080035A8(u8 layer);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);

void func_080D7220(const Position *position, u8 index, u8 layer,
                   u16 x, u16 y, u16 control)
{
    const u32 *definitions = data_083954C0;
    u32 attributes = func_08003A74(definitions[index]);
    u16 dx;
    u16 dy;

    attributes |= func_08003A80(0x06008000);
    control |= attributes;
    func_080034B8(control, layer);
    {
        u32 mask = func_080035A8(layer);
        u16 flags = g_control_flags_03000940;
        flags |= mask;
        g_control_flags_03000940 = flags;
    }
    dx = position->x - x;
    dy = position->y - y;
    func_08003508((s16)dx, layer);
    func_08003558((s16)dy, layer);
}
