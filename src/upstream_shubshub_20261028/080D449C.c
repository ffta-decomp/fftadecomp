/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D449C.c
 * Original SHA-256: ff673f186c888dc4214e0c423b30bcf3c075bc0fc4e3eab5acb7e33b27fa035c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D449C..0x080D45D0: 308 bytes, 143 instructions, including a pool. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    const u8 *descriptor;
    u8 unknown_08[0xC];
    u16 flags;
} AnimationCommand;

typedef struct {
    const u8 *descriptor;
    u16 resource;
    u8 kind;
    u8 flags;
    u16 delay;
    u16 frame;
    u16 timer;
    u8 unknown_0E[2];
    void *handle;
    void *task;
} AnimationState;

extern void func_08148498(void *handle);
extern u32 func_081485D4(void *handle);
extern u32 func_08005BB0(void *task);
extern void func_08005B58(void *task);
extern void func_080D4444(AnimationState *animation);
extern void func_080D4224(AnimationState *animation);

u32 func_080D449C(void *context, AnimationCommand *command, AnimationState *animation)
{
    switch (command->state) {
    case 0: {
        const u8 *descriptor = command->descriptor;
        const u8 *active_descriptor;
        u32 low;

        animation->descriptor = descriptor;
        animation->flags = command->flags;
        animation->resource = descriptor[0];
        if (descriptor[1] & 2) {
            animation->resource = descriptor[0] + 0x100;
        }
        active_descriptor = animation->descriptor;
        animation->kind = active_descriptor[2];
        low = active_descriptor[4];
        animation->delay = (active_descriptor[5] << 8) | low;
        break;
    }
    case 1:
        if (animation->handle) {
            func_08148498(animation->handle);
            animation->handle = 0;
        }
        break;
    case 0x100:
        if (animation->delay == 0) {
            func_080D4444(animation);
            command->state = 0x102;
        } else {
            command->state++;
        }
        break;
    case 0x101:
        animation->delay--;
        if (animation->delay == 0) {
            func_080D4444(animation);
            command->state++;
        }
        break;
    case 0x102:
        if (!(animation->flags & 0x80)) {
            u32 finished = 0;

            if (animation->timer) {
                animation->timer--;
                if (animation->timer == 0) {
                    func_080D4224(animation);
                    finished = 1;
                }
            } else if (animation->handle) {
                if (func_081485D4(animation->handle)) {
                    func_08148498(animation->handle);
                    animation->handle = 0;
                    finished = 1;
                }
            } else if (func_08005BB0(animation->task)) {
                func_08005B58(animation->task);
                animation->task = 0;
                finished = 1;
            }
            if (finished) {
                animation->frame++;
                if (animation->frame == animation->descriptor[3]) {
                    if (animation->flags & 1) {
                        animation->frame = 0;
                    } else {
                        command->state = 2;
                        finished = 0;
                    }
                }
                if (finished) {
                    func_080D4444(animation);
                }
            }
        }
        break;
    }
    return 0;
}
