/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FBEA0.c
 * Original SHA-256: eacef7c8353f6da058539b4ee701832ce2a1e3ff2dbd03958a3e42cccda7b229
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command080FBEA0 {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 mode;
};

struct Runtime080FBEA0 {
    s16 x;
    s16 y;
    u16 timer;
    u8 mode;
    u8 ready;
    void *related;
    void *resource;
    void *object;
    void *opening;
    u32 parameters[5];
    void *movement;
    void *operation;
    void *initiator;
    void *script;
};

extern const u8 data_0839D0B4[];
extern const u8 data_0839D164[];
extern const u8 data_0839D0D8[];
extern const u8 data_0839D150[];
extern const u8 data_0839D168[];

extern void *func_080E03F8(void *object, const void *data, u32 mode,
                          u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080D3B54(void *object);
extern void *func_080DDF68(void *object, void **related, u32 flags, u32 mode,
                          u8 *ready, const void *data, u32 count, u32 value,
                          void *context);
extern void func_080DBFFC(void *object, u32 value);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern u8 func_080DBC88(void *object);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern void func_080D6194(void *operation, u8 enabled);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern u8 func_080DE1F0(void *object);
extern void *func_080D6134(void *operation);
extern void *func_080DBA5C(void *operation);

/* Complete [0x080FBEA0, 0x080FC056): 438 bytes, 188 instructions. */
u32 func_080FBEA0(void *context, struct Command080FBEA0 *command,
                  struct Runtime080FBEA0 *runtime)
{
    switch (command->state) {
    case 0: {
        void *object;
        u32 mode;

        runtime->mode = command->mode;
        object = command->object;
        runtime->object = object;
        mode = 3;
        if (runtime->mode)
            mode = 0;
        runtime->opening = func_080E03F8(object, data_0839D0B4, mode,
                                        0, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 unavailable;

        runtime->opening = func_080E05DC(runtime->opening);
        if (runtime->opening != 0)
            break;
        unavailable = func_080D3B54(runtime->object);
        if (unavailable) {
            command->state = 2;
            break;
        }
        runtime->initiator = func_080DDF68(runtime->object, &runtime->related,
            0x8007, 1, &runtime->ready, data_0839D164, 5, 0, context);
        command->state++;
        break;
    }
    case 0x101:
        if (!runtime->ready)
            break;
        func_080DBFFC(runtime->object, 0);
        runtime->timer = 30;
        command->state++;
        /* fall through */
    case 0x102: {
        void *related;
        u8 kind;

        if (runtime->timer != 0) {
            runtime->timer--;
            if (runtime->timer != 0)
                break;
        }
        if (func_080D8B4C())
            break;
        if (!func_080D8858(runtime->object, 0)) {
            command->state = 2;
            break;
        }
        related = func_080DD4A4(runtime->object, 0);
        runtime->resource = func_080DD748(related, &runtime->x, &runtime->y, 0);
        kind = func_080DBC88(runtime->related);
        runtime->movement = func_080D6098(runtime->x, runtime->y, 0, 1, 5,
            runtime->parameters, data_0839D0D8, context);
        if (kind > 1)
            func_080D6194(runtime->movement, 1);
        runtime->operation = func_080DCFE4(related, data_0839D150, 12, 30,
                                           12, context, 30);
        runtime->script = func_080DFD8C(data_0839D168, 1, 4, 0, context);
        command->state++;
        break;
    }
    case 0x103:
        if (func_080DE1F0(runtime->related)) {
            runtime->movement = func_080D6134(runtime->movement);
            if (runtime->movement != 0)
                break;
            runtime->operation = func_080DBA5C(runtime->operation);
            if (runtime->operation == 0)
                command->state = 2;
        }
        break;
    }
    return 0;
}
