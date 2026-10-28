/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08106778.c
 * Original SHA-256: ba43ca2a989bc3d37446457b5631c1edae5f7682798263fa7636cae062df6f5e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[0xE];
    u16 option;
} EffectCommand;

typedef struct {
    u8 unknown_00[0xC];
} EffectMotion;

typedef struct {
    u16 delay;
    u8 option;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *entity;
    void *display;
    EffectMotion motion;
    void *animation;
    void *script;
    void *startup;
    void *object;
    void *attachment;
    void *controller;
} EffectState;

extern const u8 data_083A054C[];
extern const u8 data_083A0588[];
extern const u8 data_083A05D0[];
extern const u8 data_083A05E4[];
extern const u8 data_088ED4A4[];
extern const u8 data_0894D6C4[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *data, u32 option,
                          u32 mode, u32 flags, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *startup);
extern u8 func_080D8858(void *object, u32 mode);
extern void *func_080DD4A4(void *object, u32 mode);
extern void *func_080DD748(void *unit, s16 *x, s16 *y, u32 mode);
extern void *func_080D6098(s16 x, s16 y, u32 mode, u32 option, u32 count,
                          EffectMotion *motion, const void *data, void *parent);
extern void *func_080DCFE4(void *unit, const void *data, u32 count, u32 value,
                          u32 mode, void *parent, u32 extra);
extern void *func_080DFD8C(const void *data, u32 mode, u32 count,
                          u32 flags, void *parent);
extern void func_080D49FC(u8 index, u8 mode, u16 value, s16 x, s16 y);
extern void *func_080D4B64(u8 index, const void *data, u16 value, u8 mode);
extern u32 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *parent);
extern void func_080DF8CC(void *entity);
extern void *func_080D3F08(void *script);
extern void *func_080D4D2C(void *display, u8 mode);
extern void *func_080D6134(void *animation);
extern void *func_080DBA5C(void *attachment);

/* Complete [0x08106778, 0x0810693C): 452 bytes, 185 instructions. */
u32 func_08106778(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0: {
        void *object;
        u32 option;

        state->option = command->option;
        object = command->object;
        state->object = object;
        option = 5;
        if (state->option)
            option = 0;
        state->startup = func_080E03F8(object, data_083A054C, option,
                                      1, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->startup = func_080E05DC(state->startup);
        if (state->startup)
            break;
        if (func_080D8858(state->object, 0)) {
            void *unit = func_080DD4A4(state->object, 0);

            state->entity = func_080DD748(unit, &state->x, &state->y, 0);
            state->animation = func_080D6098(state->x, state->y, 0, 1, 3,
                                            &state->motion, data_083A0588,
                                            context);
            state->attachment = func_080DCFE4(unit, data_083A05D0, 12, 0x55,
                                             4, context, 0x55);
            state->controller = func_080DFD8C(data_083A05E4, 2, 4, 0, context);
            state->delay = 20;
            command->state++;
        } else {
            command->state = 2;
        }
        break;
    case 0x101:
        state->delay--;
        if (state->delay)
            break;
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->display = func_080D4B64(0, data_088ED4A4, 0x3DD, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;

            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        state->script = func_080D3E9C(data_0894D6C4, context);
        state->delay = 16;
        command->state++;
        break;
    case 0x102:
        if (state->delay) {
            state->delay--;
            if (state->delay)
                break;
            func_080DF8CC(state->entity);
        }
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        state->display = func_080D4D2C(state->display, 0);
        if (state->display)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;

            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        state->animation = func_080D6134(state->animation);
        if (state->animation)
            break;
        state->attachment = func_080DBA5C(state->attachment);
        if (state->attachment)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
