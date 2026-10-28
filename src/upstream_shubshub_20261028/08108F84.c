/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08108F84.c
 * Original SHA-256: e3ff763c87fdcd41004396a397c2bc0795bd481de61bee05da3d54c25034a729
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command08108F84 {
    u16 state;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 mode;
};

struct Runtime08108F84 {
    u16 timer;
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_07;
    u8 skip;
    u8 unknown_09;
    u8 mode;
    u8 unknown_0B;
    void *actor;
    void *related;
    u32 parameters[1];
    void *movement;
    void *effect_object;
    void *first;
    void *second;
    void *opening;
    void *object;
    void *preparation;
    void *operation;
    void *script;
};

extern const u8 data_083A1254[];
extern const u8 data_088EF398[];
extern const u8 data_0894D90C[];
extern const u8 data_083A1278[];
extern const u8 data_0894AB50[];
extern const u8 data_083A12A4[];
extern const u8 data_083A1290[];
extern const u8 data_083A12AC[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *data, u32 mode,
                          u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080D3B54(void *object);
extern void *func_080DD47C(void *object);
extern void func_080DE10C(void *object, u32 value);
extern void *func_080DE4B0(void *object, u8 *ready, u32 first, u32 second,
                          u32 third, u32 fourth, u32 fifth, void *context);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD4C4(void *object);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080D49FC(u32 first, u32 second, u32 third, s16 x, s16 y);
extern void *func_080D4B64(u8 group, const void *data, u16 value, u8 mode);
extern u32 func_080035A8(u16 value);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern void *func_080D4724(const void *data, void *context, u32 value);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void *func_080D4D2C(void *object, u32 value);
extern void *func_080D3F08(void *operation);
extern void *func_080D4774(void *operation);
extern void *func_080D6134(void *operation);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern u8 func_080DD580(void *object);
extern void *func_080DBA5C(void *operation);

/* Complete [0x08108F84, 0x08109212): 654 bytes, 271 instructions. */
u32 func_08108F84(void *context, struct Command08108F84 *command,
                  struct Runtime08108F84 *runtime)
{
    switch (command->state) {
    case 0: {
        u32 mode;

        runtime->mode = command->mode;
        runtime->object = command->object;
        mode = 3;
        if (runtime->mode)
            mode = 0;
        if (command->flags & 2)
            runtime->skip = 1;
        runtime->opening = func_080E03F8(runtime->object, data_083A1254,
                                        mode, 0, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        runtime->opening = func_080E05DC(runtime->opening);
        if (runtime->opening != 0)
            break;
        if (func_080D3B54(runtime->object)) {
            command->state = 2;
            break;
        }
        if (!runtime->skip) {
            void *resource = func_080DD47C(runtime->object);

            func_080DE10C(resource, 88);
            runtime->preparation = func_080DE4B0(resource, &runtime->ready,
                2, 2, 0, 0, 0, context);
        }
        command->state++;
        break;
    case 0x101: {
        void *resource;

        if (runtime->preparation != 0 && !runtime->ready)
            break;
        runtime->related = func_080DD4A4(runtime->object, 0);
        runtime->actor = func_080DD4C4(runtime->related);
        func_080DBDC8(runtime->actor, &runtime->x, &runtime->y);
        resource = func_080DD47C(runtime->object);
        if (runtime->skip || resource != runtime->actor)
            func_080DE10C(runtime->actor, 68);
        runtime->timer = 4;
        command->state++;
        break;
    }
    case 0x102: {
        u32 flags;
        u16 control;

        if (runtime->timer != 0) {
            runtime->timer--;
            if (runtime->timer != 0)
                break;
        }
        func_080D49FC(0, 2, 0, runtime->x, runtime->y);
        runtime->effect_object = func_080D4B64(0, data_088EF398, 0x3BF, 6);
        flags = func_080035A8(2);
        control = g_control_flags_03000940;
        control |= flags;
        g_control_flags_03000940 = control;
        runtime->first = func_080D3E9C(data_0894D90C, context);
        runtime->movement = func_080D6098(runtime->x, runtime->y, 0, 1, 1,
            runtime->parameters, data_083A1278, context);
        runtime->second = func_080D4724(data_0894AB50, context, 9);
        runtime->script = func_080DFD8C(data_083A12A4, 1, 4, 0, context);
        command->state++;
        break;
    }
    case 0x103: {
        u32 flags;
        u16 control;

        runtime->effect_object = func_080D4D2C(runtime->effect_object, 0);
        if (runtime->effect_object != 0)
            break;
        runtime->first = func_080D3F08(runtime->first);
        if (runtime->first != 0)
            break;
        runtime->second = func_080D4774(runtime->second);
        if (runtime->second != 0)
            break;
        flags = func_080035A8(2);
        control = g_control_flags_03000940;
        control &= ~flags;
        g_control_flags_03000940 = control;
        runtime->movement = func_080D6134(runtime->movement);
        if (runtime->movement != 0)
            break;
        if (!func_080D8858(runtime->object, 0)) {
            command->state = 2;
            break;
        }
        runtime->operation = func_080DCFE4(runtime->related, data_083A1290,
                                           12, 0, 0, context, 0);
        if (func_080DD580(runtime->related))
            runtime->script = func_080DFD8C(data_083A12AC, 1, 4, 0, context);
        command->state++;
        break;
    }
    case 0x104:
        runtime->operation = func_080DBA5C(runtime->operation);
        if (runtime->operation == 0)
            command->state = 2;
        break;
    }
    return 0;
}
