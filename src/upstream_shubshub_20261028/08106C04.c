/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08106C04.c
 * Original SHA-256: 4cdf762eeb47bbc634b4a27a40a575475a0592e178493a908765242024e16fbd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08106C04..0x08106DA0: 412 bytes. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 kind;
} EffectCommand;

typedef struct {
    u16 timer;
    u8 kind;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *target;
    u8 particle_data[8];
    u32 particle;
    u32 effect;
    u32 main_effect;
    u32 load;
    void *object;
    u32 object_effect;
    u32 script;
} EffectState;

extern const u8 data_083A07FC[];
extern const u8 data_083A0838[];
extern const u8 data_083A0868[];
extern const u8 data_083A087C[];
extern const u8 data_088F4680[];
extern const u8 data_08948C7C[];
extern const u8 data_0894D6A8[];
extern u16 g_control_flags_03000940;

extern u32 func_080E03F8(void *object, const void *resource, u32 kind,
                        u32 value, u32 flags, void *context);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32 load);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD748(void *actor, s16 *x, s16 *y, u32 value);
extern u32 func_080D6098(s16 x, s16 y, u32 value, u32 mode, u32 count,
                        void *storage, const void *resource, void *context);
extern u32 func_080DCFE4(void *object, const void *resource, u32 first,
                        u32 second, u32 mode, void *context, u32 third);
extern u32 func_080DFD8C(const void *resource, u32 first, u32 second,
                        u32 third, void *context);
extern void func_080D7220(const void *resource, u32 first, u32 second,
                         s16 x, s16 y, u32 third);
extern u32 func_080D4724(const void *resource, void *context, u32 value);
extern u32 func_080D3E9C(const void *resource, void *context);
extern u32 func_080D3F08(u32 effect);
extern u32 func_080D4774(u32 effect);
extern u32 func_080035A8(u32 index);
extern u32 func_080D6134(u32 particle);
extern u32 func_080DBA5C(u32 effect);

u32 func_08106C04(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0:
    {
        u32 kind;
        state->kind = command->kind;
        state->object = command->object;
        kind = 5;
        if (state->kind)
            kind = 0;
        state->load = func_080E03F8(state->object, data_083A07FC, kind,
                                     1, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
    {
        void *actor;
        if ((state->load = func_080E05DC(state->load)) != 0)
            break;
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        actor = func_080DD4A4(state->object, 0);
        state->target = func_080DD748(actor, &state->x, &state->y, 0);
        state->particle = func_080D6098(state->x, state->y, 0, 1, 2,
                                        state->particle_data, data_083A0838,
                                        context);
        state->object_effect = func_080DCFE4(actor, data_083A0868,
                                            12, 0x55, 4, context, 0x55);
        state->script = func_080DFD8C(data_083A087C, 3, 4, 0, context);
        state->timer = 17;
        command->state++;
        break;
    }
    case 0x101:
        if (--state->timer != 0)
            break;
        func_080D7220(data_088F4680, 0, 2, state->x, state->y - 8, 0);
        state->effect = func_080D4724(data_08948C7C, context, 3);
        state->main_effect = func_080D3E9C(data_0894D6A8, context);
        command->state++;
        break;
    case 0x102:
    {
        u32 mask;
        u32 flags;
        state->main_effect = func_080D3F08(state->main_effect);
        if (state->main_effect)
            break;
        state->effect = func_080D4774(state->effect);
        if (state->effect)
            break;
        mask = func_080035A8(2);
        flags = g_control_flags_03000940;
        flags &= ~mask;
        g_control_flags_03000940 = flags;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->object_effect = func_080DBA5C(state->object_effect);
        if (state->object_effect)
            break;
        command->state = 2;
        break;
    }
    }
    return 0;
}
