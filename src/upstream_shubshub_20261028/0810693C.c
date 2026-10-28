/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810693C.c
 * Original SHA-256: 40005b530d94898383bd5f32454c4ec0f540d087c1db5c26b5dadfb83802ae81
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0810693C..0x08106AF4: 440 bytes, 180 instructions. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 variant;
} EffectCommand;

typedef struct {
    u16 timer;
    u8 variant;
    u8 unknown_03;
    s16 x;
    s16 y;
    u32 position;
    void *data;
    u8 unknown_10[8];
    void *effect;
    void *overlay;
    void *animation;
    void *transition;
    void *object;
    void *attachment;
    void *controller;
} EffectState;

extern const u8 data_083A0634[];
extern const u8 data_083A067C[];
extern const u8 data_083A06C4[];
extern const u8 data_083A06D8[];
extern const u8 data_088F46C0[];
extern const u8 data_08948D00[];
extern const u8 data_0894D69C[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *descriptor, u32 mode,
                         u32 priority, u32 flags, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *transition);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void *func_080D6098(s16 x, s16 y, u32 index, u32 mode,
                         u32 priority, void **data, const void *descriptor,
                         void *parent);
extern void *func_080DCFE4(void *object, const void *descriptor, u32 mode,
                         u32 value, u32 priority, void *parent, u32 flags);
extern void *func_080DFD8C(const void *descriptor, u32 mode, u32 priority,
                         u32 flags, void *parent);
extern void func_080D7220(const void *asset, u32 index, u32 mode,
                         s16 x, s16 y, u32 flags);
extern void *func_080D4704(const void *descriptor, void *parent);
extern void *func_080D3E9C(const void *descriptor, void *parent);
extern void func_080DF8CC(u32 position);
extern void *func_080D3F08(void *animation);
extern void *func_080D4774(void *overlay);
extern u32 func_080035A8(u32 index);
extern void *func_080D6134(void *effect);
extern void *func_080DBA5C(void *attachment);

u32 func_0810693C(void *task, EffectCommand *command, EffectState *state)
{
    u16 *control_flags;
    u32 mask;
    u32 flags;

    switch (command->state) {
    case 0:
    {
        void *object;
        u32 mode;

        state->variant = command->variant;
        object = command->object;
        state->object = object;
        mode = 6;
        if (state->variant) {
            mode = 0;
        }
        state->transition = func_080E03F8(object, data_083A0634,
                                         mode, 1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
    {
        void *object;

        state->transition = func_080E05DC(state->transition);
        if (state->transition) {
            break;
        }
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        object = func_080DD4A4(state->object, 0);
        state->position = func_080DD748(object, &state->x, &state->y, 0);
        state->effect = func_080D6098(state->x, state->y, 0, 1, 3,
                                     &state->data, data_083A067C, task);
        state->attachment = func_080DCFE4(object, data_083A06C4, 0xC,
                                         0x69, 4, task, 0x69);
        state->controller = func_080DFD8C(data_083A06D8, 3, 4, 0, task);
        state->timer = 15;
        command->state++;
        break;
    }
    case 0x101:
        if (--state->timer) {
            break;
        }
        func_080D7220(data_088F46C0, 0, 2, state->x, (s16)(state->y - 12), 0);
        state->overlay = func_080D4704(data_08948D00, task);
        state->animation = func_080D3E9C(data_0894D69C, task);
        state->timer = 50;
        command->state++;
        break;
    case 0x102:
        if (state->timer) {
            if (--state->timer) {
                break;
            }
            func_080DF8CC(state->position);
        }
        state->animation = func_080D3F08(state->animation);
        if (state->animation) {
            break;
        }
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay) {
            break;
        }
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
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
