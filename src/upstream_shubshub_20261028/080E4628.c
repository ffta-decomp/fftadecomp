/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E4628.c
 * Original SHA-256: eeb0d26a1b880aa72a73b82a077915cbf1bffa8e623ae9fb0997fa188400a068
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E4628 .. 0x080E4844: 540 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 option;
} Command080E4628;

typedef struct {
    u16 timer;
    u8 variant;
    u8 option;
    s16 x;
    s16 y;
    u8 unknown_08[24];
    void *effect_20;
    void *effect_24;
    void *effect_28;
    void *effect_2c;
    void *effect_30;
    void *object;
    void *effect_38;
    void *effect_3c;
} State080E4628;

extern const u8 data_08396B3C[];
extern const u8 data_088EA7F0[];
extern const u8 data_088F4680[];
extern const u8 data_089486D4[];
extern const u8 data_0894A490[];
extern const u8 data_0894D690[];
extern const u8 data_0894ABA0[];
extern const u8 data_08949DD8[];
extern const u8 data_08396C08[];
extern const u8 data_08396B78[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(const void *, int, int, int, int);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern void func_080DD748(void *, s16 *, s16 *, int);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4724(const void *, void *, int);
extern void *func_080DCFE4(void *, int, int, int, int, void *, int);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);
extern u32 func_080035A8(int);

u32 func_080E4628(void *task, Command080E4628 *command, State080E4628 *state)
{
    void *object;
    int mode;
    u32 mask;

    switch (command->state) {
    case 0:
        state->variant = 0;
        if (command->kind == 0x60)
            state->variant = 1;
        state->option = command->option;
        object = command->object;
        state->object = object;
        mode = 5;
        if (state->option)
            mode = 0;
        state->effect_30 = func_080E03F8(object, data_08396B3C, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->effect_30 = func_080E05DC(state->effect_30);
        if (state->effect_30)
            break;
        if (state->variant == 1) {
            func_080D45D0(data_088EA7F0, 7, 1, 5, 1);
            func_080D45D0(data_088EA7F0, 6, 1, 5, 1);
        }
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        object = func_080DD4A4(state->object, 0);
        func_080DD748(object, &state->x, &state->y, 0);
        func_080D7220(data_088F4680, 0, 2, state->x, state->y, 0);
        if (state->variant == 0)
            state->effect_24 = func_080D4704(data_089486D4, task);
        else
            state->effect_24 = func_080D4704(data_0894A490, task);
        state->effect_2c = func_080D3E9C(data_0894D690, task);
        if (state->variant == 0)
            state->effect_28 = func_080D4704(data_0894ABA0, task);
        else
            state->effect_28 = func_080D4724(data_08949DD8, task, 4);
        state->effect_38 = func_080DCFE4(object, 0, 12, 0, 4, task, 0x6e);
        state->effect_3c = func_080DFD8C(data_08396C08, 1, 4, 0, task);
        state->timer = 12;
        command->state++;
        break;
    case 0x101:
        if (--state->timer)
            break;
        state->effect_20 = func_080D6098(state->x, state->y, 0, 1, 6,
                                       state->unknown_08, data_08396B78, task);
        command->state++;
        break;
    case 0x102:
        state->effect_2c = func_080D3F08(state->effect_2c);
        state->effect_24 = func_080D4774(state->effect_24);
        if (state->effect_24)
            break;
        state->effect_28 = func_080D4774(state->effect_28);
        if (state->effect_28)
            break;
        state->effect_20 = func_080D6134(state->effect_20);
        if (state->effect_20)
            break;
        state->effect_38 = func_080DBA5C(state->effect_38);
        if (state->effect_38)
            break;
        mask = func_080035A8(2);
        g_control_flags_03000940 &= ~mask;
        command->state = 2;
        break;
    }
    return 0;
}
