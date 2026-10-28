/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810B488.c
 * Original SHA-256: f447572510632e91546720608a4ca90ead8bcbda38dde09cf82453715e1dc9ee
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command0810B488 {
    u16 state;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 mode;
};

struct Runtime0810B488 {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 mode;
    u8 skip;
    u8 ready;
    u8 done;
    u16 unknown_0A;
    void *related;
    void *resource;
    void *secondary;
    void *object;
    void *opening;
    u32 parameters[1];
    void *movement;
    void *effect_object;
    void *first;
    void *operation;
    void *preparation;
    void *script;
};

extern const u8 data_083A1F5C[];
extern const u8 data_083A1FB8[];
extern const u8 data_088F2070[];
extern const u8 data_0894DE04[];
extern const u8 data_083A1FC0[];
extern const u8 data_088F25C0[];
extern const u8 data_0894DE14[];
extern const u8 data_083A1F8C[];
extern const u8 data_083A1FA4[];
extern const u8 data_083A1FC8[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *data, u32 mode,
                          u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080D3B54(void *object);
extern void *func_080DDF68(void *object, void **related, u32 flags, u32 mode,
                          u8 *ready, const void *data, u32 count, u32 value,
                          void *context);
extern void func_080D8C58(void *object, s16 *x, s16 *y);
extern void func_080D49FC(u32 first, u32 second, u32 third, s16 x, s16 y);
extern void *func_080D4B64(u8 group, const void *data, u16 value, u8 mode);
extern void func_0800BDD0(void *object, u8 enabled);
extern u32 func_080035A8(u16 value);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void *func_080D4D2C(void *object, u32 value);
extern void *func_080D3F08(void *operation);
extern void func_080DE3BC(void *object, u32 value);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern u8 func_080DE1F0(void *object);
extern void *func_080D6134(void *operation);
extern void *func_080DBA5C(void *operation);

/* Complete [0x0810B488, 0x0810B754): 716 bytes, 287 instructions. */
u32 func_0810B488(void *context, struct Command0810B488 *command,
                  struct Runtime0810B488 *runtime)
{
    switch (command->state) {
    case 0: {
        u32 mode;

        runtime->mode = command->mode;
        runtime->object = command->object;
        mode = 4;
        if (runtime->mode)
            mode = 0;
        if (command->flags & 2)
            runtime->skip = 1;
        runtime->opening = func_080E03F8(runtime->object, data_083A1F5C,
                                        mode, 1, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u32 value;

        runtime->opening = func_080E05DC(runtime->opening);
        if (runtime->opening != 0)
            break;
        if (func_080D3B54(runtime->object)) {
            command->state = 2;
            break;
        }
        value = 88;
        if (runtime->skip)
            value = 52;
        runtime->preparation = func_080DDF68(runtime->object, &runtime->related,
            value, 2, &runtime->ready, data_083A1FB8, 0, 0, context);
        command->state++;
        break;
    }
    case 0x101: {
        u32 flags;
        u16 control;

        if (!runtime->ready)
            break;
        func_080D8C58(runtime->object, &runtime->x, &runtime->y);
        func_080D49FC(0, 2, 0, runtime->x, runtime->y);
        runtime->effect_object = func_080D4B64(0, data_088F2070, 0x3D9, 6);
        func_0800BDD0(runtime->effect_object, 1);
        flags = func_080035A8(2);
        control = g_control_flags_03000940;
        control |= flags;
        g_control_flags_03000940 = control;
        runtime->first = func_080D3E9C(data_0894DE04, context);
        runtime->script = func_080DFD8C(data_083A1FC0, 1, 4, 0, context);
        command->state++;
        break;
    }
    case 0x102: {
        u32 clear_flags;
        u32 set_flags;
        u16 cleared_control;
        u16 set_control;

        runtime->effect_object = func_080D4D2C(runtime->effect_object, 0);
        if (runtime->effect_object != 0)
            break;
        runtime->first = func_080D3F08(runtime->first);
        if (runtime->first != 0)
            break;
        clear_flags = func_080035A8(2);
        cleared_control = g_control_flags_03000940;
        cleared_control &= ~clear_flags;
        g_control_flags_03000940 = cleared_control;
        func_080D49FC(1, 3, 0, runtime->x, runtime->y);
        runtime->effect_object = func_080D4B64(1, data_088F25C0, 0x3AD, 6);
        func_0800BDD0(runtime->effect_object, 1);
        set_flags = func_080035A8(3);
        set_control = g_control_flags_03000940;
        set_control |= set_flags;
        g_control_flags_03000940 = set_control;
        runtime->first = func_080D3E9C(data_0894DE14, context);
        func_080DE3BC(runtime->related, 0);
        command->state++;
        break;
    }
    case 0x103:
        if (!runtime->done)
            break;
        if (!func_080D8858(runtime->object, 0)) {
            command->state = 2;
            break;
        }
        runtime->secondary = func_080DD4A4(runtime->object, 0);
        runtime->resource = func_080DD748(runtime->secondary, &runtime->x,
                                         &runtime->y, 0);
        runtime->movement = func_080D6098(runtime->x, runtime->y, 0, 1, 1,
            runtime->parameters, data_083A1F8C, context);
        runtime->operation = func_080DCFE4(runtime->secondary, data_083A1FA4,
                                           12, 20, 4, context, 20);
        runtime->script = func_080DFD8C(data_083A1FC8, 1, 4, 0, context);
        command->state++;
        break;
    case 0x104: {
        u32 flags;
        u16 control;

        if (!func_080DE1F0(runtime->related))
            break;
        runtime->movement = func_080D6134(runtime->movement);
        if (runtime->movement != 0)
            break;
        runtime->effect_object = func_080D4D2C(runtime->effect_object, 1);
        if (runtime->effect_object != 0)
            break;
        flags = func_080035A8(3);
        control = g_control_flags_03000940;
        control &= ~flags;
        g_control_flags_03000940 = control;
        runtime->first = func_080D3F08(runtime->first);
        if (runtime->first != 0)
            break;
        runtime->operation = func_080DBA5C(runtime->operation);
        if (runtime->operation == 0)
            command->state = 2;
        break;
    }
    }
    return 0;
}
