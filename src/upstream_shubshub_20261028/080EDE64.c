/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EDE64.c
 * Original SHA-256: d2fc2a8bfcede5ed934218a44aa2190b89f8fdf0b2188459face1cfc8f7b2f58
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080EDE64..0x080EDFF6: complete 402-byte callback. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} TaskDescriptor;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 unknown_06;
    u8 flag;
    void *entity;
    void *underlying;
    u8 unknown_10[28];
    void *coordinate_child;
    void *setup_child;
    void *sequence_child;
    void *object;
    void *entity_child;
    void *record_child;
} CallbackState;

extern const u8 data_0839945C[];
extern const u8 data_08399480[];
extern const u8 data_08399528[];
extern const u8 data_0839953C[];
extern void func_080D38B4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void *func_080E05DC(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080EEEF0(u8, void *, void *);
extern void *func_080EEE50(void *, u8, void *);
extern void func_080D8858(void *, u8);
extern u8 func_080DD494(void *);
extern void *func_080EEF6C(void *);
extern u8 func_080EEF30(void *);
extern void *func_080DD4B4(void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080EDE64(void *task, TaskDescriptor *descriptor, CallbackState *state)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        state->flag = descriptor->flag;
        state->object = descriptor->object;
        mode = 3;
        if (state->flag)
            mode = 0;
        state->setup_child = func_080E03F8(state->object, data_0839945C,
                                           mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (!state->setup_child) {
            state->entity = func_080DD4A4(state->object, 0);
            state->underlying = func_080DD748(state->entity, &state->x,
                                              &state->y, 0);
            if (state->flag)
                descriptor->phase = 0x102;
            else {
                state->setup_child = func_080EEEF0(1, state->object, task);
                descriptor->phase++;
            }
        }
        break;
    case 0x101:
        state->setup_child = func_080E05DC(state->setup_child);
        if (!state->setup_child) {
            state->sequence_child = func_080EEE50(state->object, 1, task);
            func_080D8858(state->object, 0);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!func_080DD494(state->object)) {
            state->sequence_child = func_080EEF6C(state->sequence_child);
            if (!state->sequence_child)
                descriptor->phase = 2;
        } else if (state->flag || func_080EEF30(state->sequence_child)) {
            state->underlying = func_080DD4B4(state->object, 0);
            state->coordinate_child = func_080D6098(state->x, state->y,
                0, 1, 7, state->unknown_10, data_08399480, task);
            state->entity_child = func_080DCFE4(state->entity, data_08399528,
                                               12, 50, 2, task, 50);
            state->record_child = func_080DFD8C(data_0839953C, 2, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x103:
        state->sequence_child = func_080EEF6C(state->sequence_child);
        if (state->sequence_child)
            break;
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child)
            break;
        state->entity_child = func_080DBA5C(state->entity_child);
        if (!state->entity_child)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
