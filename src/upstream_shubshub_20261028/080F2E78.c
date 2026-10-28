/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F2E78.c
 * Original SHA-256: 238fd9a20d4a3d17297ab1229cf3dd279e4196c245e80e247c7503275552d73a
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
    s16 x;
    s16 y;
    u8 unknown_04;
    u8 kind;
    u8 ready;
    u8 unknown_07;
    u32 process;
    void *position_source;
    void *object;
    u32 load;
    u8 particle_data[20];
    u32 particle;
    u32 effect;
    u32 object_effect;
    u32 preparation;
    u32 script;
} EffectState;

extern const u8 data_0839A94C[];
extern const u8 data_0839AA08[];
extern const u8 data_0839A97C[];
extern const u8 data_0894ABA0[];
extern const u8 data_0839A9F4[];
extern const u8 data_0839AA10[];

extern u32 func_080E03F8(void *object, const void *resource, u32 kind,
                        u32 value, u32 flags, void *context);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32 load);
extern u8 func_080D3B54(void *object);
extern u32 func_080DDF68(void *object, u32 *process, u32 duration, u32 mode,
                        u8 *ready, const void *resource, u32 first, u32 second,
                        void *context);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD4C4(void *object);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern u32 func_080D6098(s16 x, s16 y, u32 value, u32 mode, u32 count,
                        void *storage, const void *resource, void *context);
extern u32 func_080D4704(const void *resource, void *context);
extern u32 func_080DCFE4(void *object, const void *resource, u32 first,
                        u32 second, u32 mode, void *context, u32 third);
extern u32 func_080DFD8C(const void *resource, u32 first, u32 second,
                        u32 third, void *context);
extern u8 func_080DE1F0(u32 process);
extern u32 func_080D6134(u32 particle);
extern u32 func_080D4774(u32 effect);
extern u32 func_080DBA5C(u32 effect);

u32 func_080F2E78(void *context, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0:
    {
        u32 kind;
        state->kind = command->kind;
        state->object = command->object;
        kind = 4;
        if (state->kind)
            kind = 0;
        state->load = func_080E03F8(state->object, data_0839A94C, kind,
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
        state->preparation = func_080DDF68(state->object, &state->process,
                                           60, 2, &state->ready,
                                           data_0839AA08, 0, 0, context);
        command->state++;
        break;
    case 0x101:
    {
        void *object;
        if (!state->ready)
            break;
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        object = func_080DD4A4(state->object, 0);
        state->position_source = func_080DD4C4(object);
        func_080DBDC8(state->position_source, &state->x, &state->y);
        state->particle = func_080D6098(state->x, state->y, 0, 1, 5,
                                        state->particle_data, data_0839A97C,
                                        context);
        state->effect = func_080D4704(data_0894ABA0, context);
        state->object_effect = func_080DCFE4(object, data_0839A9F4, 12,
                                            0x67, 4, context, 0x67);
        state->script = func_080DFD8C(data_0839AA10, 2, 4, 0, context);
        command->state++;
        break;
    }
    case 0x102:
        if (!func_080DE1F0(state->process))
            break;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->effect = func_080D4774(state->effect);
        if (state->effect)
            break;
        state->object_effect = func_080DBA5C(state->object_effect);
        if (state->object_effect)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
