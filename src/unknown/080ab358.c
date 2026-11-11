/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080AB358.c
 * Original SHA-256: 236fd999ab262921bca99081daa41e996ff41a659d1a24fe877e8826b0eac989
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
} Actor;

typedef struct {
    s32 velocity;
    s32 height;
    s32 destination;
} Motion;

typedef struct {
    Actor *actor;
    Motion motion;
    u8 unknown_10[0x26];
    u16 animation;
    u8 unknown_38[6];
    s8 direction;
    u8 unknown_3F;
    u8 flags;
    u8 unknown_41[0xB3];
    s16 effect_x;
    s16 effect_y;
    s16 effect_z;
    u8 unknown_FA[2];
    u8 effect_flag;
    u8 effect_flag2;
    u8 unknown_FE[0x34];
    s8 step_x;
    s8 step_z;
    u8 unknown_134[2];
    s16 destination_x;
    s16 destination_z;
    u16 unknown_13A;
    u16 phase;
    u8 unknown_13E[0x4A];
    u8 mode;
} State;

extern void func_0809D66C(s8, s8 *, s8 *);
extern void func_0809836C(void *, u16, s8, u16);
extern s32 func_08099C34(void *);
extern u32 func_08099C64(const void *);
extern void func_08141520(u16);
extern void func_080A92E4(u16, s16, s16, s16, u32);
extern void func_0809A570(void *, u32, u32);
/* Both byte output pointers are consumed by the full captured A8390/A1D84 chain. */
extern void func_080A8390(s8, s8, s8 *, s8 *);
extern u32 func_08002804(void);
extern s32 func_08142950(s32, s32);
extern void func_080E2C00(const void *, s16, s16, s16, u8, u8);
extern u8 func_080A9E6C(void *, s32);

/* Complete [0x080AB358, 0x080AB672): 794 bytes.
 * Local call views are conditional structural ABI views of the saved entries. */
u32 func_080AB358(State *state, Actor *target, u32 unused, const void *effect)
{
    Motion *motion;
    s32 event;
    s8 first;
    s8 second;
    u8 moving;

    switch (state->phase) {
    case 0:
        state->flags |= 2;
        state->actor->flags &= ~1;
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->destination_x = (((target->x >> 5) - state->step_x * 4) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z * 4) << 5) + 16;
        state->step_x *= -1;
        state->step_z *= -1;
        state->motion.destination = target->y << 8;
        state->motion.height = (target->y - 0x30) << 8;
        state->motion.velocity = 0x800;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        state->phase = 1;
        break;
    case 1:
        event = func_08099C34(state->actor);
        if (event == 0) {
            func_08141520(0x80);
            if (state->mode == 0) {
                func_080A92E4(0, target->x, target->y, target->z, 0x15);
            } else {
                func_0809836C(target, 5, target->direction, 0);
                func_0809A570(target, 0, 0x8000);
                func_080A8390(state->actor->direction, target->direction, &first, &second);
                if (first)
                    func_0809A570(target, 0, 0x200);
                if (second)
                    func_0809A570(target, 0, 0x400);
                state->effect_x = state->step_x * 16 + target->x;
                state->effect_y = (s16)(func_08142950((s16)func_08002804(), 9) + 8) + target->y;
                state->effect_z = state->step_z * 16 + target->z;
                state->effect_flag = 0;
                state->effect_flag2 = 0;
                func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                             state->effect_flag, event);
            }
        }
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->actor->y = state->motion.height >> 8;
        func_080A9E6C(state, 4);
        if (func_08099C64(state->actor)) {
            func_0809836C(state->actor, 3, state->direction, 0);
            state->motion.destination = (target->y - 0x30) << 8;
            state->motion.height = target->y << 8;
            state->motion.velocity = 0x800;
            state->actor->y = state->motion.height >> 8;
            state->phase = 2;
        }
        break;
    case 2:
        if (state->step_x)
            state->actor->x += state->step_x * 4;
        if (state->step_z)
            state->actor->z += state->step_z * 4;
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0) {
            motion->height = motion->destination;
            moving = 0;
        } else {
            moving = 1;
        }
        state->actor->y = state->motion.height >> 8;
        if (!moving) {
            state->actor->flags |= 1;
            state->flags = 0;
            return 0;
        }
        break;
    }
    return 1;
}
