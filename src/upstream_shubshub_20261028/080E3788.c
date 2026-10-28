/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E3788.c
 * Original SHA-256: ace3c1f1a608f4c9115bf452f3aab9418568d295ac7f759fda155206bf210e7c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E3788..0x080E3A10: 648 bytes. */
typedef struct {
    s16 value;
    u8 unknown_02[10];
} PositionTransition;

typedef struct {
    u16 state;
    u8 unknown_02[6];
    void *object;
    u8 unknown_0C[8];
    s16 angle;
} PositionEffectCommand;

typedef struct {
    s16 x;
    s16 y;
    u16 timer;
    u8 special;
    u8 index;
    u8 kind;
    u8 unknown_09[3];
    void *object;
    u32 load_handle;
    u32 sprite;
    u32 effect_a;
    u32 effect_b;
    u32 unknown_20;
    PositionTransition transition;
    u32 effect_handle;
} PositionEffectState;

extern const void *const data_0839639C[];
extern const u8 data_083963E4[];
extern const void *const data_083963C0[];
extern const u8 data_083963ED[];
extern const void *const data_083963F8[];
extern const u16 data_08396440[];
extern const void *const data_0839641C[];
extern const u16 data_08396452[];
extern const u8 data_0894DE6C[];
extern const u8 data_0894CF34[];
extern const void *const data_0839646C[];
extern const u8 data_08396474[];
extern u16 g_control_flags_03000940;

extern u32 func_080DD478(void *object);
extern u8 func_080CE410(u32 actor);
extern void func_080DE10C(void *object, u16 value);
extern void func_080D38B4(void);
extern u8 func_080DBC88(void *object);
extern u32 func_080D7A70(const void *resource, u8 palette, void *context);
extern void func_080DC014(void *object);
extern u32 func_080D7ABC(u32 handle);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080E0608(PositionTransition *transition, s16 from,
                         s16 to, u16 duration);
extern void func_080D49FC(u32 index, u32 type, u32 flags, s16 x, s16 y);
extern u32 func_080D4B64(u32 index, const void *resource, u16 size, u32 type);
extern void func_0800BE10(u32 sprite, u8 enabled);
extern void func_0800BDA4(u32 sprite, u8 enabled);
extern u32 func_080035A8(u32 index);
extern u32 func_080D3E9C(const void *resource, void *context);
extern u32 func_080D4704(const void *resource, void *context);
extern u32 func_080DFD8C(const void *resource, u8 parameter, u32 type,
                         u32 flags, void *context);
extern void func_080DE390(void *object);
extern void func_080E064C(PositionTransition *transition);
extern u8 func_080E0690(PositionTransition *transition);
extern u32 func_080D3F08(u32 handle);
extern u32 func_080D4774(u32 handle);
extern void func_080D4D14(u32 sprite, u32 flags);

u32 func_080E3788(void *context, PositionEffectCommand *command,
                  PositionEffectState *state)
{
    switch (command->state) {
    case 0:
        state->object = command->object;
        state->special = 0;
        if (command->angle == 360) {
            state->index = func_080CE410(func_080DD478(state->object));
            state->special = 1;
        } else {
            state->index = command->angle + 57;
        }
        if (state->special == 1)
            func_080DE10C(state->object, 0x48);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->kind = func_080DBC88(state->object);
        if (state->kind == 0 || state->kind == 3)
            state->load_handle = func_080D7A70(data_0839639C[state->index],
                data_083963E4[state->index], context);
        else
            state->load_handle = func_080D7A70(data_083963C0[state->index],
                data_083963ED[state->index], context);
        func_080DC014(state->object);
        command->state++;
        break;
    case 0x101:
        state->load_handle = func_080D7ABC(state->load_handle);
        if (state->load_handle == 0) {
            func_080DBDC8(state->object, &state->x, &state->y);
            if (state->special == 0)
                func_080E0608(&state->transition, 32, 0, 120);
            else
                func_080E0608(&state->transition, 0, 32, 120);
            func_080D49FC(0, 2, 0, state->x,
                (s16)(state->y - state->transition.value));
            if (state->kind == 0 || state->kind == 3)
                state->sprite = func_080D4B64(0, data_083963F8[state->index],
                    data_08396440[state->index], 6);
            else
                state->sprite = func_080D4B64(0, data_0839641C[state->index],
                    data_08396452[state->index], 6);
            if (state->kind > 1)
                func_0800BE10(state->sprite, 1);
            func_0800BDA4(state->sprite, 1);
            {
                u32 mask = func_080035A8(2);
                u32 flags = g_control_flags_03000940;

                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            state->effect_a = func_080D3E9C(data_0894DE6C, context);
            if (state->special == 0)
                state->effect_b = func_080D4704(data_0894CF34, context);
            state->effect_handle = func_080DFD8C(data_0839646C[state->special],
                data_08396474[state->special], 4, 0, context);
            if (state->special == 0)
                state->timer = 96;
            command->state++;
        }
        break;
    case 0x102:
        if (state->timer) {
            if (--state->timer == 0 && state->special == 0)
                func_080DE390(state->object);
        }
        func_080E064C(&state->transition);
        func_0800BC08(0, state->x,
            (s16)(state->y - state->transition.value));
        if (func_080E0690(&state->transition)) {
            state->effect_a = func_080D3F08(state->effect_a);
            if (state->effect_a == 0) {
                state->effect_b = func_080D4774(state->effect_b);
                if (state->effect_b == 0) {
                    func_080D4D14(state->sprite, 0);
                    state->sprite = 0;
                    {
                        u32 mask = func_080035A8(2);
                        u32 flags = g_control_flags_03000940;

                        flags &= ~mask;
                        g_control_flags_03000940 = flags;
                    }
                    if (state->special == 1)
                        func_080DE390(state->object);
                    command->state = 2;
                }
            }
        }
        break;
    }
    return 0;
}
