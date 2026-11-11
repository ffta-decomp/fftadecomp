/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08060E30.c
 * Original SHA-256: 3e4d0adaa4e8e75feb16b92bcc1451900158f35ef660214772ae3fa81e36147c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed int s32;

typedef struct {
    u8 unknown00[9];
    u8 value09;
} Object;

typedef struct {
    u16 phase;
    u16 unknown02;
    Object *object;
} Descriptor;

typedef struct {
    u8 unknown0000[0x108C];
    Object *object;
    s8 selection;
    u8 enabled;
    u8 detail;
    u8 countdown;
    u8 active;
} State;

extern u16 func_08022238(void *, u8 *);
extern void func_08029864(State *, u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_0802A2C0(u8, u8, u8, u8);
extern void func_08029D20(State *, u8);
extern u32 func_0802995C(State *);
extern void func_08061350(void);
extern void func_0806144C(u8);
extern u32 func_080614C4(const void *);
extern void func_08029C34(State *, u8, u8, u8, u8, u8, u8);
extern void func_08029CD8(State *, u8, u8);

/* Complete [0x08060E30, 0x08061026), including literal pools. */
u32 func_08060E30(void *unused, Descriptor *descriptor, State *state)
{
    u8 first_output;
    u8 second_output;
    u32 selection;

    switch (descriptor->phase) {
    case 0:
        state->object = descriptor->object;
        state->selection = -1;
        state->enabled = 0;
        state->detail = func_080614C4(state->object);
        state->active = 0;
        state->countdown = 32;
        break;
    case 1:
        break;
    case 0x100: {
        u8 value = func_08022238(state->object, &first_output);
        func_08029864(state, 20, 8, 7, state->object->value09,
                      value, 0, first_output, 1, 0);
        func_0802A2C0(20, 8, 6, 7);
        descriptor->phase = 0x101;
        break;
    }
    case 0x103:
        func_08029D20(state, 2);
        descriptor->phase = 0x101;
        break;
    case 0x101:
        selection = func_0802995C(state);
        state->selection = selection;
        if ((s8)selection == 4) {
            descriptor->phase = 0x104;
        } else if (*(u16 *)&state->selection == 1) {
            state->enabled = 1;
            func_08061350();
        } else if ((s8)selection == 3 && state->enabled) {
            state->enabled = 0;
            func_0806144C(1);
        }
        if (state->selection == 1 && !state->active) {
            if (state->countdown) {
                state->countdown--;
                if (state->countdown)
                    break;
            }
            func_08029CD8(state, state->detail, 1);
            state->active = 1;
        }
        break;
    case 0x102: {
        u8 value = func_08022238(state->object, &second_output);
        state->detail = func_080614C4(state->object);
        func_08029C34(state, state->object->value09, value, 0,
                      second_output, 1, 0);
        state->active = 0;
        state->countdown = 32;
        break;
    }
    case 0x104:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
