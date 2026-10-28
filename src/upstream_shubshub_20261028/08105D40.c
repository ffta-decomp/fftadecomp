/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08105D40.c
 * Original SHA-256: 7a43065b7ba759a22ee51058e595d4d58d4783d501e876e16c95773d423a20de
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08105D40..0x08105F62: complete 546-byte callback. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 kind;
    u16 flag;
} TaskDescriptor;

typedef struct {
    u8 index;
    u8 flag;
    u8 special;
    u8 unknown_03;
    u16 countdown;
    s16 x;
    s16 y;
    u16 unknown_0A;
    void *underlying;
    u8 unknown_10[4];
    void *first_child;
    u8 unknown_18[12];
    void *second_child;
    void *setup_child;
    void *object;
    void *object_child;
    void *record_child;
} CallbackState;

typedef struct {
    u8 unknown_00[20];
} EffectDescriptor;

extern const void *const data_0839FEBC[];
extern const u8 data_0839FEC8[];
extern const void *const data_0839FF14[];
extern const void *const data_0839FFF8[];
extern const u8 data_083A0004[];
extern const EffectDescriptor data_083A0008[];
extern const u8 data_083A0030[];
extern const void *const data_083A0064[];
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern s8 func_080DD5A8(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08105D40(void *task, TaskDescriptor *descriptor, CallbackState *state)
{
    void *object;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        if ((s16)descriptor->kind == 0x19C) {
            state->index = 0;
            state->special = 1;
            state->underlying = descriptor->object;
        } else {
            state->index = descriptor->kind + 9;
            state->flag = descriptor->flag;
            state->object = descriptor->object;
        }
        mode = data_0839FEC8[state->index];
        if (state->flag)
            mode = 0;
        if (!state->special) {
            state->setup_child = func_080E03F8(state->object,
                data_0839FEBC[state->index], mode, 1, 0, task);
        } else {
            state->setup_child = func_080E03F8(0,
                data_0839FEBC[state->index], mode, 7, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (state->setup_child)
            break;
        if (!state->special) {
            if (!func_080D8858(state->object, 0)) {
                descriptor->phase = 2;
                break;
            }
            object = func_080DD4A4(state->object, 0);
            state->underlying = func_080DD748(object, &state->x, &state->y, 0);
        } else {
            func_080DBDC8(state->underlying, &state->x, &state->y);
        }
        state->first_child = func_080D6098(state->x, state->y, 0, 1,
            1, state->unknown_10, data_0839FF14[state->index], task);
        if (!state->special) {
            u8 variant = func_080DD5A8(object) != 0;
            state->object_child = func_080DCFE4(object,
                &data_083A0008[variant], 12,
                data_083A0030[state->index], 4, task,
                data_083A0030[state->index]);
        }
        state->record_child = func_080DFD8C(data_083A0064[state->index],
                                           2, 4, 0, task);
        state->countdown = data_083A0004[state->index];
        descriptor->phase++;
        break;
    case 0x101:
        if (--state->countdown)
            break;
        state->second_child = func_080D6098(state->x, state->y, 0, 1,
            3, state->unknown_18, data_0839FFF8[state->index], task);
        descriptor->phase++;
        break;
    case 0x102:
        state->first_child = func_080D6134(state->first_child);
        state->second_child = func_080D6134(state->second_child);
        if (state->first_child || state->second_child)
            break;
        state->object_child = func_080DBA5C(state->object_child);
        if (!state->object_child)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
