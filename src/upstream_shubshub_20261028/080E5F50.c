/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E5F50.c
 * Original SHA-256: 1fe9f9ed84288e8b22f817c79ea4346622d459cfb5d22b5e7d2e8331f0030ca6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E5F50 .. 0x080E61E2: 658 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 option;
} Command080E5F50;

typedef struct {
    u16 timer;
    u8 option;
    u8 variant;
    u8 flag;
    u8 unknown_05;
    s16 x;
    s16 y;
    u16 unknown_0a;
    void *object;
    void *actor;
    u8 unknown_14[16];
    void *effect_24;
    void *effect_28;
    void *effect_2c;
    void *effect_30;
    void *effect_34;
    void *effect_38;
    void *effect_3c;
} State080E5F50;

extern const u8 data_08397280[];
extern const u8 data_088E9C70[];
extern const u8 data_088EA4C4[];
extern const u8 data_0894968C[];
extern const u8 data_0894A81C[];
extern const u8 data_0894C6BC[];
extern const u8 data_0894D7CC[];
extern const u8 data_0894DD30[];
extern const u8 data_088F46F0[];
extern const u8 data_083972BC[];
extern const u8 data_0894AC40[];
extern const u8 data_0839731C[];
extern const u8 data_08949DD8[];

extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void func_080D45D0(const void *, int, int, int, int);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern u8 func_080DD580(void *);
extern void *func_080DC498(void *, int, int, int, void *);
extern void *func_080DD214(void *, int, int, void *);
extern void *func_080D4724(const void *, void *, int);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern u16 func_080DD6E0(void *);
extern void func_080DE390(void *);
extern void *func_080DBB14(void *, int, int, int, void *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080E5F50(void *task, Command080E5F50 *command, State080E5F50 *state)
{
    int priority;
    int mode;

    switch (command->state) {
    case 0:
        state->variant = 0;
        state->flag = 0;
        priority = 1;
        if (command->kind == 0x9e) {
            state->variant = 1;
            priority = 7;
        } else if (command->kind == 0x18b) {
            state->variant = 2;
            priority = 7;
            state->flag = 1;
        }
        if (state->variant != 2) {
            state->option = command->option;
            state->object = command->object;
        } else {
            state->actor = command->object;
        }
        mode = 5;
        if (state->option)
            mode = 0;
        state->effect_34 = func_080E03F8(state->object, data_08397280, mode,
                                       priority, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->effect_34 = func_080E05DC(state->effect_34);
        if (state->effect_34)
            break;
        if (state->variant != 2) {
            if (!func_080D8858(state->object, 0)) {
                command->state = 2;
                break;
            }
            state->actor = func_080DD748(func_080DD4A4(state->object, 0),
                                         &state->x, &state->y, 0);
        } else {
            func_080D45D0(data_088E9C70, 6, 1, 5, 1);
            func_080D45D0(data_088EA4C4, 7, 1, 1, 1);
            func_080DBDC8(state->actor, &state->x, &state->y);
        }
        if (state->variant == 0)
            state->effect_28 = func_080D4704(data_0894968C, task);
        else if (state->variant == 1)
            state->effect_28 = func_080D4704(data_0894A81C, task);
        else
            state->effect_28 = func_080D4704(data_0894C6BC, task);
        if (state->variant != 2)
            state->effect_30 = func_080D3E9C(data_0894D7CC, task);
        else
            state->effect_30 = func_080D3E9C(data_0894DD30, task);
        func_080D7220(data_088F46F0, 0, 2, state->x, state->y, 0);
        state->effect_24 = func_080D6098(state->x, state->y, 0, 1, 4,
                                       state->unknown_14, data_083972BC, task);
        if (state->variant != 2) {
            if (func_080DD580(func_080DD4A4(state->object, 0)))
                state->effect_38 = func_080DC498(state->actor, 20, 12, 0x36, task);
            else
                state->effect_38 = func_080DD214(state->actor, 0, 0x78, task);
            state->effect_2c = func_080D4724(data_0894AC40, task, 100);
            command->state = 0x102;
        } else {
            state->timer = 0x36;
            command->state++;
        }
        state->effect_3c = func_080DFD8C(data_0839731C, 1, 4, 0, task);
        break;
    case 0x101:
        if (--state->timer)
            break;
        if (func_080DD6E0(state->actor) != 13)
            func_080DE390(state->actor);
        state->effect_38 = func_080DBB14(state->actor, 2, 12, 0, task);
        state->effect_2c = func_080D4724(data_08949DD8, task, 46);
        command->state++;
        break;
    case 0x102:
        state->effect_28 = func_080D4774(state->effect_28);
        if (state->effect_28)
            break;
        state->effect_2c = func_080D4774(state->effect_2c);
        if (state->effect_2c)
            break;
        state->effect_30 = func_080D3F08(state->effect_30);
        if (state->effect_30)
            break;
        state->effect_24 = func_080D6134(state->effect_24);
        if (state->effect_24)
            break;
        state->effect_38 = func_080DBA5C(state->effect_38);
        if (state->effect_38)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
