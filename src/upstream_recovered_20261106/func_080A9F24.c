/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080A9F24.c
 * Original SHA-256: 0cc6e8a02300efe1332a7bf43f0d167c5487d974a0893d7ace018d40ed2d86b9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* 0x080A9F24: 886 bytes. */
typedef struct {
    u8 unknown_00[8];
    s16 x, y, z;
    u8 unknown_0e[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
} Object;

typedef struct {
    s32 velocity, height, limit;
} Motion;

typedef struct {
    Object *object;
    Motion motion;
    u8 unknown_10[0x26];
    u16 commands[3];
    u8 index, count;
    s8 direction;
    u8 unknown_3f;
    u8 flags;
    u8 unknown_41[0xb3];
    s16 x, y, z;
    u8 unknown_fa[2];
    u8 effect_arg, effect_status;
    u8 unknown_fe[0x34];
    s8 dx, dz;
    u8 unknown_134[2];
    s16 destination_x, destination_z;
    u8 unknown_13a[2];
    u16 state;
    u8 unknown_13e[0x4a];
    u8 mode;
} Movement;

extern void func_0809D66C(s8 direction, s8 *dx, s8 *dz);
extern void func_0809836C(Object *object, u16 animation, s8 direction, u16 command);
extern s32 func_08099C34(Object *object);
extern u32 func_08099C64(const Object *object);
extern void func_080A92E4(u16 mode, s16 x, s16 y, s16 z, u32 effect);
extern void func_08141570(s32 player, u16 song);
extern void func_080A7EC4(u16 command);
extern void func_0809A570(Object *object, u32 clear, u32 set);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern s32 func_08142950(s32 dividend, s32 divisor);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern u8 func_080A9E6C(Movement *movement, s32 distance);

static inline s32 opposite_component(s8 component)
{
    return -component;
}

u32 func_080A9F24(Movement *movement, Object *other, u32 unused, void *effect)
{
    switch (movement->state) {
    case 0:
        movement->flags |= 2;
        movement->object->flags &= ~1;
        func_0809D66C(movement->direction, &movement->dx, &movement->dz);
        movement->object->x = (((other->x >> 5) - movement->dx * 4) << 5) + 16;
        movement->object->z = (((other->z >> 5) - movement->dz * 4) << 5) + 16;
        movement->destination_x = (((other->x >> 5) - movement->dx) << 5) + 16;
        movement->destination_z = (((other->z >> 5) - movement->dz) << 5) + 16;
        movement->motion.limit = other->y << 8;
        movement->motion.height = (other->y - 48) << 8;
        movement->motion.velocity = 0x900;
        movement->object->y = movement->motion.height >> 8;
        func_0809836C(movement->object, 7, movement->direction, movement->commands[0]);
        movement->state = 1;
        break;
    case 1:
        {
            s32 busy = func_08099C34(movement->object);
            if (busy == 0) {
                if (movement->mode == 0) {
                    func_080A92E4(0, other->x, other->y, other->z, 0x15);
                    func_08141570(2, 0x8d);
                } else {
                    s8 left, right;
                    s32 height_offset;
                    func_080A7EC4(movement->commands[movement->index]);
                    func_0809836C(other, 5, other->direction, 0);
                    func_0809A570(other, 0, 0x8000);
                    func_080A8390(movement->object->direction, other->direction, &left, &right);
                    if (left != 0)
                        func_0809A570(other, 0, 0x200);
                    if (right != 0)
                        func_0809A570(other, 0, 0x400);
                    movement->x = other->x - movement->dx * 16;
                    height_offset = func_08142950((s16)func_08002804(), 9) + 8;
                    movement->y = other->y + height_offset;
                    movement->z = other->z - movement->dz * 16;
                    movement->effect_arg = 0;
                    movement->effect_status = 0;
                    func_080E2C00(effect, movement->x, movement->y, movement->z,
                                 movement->effect_arg, busy);
                }
                ++movement->index;
                if (movement->count > movement->index)
                    func_0809836C(movement->object, 7, movement->direction,
                                 movement->commands[movement->index]);
            }
        }
        {
            Motion *motion = &movement->motion;
            motion->height += movement->motion.velocity;
            movement->motion.velocity -= 0x99;
            if (motion->limit >= motion->height && movement->motion.velocity <= 0)
                motion->height = motion->limit;
        }
        movement->object->y = movement->motion.height >> 8;
        func_080A9E6C(movement, 4);
        if (func_08099C64(movement->object)) {
            func_0809836C(movement->object, 3, movement->direction, 0);
            movement->motion.limit = (other->y - 48) << 8;
            movement->motion.height = other->y << 8;
            movement->motion.velocity = 0x900;
            movement->object->y = movement->motion.height >> 8;
            movement->dx = opposite_component(movement->dx);
            movement->dz = opposite_component(movement->dz);
            movement->state = 2;
        }
        break;
    case 2:
        {
            s32 moving;
            Motion *motion;
            if (movement->dx != 0)
                movement->object->x += movement->dx * 4;
            if (movement->dz != 0)
                movement->object->z += movement->dz * 4;
            motion = &movement->motion;
            motion->height += movement->motion.velocity;
            movement->motion.velocity -= 0x99;
            if (motion->limit >= motion->height && movement->motion.velocity <= 0) {
                motion->height = motion->limit;
                moving = 0;
            } else {
                moving = 1;
            }
            movement->object->y = movement->motion.height >> 8;
            if (!moving) {
                movement->object->flags |= 1;
                movement->flags = 0;
                return 0;
            }
        }
        break;
    }
    return 1;
}
