/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08102DC0.c
 * Original SHA-256: 0bec0a75fdd466e63e83062a916527672fda316b53438001e0ccb52eb2725ef8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08102DC0..0x08102FEC: 556 bytes, 233 instructions. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 variant;
} EffectCommand;

typedef struct {
    s16 x;
    s16 y;
    u16 timer;
    u8 unknown_06;
    u8 variant;
    u8 ready;
    u8 unknown_09[3];
    void *movement;
    u32 position;
    void *object;
    void *transition;
    void *data;
    void *effect;
    void *animation;
    void *overlay;
    void *attachment;
    void *sequence;
    void *controller;
} EffectState;

extern const u8 data_0839F094[];
extern const u8 data_0839F0F0[];
extern const u8 data_088F5A94[];
extern const u8 data_0894DA1C[];
extern const u8 data_0839F0C4[];
extern const u8 data_0894848C[];
extern const u8 data_0839F0DC[];
extern const u8 data_0839F0F4[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *descriptor, u32 mode,
                         u32 priority, u32 flags, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *transition);
extern u8 func_080D3B54(void *object);
extern void *func_080DDF68(void *object, void **movement, u32 id, u32 mode,
                         u8 *ready, const void *descriptor, u32 priority,
                         u32 flags, void *parent);
extern void func_080DBFFC(void *object, u32 mode);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void func_080D7220(const void *asset, u32 index, u32 mode,
                         s16 x, s16 y, u32 flags);
extern void *func_080D3E9C(const void *descriptor, void *parent);
extern u8 func_080DD580(void *object);
extern void *func_080D6098(s16 x, s16 y, u32 index, u32 mode,
                         u32 priority, void **data, const void *descriptor,
                         void *parent);
extern void *func_080D4724(const void *descriptor, void *parent, u32 duration);
extern void *func_080DCFE4(void *object, const void *descriptor, u32 mode,
                         u32 value, u32 priority, void *parent, u32 flags);
extern void *func_080DFD8C(const void *descriptor, u32 mode, u32 priority,
                         u32 flags, void *parent);
extern u8 func_080DE1F0(void *movement);
extern void *func_080D3F08(void *animation);
extern u32 func_080035A8(u32 index);
extern void *func_080D4774(void *overlay);
extern void *func_080D6134(void *effect);
extern void *func_080DBA5C(void *attachment);

u32 func_08102DC0(void *task, EffectCommand *command, EffectState *state)
{
    u16 *control_flags;
    u32 mask;
    u32 flags;

    switch (command->state) {
    case 0:
    {
        u32 mode;
        state->variant = command->variant;
        state->object = command->object;
        mode = 4;
        if (state->variant) {
            mode = 0;
        }
        state->transition = func_080E03F8(state->object, data_0839F094,
                                         mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
    {
        u8 busy;
        state->transition = func_080E05DC(state->transition);
        if (state->transition) {
            break;
        }
        busy = func_080D3B54(state->object);
        if (busy) {
            command->state = 2;
            break;
        }
        state->sequence = func_080DDF68(state->object, &state->movement,
                                       0x8007, 1, &state->ready,
                                       data_0839F0F0, 5, busy, task);
        command->state++;
        break;
    }
    case 0x101:
        if (!state->ready) {
            break;
        }
        func_080DBFFC(state->object, 0);
        state->timer = 10;
        command->state++;
        /* Continue into the countdown phase. */
    case 0x102:
    {
        void *object;
        u32 busy;
        u32 mode;
        if (state->timer && --state->timer) {
            break;
        }
        busy = func_080D8B4C();
        if (busy) {
            break;
        }
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        object = func_080DD4A4(state->object, 0);
        state->position = func_080DD748(object, &state->x, &state->y, 0);
        func_080D7220(data_088F5A94, 0, 2, state->x, state->y, busy);
        state->animation = func_080D3E9C(data_0894DA1C, task);
        mode = 2;
        if (func_080DD580(object)) {
            state->effect = func_080D6098(state->x, state->y, 0, 1, 1,
                                         &state->data, data_0839F0C4, task);
            state->overlay = func_080D4724(data_0894848C, task, 0x50);
        } else {
            mode = 1;
        }
        state->attachment = func_080DCFE4(object, data_0839F0DC, 0xC,
                                         0x5A, 4, task, 0x5A);
        state->controller = func_080DFD8C(data_0839F0F4, mode, 4, 0, task);
        command->state++;
        break;
    }
    case 0x103:
        if (!func_080DE1F0(state->movement)) {
            break;
        }
        state->animation = func_080D3F08(state->animation);
        if (state->animation) {
            break;
        }
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay) {
            break;
        }
        state->effect = func_080D6134(state->effect);
        if (state->effect) {
            break;
        }
        state->attachment = func_080DBA5C(state->attachment);
        if (state->attachment) {
            break;
        }
        command->state = 2;
        break;
    }
    return 0;
}
