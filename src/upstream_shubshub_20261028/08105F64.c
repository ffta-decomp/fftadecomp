/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08105F64.c
 * Original SHA-256: 85f0012e9cbbeccf48f74123796fe271d447b1378108cabf35473ad8cc5a4508
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
    EffectMotion motion;
    void *animation;
    void *overlay;
    void *script;
    void *startup;
    void *object;
    void *attachment;
    void *controller;
} EffectState;

extern const u8 data_083A00B8[];
extern const u8 data_083A0100[];
extern const u8 data_083A0148[];
extern const u8 data_083A015C[];
extern const u8 data_088F4680[];
extern const u8 data_08948834[];
extern const u8 data_0894D690[];
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
extern void func_080D7220(const void *data, u32 index, u32 mode,
                         s16 x, s16 y, u32 flags);
extern void *func_080D4704(const void *data, void *parent);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D3F08(void *script);
extern void *func_080D4774(void *overlay);
extern u32 func_080035A8(u8 layer);
extern void *func_080D6134(void *animation);
extern void *func_080DBA5C(void *attachment);

/* Complete [0x08105F64, 0x081060FC): 408 bytes, 166 instructions. */
u32 func_08105F64(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0: {
        void *object;
        u32 option;

        state->option = command->option;
        object = command->object;
        state->object = object;
        option = 6;
        if (state->option)
            option = 0;
        state->startup = func_080E03F8(object, data_083A00B8, option,
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
                                            &state->motion, data_083A0100,
                                            context);
            state->attachment = func_080DCFE4(unit, data_083A0148, 12, 0x3C,
                                             4, context, 0x3C);
            state->controller = func_080DFD8C(data_083A015C, 2, 4, 0, context);
            state->delay = 19;
            command->state++;
        } else {
            command->state = 2;
        }
        break;
    case 0x101:
        state->delay--;
        if (state->delay)
            break;
        func_080D7220(data_088F4680, 0, 2, state->x, state->y, 0);
        state->overlay = func_080D4704(data_08948834, context);
        state->script = func_080D3E9C(data_0894D690, context);
        command->state++;
        break;
    case 0x102:
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay)
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
