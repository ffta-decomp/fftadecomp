/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08099EA0.c
 * Original SHA-256: 704669e5e06923d0e59fdffc517d6d6e3d1c0d03db4453d8d69239b81ac063e8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    s8 first_offset;
    s8 second_offset;
    u8 unknown_F8[4];
    u8 state;
    u8 mode;
    s8 x;
    s8 y;
} Child08099EA0;

typedef struct {
    Child08099EA0 *child;
    u8 unknown_04[0x38];
    void *graphics;
} Object08099EA0;

extern void func_080CA2E8(Child08099EA0 *child);
extern void func_08149230(void *graphics, s8 x, s8 y, u8 mode,
                          s8 first_offset, s8 second_offset);

/* 0x08099EA0..0x08099F00: 96 bytes, 46 instructions. */
void func_08099EA0(Object08099EA0 *object)
{
    s32 x;
    s32 y;

    func_080CA2E8(object->child);
    x = object->child->x;
    y = object->child->y;
    if (object->child->state == 2 || object->child->mode == 5 ||
        object->child->state == 3) {
        x = 34;
        y = -34;
    }
    func_08149230(object->graphics, x, y, 0xFF,
                  object->child->first_offset, object->child->second_offset);
}
