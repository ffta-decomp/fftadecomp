/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08102BD4.c
 * Original SHA-256: cf84593142edf3aea9716dc69d673eb771b89e79b4ab9b09f14d14d297f54440
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08102BD4 .. 0x08102DBE: 490 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 option;
} Command08102BD4;

typedef struct {
    u8 option;
    u8 unknown_01;
    u16 timer;
    s16 x;
    s16 y;
    u8 signal;
    u8 unknown_09[3];
    u32 unknown_0c;
    void *effect_10;
    void *effect_14;
    void *object;
    void *actor;
    void *object_20;
    void *effect_24;
    void *effect_28;
    void *effect_2c;
    void *effect_30;
} State08102BD4;

extern const u8 data_0839F014[];
extern const u8 data_0839F058[];
extern const u8 data_0839F02C[];
extern const u8 data_08949DD8[];
extern const u8 data_0839F044[];
extern const u8 data_0839F05C[];

extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, int, int, u8 *, const void *, int, int, void *);
extern void func_080DC12C(void *, int, int);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern void *func_080D4704(const void *, void *);
extern s8 func_080DBC88(void *);
extern void func_080D6194(void *, int);
extern void *func_080DCFE4(void *, const void *, int, int, int, void *, int);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_08102BD4(void *task, Command08102BD4 *command, State08102BD4 *state)
{
    int mode;
    void *actor;

    switch (command->state) {
    case 0:
        state->option = command->option;
        state->object = command->object;
        mode = 2;
        if (state->option)
            mode = 0;
        state->effect_24 = func_080E03F8(state->object, data_0839F014, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->effect_24 = func_080E05DC(state->effect_24);
        if (state->effect_24)
            break;
        if (func_080D3B54(state->object)) {
            command->state = 2;
            break;
        }
        state->effect_2c = func_080DDF68(state->object, &state->actor, 0x8007, 1,
                                       &state->signal, data_0839F058, 5, 0, task);
        command->state++;
        break;
    case 0x101:
        if (state->signal)
            command->state++;
        break;
    case 0x102:
        func_080DC12C(state->object, 0, 0);
        state->timer = 10;
        command->state++;
        /* Fall through to the timer phase. */
    case 0x103:
        if (state->timer && --state->timer)
            break;
        if (func_080D8B4C())
            break;
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        actor = func_080DD4A4(state->object, 0);
        state->object_20 = func_080DD748(actor, &state->x, &state->y, 0);
        state->effect_10 = func_080D6098(state->x, state->y, 0, 1, 1,
                                       &state->unknown_0c, data_0839F02C, task);
        state->effect_14 = func_080D4704(data_08949DD8, task);
        if (func_080DBC88(state->actor) > 1)
            func_080D6194(state->effect_10, 1);
        state->effect_28 = func_080DCFE4(actor, data_0839F044, 12, 0x32, 12, task, 0x32);
        state->effect_30 = func_080DFD8C(data_0839F05C, 1, 4, 0, task);
        command->state++;
        break;
    case 0x104:
        state->effect_14 = func_080D4774(state->effect_14);
        if (state->effect_14)
            break;
        state->effect_10 = func_080D6134(state->effect_10);
        if (state->effect_10)
            break;
        if (!func_080DE244(state->actor))
            break;
        state->effect_28 = func_080DBA5C(state->effect_28);
        if (state->effect_28)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
