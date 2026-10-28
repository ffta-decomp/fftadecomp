/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FFEC0.c
 * Original SHA-256: 2e4ad76c3dc9bd2565b885b9bab5d07614394afb7b20f6dedfd2d4df444680ed
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080FFEC0..0x081001F0: complete 816-byte callback. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} TaskDescriptor;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    u8 count;
    u8 index;
    u8 delay;
    u8 unknown_09;
    u16 countdown;
    u8 unknown_0C[12];
    void *coordinate_child;
    void *resource_child;
    void *effect_object;
    void *script_child;
    void *output;
    void *object;
    void *setup_child;
    void *output_child;
    void *children[5];
    void *record_child;
} CallbackState;

extern const u8 data_0839E60C[];
extern const u8 data_0839E68C[];
extern const u8 data_0839E630[];
extern const u8 data_0839E690[];
extern const u8 data_0894B1F0[];
extern const u8 data_088F06B0[];
extern const u8 data_0894DAA0[];
extern const u8 data_0839E698[];
extern const u8 data_0839E678[];
extern u16 g_control_flags_03000940;
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern void func_080D8C58(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern u8 func_080D8924(void *, u8, u16, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080D6134(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_080FFEC0(void *task, TaskDescriptor *descriptor, CallbackState *state)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        state->flag = descriptor->flag;
        state->object = descriptor->object;
        mode = 3;
        if (state->flag)
            mode = 0;
        state->setup_child = func_080E03F8(state->object, data_0839E60C,
                                           mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (state->setup_child)
            break;
        if (state->flag) {
            state->count = func_080DD494(state->object);
            state->delay = 1;
            descriptor->phase = 0x105;
        } else {
            state->output_child = func_080DDF68(state->object, &state->output,
                0x8007, 1, &state->ready, data_0839E68C, 5, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (!state->ready)
            break;
        func_080D8CD4(state->object);
        state->countdown = 20;
        descriptor->phase++;
        break;
    case 0x102:
        if (state->countdown && --state->countdown)
            break;
        if (func_080D8B4C())
            break;
        func_080D8C58(state->object, &state->x, &state->y);
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1,
            3, state->unknown_0C, data_0839E630, task);
        state->record_child = func_080DFD8C(data_0839E690, 1, 4, 0, task);
        state->resource_child = func_080D4704(data_0894B1F0, task);
        state->countdown = 24;
        descriptor->phase++;
        break;
    case 0x103:
        if (--state->countdown)
            break;
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->effect_object = func_080D4B64(0, data_088F06B0, 0x320, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        state->script_child = func_080D3E9C(data_0894DAA0, task);
        state->record_child = func_080DFD8C(data_0839E698, 1, 4, 0, task);
        state->count = func_080D8924(state->object, 0, 20, task);
        state->countdown = 6;
        descriptor->phase++;
        break;
    case 0x104:
        if (--state->countdown)
            break;
        state->count = func_080DD494(state->object);
        if (!state->count) {
            descriptor->phase = 2;
        } else {
            state->delay = 1;
            descriptor->phase++;
        }
        break;
    case 0x105: {
        void *object;
        u8 parity;
        u16 flags;
        if (--state->delay)
            break;
        object = func_080DD4A4(state->object, state->index);
        parity = state->index & 1;
        flags = parity ? 4 : 2;
        state->children[state->index] = func_080DCFE4(object, data_0839E678,
            12 - parity, 0, flags | 8, task, 0);
        state->delay = 30;
        state->index++;
        if (state->index != state->count)
            descriptor->phase = 0x105;
        else
            descriptor->phase++;
        break;
    }
    case 0x106: {
        u8 complete;
        u8 i;
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child)
            break;
        state->effect_object = func_080D4D2C(state->effect_object, 0);
        if (state->effect_object)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        state->script_child = func_080D3F08(state->script_child);
        if (state->script_child)
            break;
        state->resource_child = func_080D4774(state->resource_child);
        if (state->resource_child)
            break;
        if (!func_080DE1F0(state->output))
            break;
        complete = 1;
        for (i = 0; i < 5; i++) {
            state->children[i] = func_080DBA5C(state->children[i]);
            if (state->children[i])
                complete = 0;
        }
        if (complete)
            descriptor->phase = 2;
        break;
    }
    }
    return 0;
}
