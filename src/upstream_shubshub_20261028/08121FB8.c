/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08121FB8.c
 * Original SHA-256: bae4879c9e55759eb843fb15d1da12d475edca4837633701e9ba71c1652d537c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08121FB8..0x08122160: 424 bytes. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 first;
    u16 second;
} Command;

typedef struct {
    u16 first;
    u16 second;
    u16 timer;
    u8 ready;
    u8 filter;
    void *context;
    void *object;
} CommandState;

typedef struct {
    u8 unknown_00[2];
    s16 index;
} ObjectInfo;

extern u8 g_state_0200F390;
extern u32 func_08122ABC(CommandState *state);
extern void *func_08121D0C(u32 index);
extern ObjectInfo *func_08005BFC(void *object);
extern u32 func_08122160(CommandState *state);
extern void func_08005C04(void *context, Command *command);
extern u8 func_080D37F8(void);
extern u8 func_080D37C4(void);
extern u32 func_08121DBC(void);
extern u8 func_080D3878(void);
extern void func_080D3864(u32 value);
extern void func_08121DA8(u32 value);
extern u8 func_080C72E4(void);
extern u32 func_08121E1C(void);
extern u8 func_080C74B4(void);
extern void func_080C7548(u32 value);
extern void func_08124CE8(void);
extern void func_08004C40(void);

static inline u8 matching_actor_exists(u8 filter)
{
    s32 index;
    for (index = 0; index < 16; index++) {
        void *object = func_08121D0C(index);
        if (object != 0) {
            if (filter == 0xFF)
                return 1;
            if (func_08005BFC(object)->index == filter)
                return 1;
        }
    }
    return 0;
}

u32 func_08121FB8(void *context, Command *command, CommandState *state)
{
    if (command->state > 0xFF && state->context == 0)
        return 0;

    switch (command->state) {
    case 0:
        state->first = command->first;
        state->second = command->second;
        state->object = command->object;
        state->context = context;
        break;
    case 3:
        break;
    case 0x100:
    {
        u32 next = func_08122ABC(state);
        switch (next) {
        case 0x11D:
        case 0x11E:
            command->state = 3;
            break;
        default:
            command->state = next;
            break;
        }
        break;
    }
    case 0x112:
        if (g_state_0200F390 == 14)
            command->state = 0x100;
        break;
    case 0x113:
        if (!matching_actor_exists(state->filter))
            command->state = 0x100;
        break;
    case 0x11C:
        command->state = func_08122160(state);
        break;
    case 0x114:
        if (state->timer == 0 || --state->timer == 0)
            command->state = 0x100;
        break;
    case 0x115:
        if (state->ready == 1) {
            state->ready = 0;
            command->state = 0x100;
            func_08005C04(context, command);
        }
        break;
    case 0x116:
        if (func_080D37F8())
            command->state = 0x100;
        break;
    case 0x117:
        if (func_080D37C4())
            command->state = 0x100;
        break;
    case 0x118:
    {
        u32 value = func_08121DBC();
        if (func_080D3878()) {
            func_080D3864(value);
            func_08121DA8(0);
            command->state = 0x100;
        }
        break;
    }
    case 0x119:
        if (func_080C72E4())
            command->state = 0x100;
        break;
    case 0x11A:
    {
        u32 value = func_08121E1C();
        if (!func_080C74B4()) {
            func_080C7548(value);
            func_08124CE8();
            command->state = 0x100;
        }
        break;
    }
    case 0x11B:
        if (state->timer == 0 || --state->timer == 0) {
            func_08004C40();
            command->state = 0x100;
        }
        break;
    }
    return 0;
}
