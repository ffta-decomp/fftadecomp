/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810457C.c
 * Original SHA-256: 1788ae124cc36ba97d234631b28787dd05cf2785bc7e67e762fc228d6b2ca1e4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command0810457C {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xE];
    u16 mode;
};

struct Runtime0810457C {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 mode;
    u8 unknown_07;
    void *resource;
    void *related;
    void *object;
    void *opening;
    u32 parameters[5];
    void *movement;
    void *effect_object;
    void *first;
    void *operation;
    void *script;
};

extern const u8 data_0839F4F8[];
extern const u8 data_088F162C[];
extern const u8 data_0894DC44[];
extern const u8 data_0839F528[];
extern const u8 data_0839F5B4[];
extern const u8 data_0839F5A0[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *object, const void *data, u32 mode,
                          u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern void func_080D49FC(u32 first, u32 second, u32 third, s16 x, s16 y);
extern void *func_080D4B64(u8 group, const void *data, u16 value, u8 mode);
extern u32 func_080035A8(u16 value);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void *func_080D4D2C(void *object, u32 value);
extern void *func_080D3F08(void *operation);
extern void *func_080D6134(void *operation);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern void *func_080DBA5C(void *operation);

/* Complete [0x0810457C, 0x0810471A): 414 bytes, 167 instructions. */
u32 func_0810457C(void *context, struct Command0810457C *command,
                  struct Runtime0810457C *runtime)
{
    switch (command->state) {
    case 0: {
        u32 mode;

        runtime->mode = command->mode;
        runtime->object = command->object;
        mode = 4;
        if (runtime->mode)
            mode = 0;
        runtime->opening = func_080E03F8(runtime->object, data_0839F4F8,
                                        mode, 1, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u32 flags;
        u16 control;

        runtime->opening = func_080E05DC(runtime->opening);
        if (runtime->opening != 0)
            break;
        if (!func_080D8858(runtime->object, 0)) {
            command->state = 2;
            break;
        }
        runtime->related = func_080DD4A4(runtime->object, 0);
        runtime->resource = func_080DD748(runtime->related, &runtime->x,
                                         &runtime->y, 0);
        func_080D49FC(0, 2, 0, runtime->x, runtime->y);
        runtime->effect_object = func_080D4B64(0, data_088F162C, 0x3D6, 6);
        flags = func_080035A8(2);
        control = g_control_flags_03000940;
        control |= flags;
        g_control_flags_03000940 = control;
        runtime->first = func_080D3E9C(data_0894DC44, context);
        runtime->movement = func_080D6098(runtime->x, runtime->y, 0, 1, 5,
            runtime->parameters, data_0839F528, context);
        runtime->script = func_080DFD8C(data_0839F5B4, 3, 4, 0, context);
        command->state++;
        break;
    }
    case 0x101: {
        u32 flags;
        u16 control;

        runtime->effect_object = func_080D4D2C(runtime->effect_object, 0);
        if (runtime->effect_object != 0)
            break;
        runtime->first = func_080D3F08(runtime->first);
        if (runtime->first != 0)
            break;
        flags = func_080035A8(2);
        control = g_control_flags_03000940;
        control &= ~flags;
        g_control_flags_03000940 = control;
        runtime->movement = func_080D6134(runtime->movement);
        if (runtime->movement != 0)
            break;
        runtime->operation = func_080DCFE4(runtime->related, data_0839F5A0,
                                           12, 0, 4, context, 0);
        command->state++;
        break;
    }
    case 0x102:
        runtime->operation = func_080DBA5C(runtime->operation);
        if (runtime->operation == 0)
            command->state = 2;
        break;
    }
    return 0;
}
