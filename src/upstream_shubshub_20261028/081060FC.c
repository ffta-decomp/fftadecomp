/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081060FC.c
 * Original SHA-256: a93b2f5467b93ac2b4cc5471d12e3e1112e4cd58e8749b5db9e09d3a96576a9f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x081060FC .. 0x081062C4: 456 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 option;
} Command081060FC;

typedef struct {
    u16 timer;
    u8 option;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *actor;
    u8 unknown_0c[12];
    void *effect_18;
    void *effects[2];
    void *effect_24;
    void *effect_28;
    void *object;
    void *effect_30;
    void *effect_34;
} State081060FC;

extern const u8 data_083A01AC[];
extern const u8 data_083A01E8[];
extern const u8 data_083A0240[][20];
extern const u8 data_083A0268[];
extern const u8 data_088F468C[];
extern const u8 data_083A0230[];
extern const u8 data_0894D690[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern s16 func_080DD4D4(void *);
extern void *func_080DCFE4(void *, const void *, int, int, int, void *, int);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void func_080D4870(const void *, void **, int, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern u8 func_080D48DC(void **, int);
extern u32 func_080035A8(int);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_081060FC(void *task, Command081060FC *command, State081060FC *state)
{
    void *object;
    void *actor;
    int mode;
    int variant;
    u32 mask;

    switch (command->state) {
    case 0:
        state->option = command->option;
        object = command->object;
        state->object = object;
        mode = 5;
        if (state->option)
            mode = 0;
        state->effect_28 = func_080E03F8(object, data_083A01AC, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->effect_28 = func_080E05DC(state->effect_28);
        if (state->effect_28)
            break;
        if (!func_080D8858(state->object, 0)) {
            command->state = 2;
            break;
        }
        actor = func_080DD4A4(state->object, 0);
        state->actor = func_080DD748(actor, &state->x, &state->y, 0);
        state->effect_18 = func_080D6098(state->x, state->y, 0, 1, 3,
                                       state->unknown_0c, data_083A01E8, task);
        variant = 0;
        if (func_080DD4D4(actor) > 0)
            variant = 1;
        state->effect_30 = func_080DCFE4(actor, data_083A0240[variant],
                                       12, 0, 4, task, 0x46);
        state->effect_34 = func_080DFD8C(data_083A0268, 2, 4, 0, task);
        state->timer = 14;
        command->state++;
        break;
    case 0x101:
        if (--state->timer)
            break;
        func_080D7220(data_088F468C, 0, 2, state->x, state->y, 0);
        func_080D4870(data_083A0230, state->effects, 2, task);
        state->effect_24 = func_080D3E9C(data_0894D690, task);
        command->state++;
        break;
    case 0x102:
        state->effect_24 = func_080D3F08(state->effect_24);
        if (state->effect_24)
            break;
        if (!func_080D48DC(state->effects, 2))
            break;
        mask = func_080035A8(2);
        g_control_flags_03000940 &= ~mask;
        state->effect_18 = func_080D6134(state->effect_18);
        if (state->effect_18)
            break;
        state->effect_30 = func_080DBA5C(state->effect_30);
        if (state->effect_30)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
