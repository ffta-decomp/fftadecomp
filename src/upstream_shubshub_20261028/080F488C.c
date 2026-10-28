/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F488C.c
 * Original SHA-256: 25ab6637e607ebc3bd32b979a213b3b42070cf71ae0dd88f6f5a6791f87eaac3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command080F488C {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 mode;
};

struct Runtime080F488C {
    u16 unknown_00;
    u16 unknown_02;
    u16 timer;
    u8 unknown_06;
    u8 mode;
    void *resource;
    void *part;
    void *related;
    void *object;
    u8 unknown_18[12];
    void *opening;
    u8 unknown_28[12];
    void *main;
    void *operation;
    void *script;
};

extern const u8 data_0839B1A8[];
extern const u8 data_0839B1C0[];

extern void *func_080E03F8(void *object, const void *data, u32 mode,
                          u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080D3B54(void *object);
extern void *func_080DD4B4(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void *func_080DD47C(void *object);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DF75C(void *resource, void *part, u32 first, u32 second,
                          u32 third, u32 fourth, void *context);
extern u8 func_080DBA3C(void *operation);
extern u8 func_080DD580(void *object);
extern void *func_080DF7A0(void *part, u32 first, u32 second, u32 third,
                          u32 fourth, void *context);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern void *func_080DBA5C(void *operation);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void func_080DBEB4(void *object, u8 visible);
extern void func_080DF790(void *operation);
extern void func_080DE328(void *object);

/* Complete [0x080F488C, 0x080F4A6E): 482 bytes, 205 instructions. */
u32 func_080F488C(void *context, struct Command080F488C *command,
                  struct Runtime080F488C *runtime)
{
    switch (command->state) {
    case 0: {
        void *object;
        u32 mode;

        runtime->mode = command->mode;
        object = command->object;
        runtime->object = object;
        mode = 2;
        if (runtime->mode)
            mode = 0;
        runtime->opening = func_080E03F8(object, data_0839B1A8, mode,
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
        runtime->part = func_080DD4B4(runtime->object, 0);
        runtime->related = func_080DD4A4(runtime->object, 0);
        runtime->resource = func_080DD47C(runtime->object);
        if (!func_080D8858(runtime->object, 0)) {
            command->state = 2;
            break;
        }
        runtime->main = func_080DF75C(runtime->resource, runtime->part,
                                     140, 0x3E5, 6, 0, context);
        command->state++;
        break;
    }
    case 0x101:
        if (func_080DBA3C(runtime->main)) {
            if (func_080DD580(runtime->related))
                runtime->operation = func_080DF7A0(runtime->part, 6, 0, 4,
                                                  0, context);
            else
                runtime->operation = func_080DCFE4(runtime->related, 0,
                                                   12, 0, 4, context, 0);
            command->state++;
        }
        break;
    case 0x102:
        runtime->operation = func_080DBA5C(runtime->operation);
        if (runtime->operation != 0)
            break;
        if (!func_080DD580(runtime->related)) {
            command->state = 0x104;
            break;
        }
        runtime->script = func_080DFD8C(data_0839B1C0, 1, 4, 0, context);
        runtime->timer = 20;
        command->state++;
        break;
    case 0x103:
        runtime->timer--;
        if (runtime->timer & 1)
            func_080DBEB4(runtime->part, 1);
        else
            func_080DBEB4(runtime->part, 0);
        if (runtime->timer > 19) {
            if (func_080DD580(runtime->related))
                command->state = 0x105;
            else
                command->state++;
        }
        break;
    case 0x104:
        func_080DF790(runtime->main);
        func_080DE328(runtime->related);
        command->state++;
        break;
    case 0x105:
        runtime->main = func_080DBA5C(runtime->main);
        if (runtime->main == 0)
            command->state = 2;
        break;
    }
    return 0;
}
