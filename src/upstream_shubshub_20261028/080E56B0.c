/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E56B0.c
 * Original SHA-256: 2ca4476b73986d1195708f60d0b2a94b17d16df8bce7536b2d234d26eeee47ac
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E56B0..0x080E5978: 712 bytes. */
typedef struct {
    s16 value;
    u8 unknown_02[10];
} HeightTransition;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 mode;
} StagedEffectCommand;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03;
    s16 x;
    s16 y;
    HeightTransition transition;
    void *target;
    u8 particle_a_data[8];
    u32 particle_a;
    u8 particle_b_data[4];
    u32 particle_b;
    u32 sprite;
    u32 effect_a;
    u32 effect_b;
    u32 main_effect;
    u32 load_handle;
    void *object;
    u32 object_effect;
    u32 extra_effect;
} StagedEffectState;

extern const u8 data_08396FF4[];
extern const u8 data_088EE8B0[];
extern const u8 data_0894D7F0[];
extern const u8 data_08397030[];
extern const u8 data_08397078[];
extern const u8 data_088ED5BC[];
extern const u8 data_08397060[];
extern const u8 data_08949374[];
extern const u8 data_0894D69C[];
extern const u8 data_08949F18[];
extern u16 g_control_flags_03000940;

extern u32 func_080E03F8(void *object, const void *resource, u32 type,
                         u32 enabled, u32 flags, void *context);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32 handle);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD748(void *target, s16 *x, s16 *y, s16 *z);
extern void func_080D49FC(u32 index, u32 type, u32 flags, s16 x, s16 y);
extern u32 func_080D4B64(u32 index, const void *resource, u16 size, u32 type);
extern void func_0800BDA4(u32 sprite, u8 enabled);
extern u32 func_080035A8(u32 index);
extern u32 func_080D3E9C(const void *resource, void *context);
extern u32 func_080D6098(s16 x, s16 y, u32 flags, u32 enabled,
                         u32 count, void *data, const void *resource,
                         void *context);
extern void func_080E0608(HeightTransition *transition, s16 from,
                         s16 to, u16 duration);
extern u32 func_080DFD8C(const void *resource, u8 parameter, u32 type,
                         u32 flags, void *context);
extern void func_080E064C(HeightTransition *transition);
extern u8 func_080E0690(HeightTransition *transition);
extern u32 func_080D3F08(u32 handle);
extern void func_080D4D14(u32 sprite, u32 flags);
extern void func_0800BC4C(u32 index, u32 value);
extern u32 func_080D4704(const void *resource, void *context);
extern void func_080D3F84(u32 handle, u32 first, u32 second);
extern u32 func_080DCFE4(void *target, u32 first, u32 second, u32 third,
                         u32 fourth, void *context, u32 sixth);
extern u32 func_080D4774(u32 handle);
extern u32 func_080D6134(u32 handle);
extern u32 func_080DBA5C(u32 handle);

u32 func_080E56B0(void *context, StagedEffectCommand *command,
                  StagedEffectState *state)
{
    switch (command->state) {
    case 0: {
        u32 type;

        state->mode = command->mode;
        state->object = command->object;
        type = 5;
        if (state->mode)
            type = 0;
        state->load_handle = func_080E03F8(state->object, data_08396FF4,
            type, 1, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->load_handle = func_080E05DC(state->load_handle);
        if (state->load_handle)
            break;
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        state->target = func_080DD748(func_080DD4A4(state->object, 0),
            &state->x, &state->y, 0);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->sprite = func_080D4B64(0, data_088EE8B0, 0x3B4, 7);
        func_0800BDA4(state->sprite, 1);
        {
            u32 mask = func_080035A8(2);
            u32 flags = g_control_flags_03000940;

            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        state->main_effect = func_080D3E9C(data_0894D7F0, context);
        state->particle_a = func_080D6098(state->x, state->y, 0, 1, 2,
            state->particle_a_data, data_08397030, context);
        func_080E0608(&state->transition, state->y, (s16)(state->y - 24), 120);
        state->extra_effect = func_080DFD8C(data_08397078, 3, 4, 0, context);
        command->state++;
        break;
    case 0x101:
        func_080E064C(&state->transition);
        func_0800BC08(0, state->x, state->transition.value);
        if (!func_080E0690(&state->transition))
            break;
        state->main_effect = func_080D3F08(state->main_effect);
        if (state->main_effect)
            break;
        func_080D4D14(state->sprite, 0);
        state->sprite = 0;
        {
            u32 mask = func_080035A8(2);
            u32 flags = g_control_flags_03000940;

            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        func_080D49FC(0, 3, 0, state->x, (s16)(state->y - 8));
        func_0800BC4C(0, 1);
        state->sprite = func_080D4B64(0, data_088ED5BC, 0x39B, 6);
        func_0800BDA4(state->sprite, 1);
        {
            u32 mask = func_080035A8(3);
            u32 flags = g_control_flags_03000940;

            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        state->particle_b = func_080D6098(state->x, state->y, 0, 1, 1,
            state->particle_b_data, data_08397060, context);
        state->effect_a = func_080D4704(data_08949374, context);
        state->main_effect = func_080D3E9C(data_0894D69C, context);
        func_080D3F84(state->main_effect, 8, 255);
        state->effect_b = func_080D4704(data_08949F18, context);
        state->object_effect = func_080DCFE4(func_080DD4A4(state->object, 0),
            0, 12, 0, 4, context, 40);
        command->state++;
        break;
    case 0x102:
        state->main_effect = func_080D3F08(state->main_effect);
        if (state->main_effect)
            break;
        state->effect_a = func_080D4774(state->effect_a);
        if (state->effect_a)
            break;
        {
            u32 mask = func_080035A8(3);
            u32 flags = g_control_flags_03000940;

            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        state->particle_a = func_080D6134(state->particle_a);
        if (state->particle_a)
            break;
        state->particle_b = func_080D6134(state->particle_b);
        if (state->particle_b)
            break;
        state->object_effect = func_080DBA5C(state->object_effect);
        if (state->object_effect)
            break;
        state->effect_b = func_080D4774(state->effect_b);
        if (state->effect_b)
            break;
        func_080D4D14(state->sprite, 0);
        state->sprite = 0;
        command->state = 2;
        break;
    }
    return 0;
}
