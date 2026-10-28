/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08102FEC.c
 * Original SHA-256: ca096c89d53fb4b07a60b87d5bf7162c4f2819c705c9848c3c9a67d80558d9f7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 kind;
} EffectCommand;

typedef struct {
    u8 kind;
    u8 unknown_01;
    u16 timer;
    s16 x;
    s16 y;
    u8 particle_data[16];
    u32 particle;
    u32 effect;
    void *object;
    void *actor;
    u32 load;
    u32 transition;
    u32 object_effect;
    u32 script;
} EffectState;

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} ActorData;

extern const u8 data_0839F11C[];
extern const u8 data_0839F134[];
extern const u8 data_08949DD8[];
extern const u8 data_0839F194[];
extern const u8 data_0839F1A8[];

extern u32 func_080E03F8(void *object, const void *resource, u32 kind,
                        u32 value, u32 flags, void *context);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32 load);
extern u8 func_080D3B54(void *object);
extern void *func_080DD4B4(void *object, u32 index);
extern void func_080DE10C(void *actor, u16 duration);
extern u8 func_080DE1F0(void *actor);
extern s8 func_080DBC88(void *actor);
extern u32 func_080DF7A0(void *actor, u32 first, u32 mode, u32 second,
                        u32 third, void *context);
extern void func_080DF950(u32 transition, u16 value);
extern u32 func_080DBA5C(u32 effect);
extern u8 func_080D8858(void *object, u32 index);
extern void func_080DBDC8(void *actor, s16 *x, s16 *y);
extern u32 func_080D6098(s16 x, s16 y, u32 value, u32 mode, u32 count,
                        void *storage, const void *resource, void *context);
extern u32 func_080D4704(const void *resource, void *context);
extern void *func_080DD4A4(void *object, u32 index);
extern u32 func_080DCFE4(void *object, const void *resource, u32 first,
                        u32 second, u32 mode, void *context, u32 third);
extern u32 func_080DFD8C(const void *resource, u32 first, u32 second,
                        u32 third, void *context);
extern ActorData *func_080DD350(void *actor);
extern u32 func_080D4774(u32 effect);
extern u32 func_080D6134(u32 particle);

u32 func_08102FEC(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0:
    {
        u32 kind;
        state->kind = command->kind;
        state->object = command->object;
        kind = 2;
        if (state->kind)
            kind = 0;
        state->load = func_080E03F8(state->object, data_0839F11C, kind,
                                     0, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->load = func_080E05DC(state->load);
        if (state->load)
            break;
        if (func_080D3B54(state->object)) {
            command->state = 2;
            break;
        }
        state->actor = func_080DD4B4(state->object, 0);
        func_080DE10C(state->actor, 140);
        command->state++;
        break;
    case 0x101:
    {
        s32 actor_kind;
        u32 mode;
        if (!func_080DE1F0(state->actor))
            break;
        actor_kind = func_080DBC88(state->actor);
        mode = 1;
        if (actor_kind <= 1)
            mode = 0;
        state->transition = func_080DF7A0(state->actor, 5, mode, 4, 0,
                                           context);
        func_080DF950(state->transition, 144);
        command->state++;
        break;
    }
    case 0x102:
        state->transition = func_080DBA5C(state->transition);
        if (state->transition)
            break;
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        func_080DBDC8(state->actor, &state->x, &state->y);
        state->particle = func_080D6098(state->x, state->y, 0, 1, 4,
                                        state->particle_data, data_0839F134,
                                        context);
        state->effect = func_080D4704(data_08949DD8, context);
        state->object_effect = func_080DCFE4(
            func_080DD4A4(state->object, 0), data_0839F194, 12, 20, 4,
            context, 20);
        state->script = func_080DFD8C(data_0839F1A8, 1, 4, 0, context);
        state->timer = 20;
        command->state++;
        break;
    case 0x103:
        if (state->timer) {
            if (--state->timer == 0) {
                ActorData *actor = func_080DD350(state->actor);
                actor->flags |= 0x20000;
            }
        }
        state->effect = func_080D4774(state->effect);
        if (state->effect)
            break;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->object_effect = func_080DBA5C(state->object_effect);
        if (state->object_effect)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
