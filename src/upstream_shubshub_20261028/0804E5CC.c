/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804E5CC.c
 * Original SHA-256: cc6351d22b6612b95a1ad57fbbdae2eff90002472960b73ab3b7e8252cd46492
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef union {
    const void *pointer;
    u32 identifier;
} MenuResource;

typedef struct {
    u8 unknown_00[0x10];
    MenuResource resource;
} MenuData;

typedef struct {
    MenuData *data;
    u16 flags;
    s16 selection;
    u8 slot;
    u8 active;
    u8 unknown_0A[0x22];
    void *window;
} MenuState;

typedef struct {
    u16 code;
    u8 unknown_02[0x12];
    u16 slot;
} MenuEvent;

typedef struct {
    const void *resource;
    u8 unknown_04[8];
    u16 identifier;
    u16 unknown_0E;
    u8 selection;
    u8 count;
    u8 mode;
} ChoiceState;

extern MenuData *data_0201F548;
extern ChoiceState g_state_020020D0;
extern void *func_08005B28(u32 size);
extern void func_08005B40(void *allocation);
extern void func_08050E94(MenuState *state);
extern u16 func_08011860(void);
extern u8 func_0804F3B4(MenuState *state);
extern void func_0804F470(MenuState *state);

/* Complete [0x0804E5CC, 0x0804E6EC): 288 bytes, 117 reachable Thumb instructions. */
u32 func_0804E5CC(void *context, MenuEvent *event, MenuState *state)
{
    switch (event->code) {
    case 1:
        if (state->window) {
            func_08005B40(state->window);
            state->window = 0;
        }
        break;
    case 0:
        state->slot = event->slot;
        state->data = data_0201F548;
        if (g_state_020020D0.mode == 3) {
            g_state_020020D0.resource = 0;
            g_state_020020D0.identifier = state->data->resource.identifier;
            g_state_020020D0.selection = 0;
            g_state_020020D0.count = 1;
        } else {
            g_state_020020D0.resource = state->data->resource.pointer;
            g_state_020020D0.selection = 0;
            g_state_020020D0.count = 4;
        }
        break;
    case 0x100:
        state->window = func_08005B28(0x794);
        func_08050E94(state);
        event->code = 0x103;
        break;
    case 0x103:
        if (func_08011860()) {
            if (state->flags & 0x40) {
                state->active = 0;
                event->code = 0x102;
            } else {
                state->active = 1;
                event->code = 0x104;
            }
        }
        break;
    case 0x105:
        if (state->flags & 0x80) {
            state->flags &= ~0x80;
            event->code = 3;
        }
        break;
    case 0x104:
        if (func_0804F3B4(state))
            event->code = 0x103;
        break;
    case 0x102:
        func_08005B40(state->window);
        state->window = 0;
        state->selection = -2;
        event->code = 0x105;
        break;
    }
    func_0804F470(state);
    return 0;
}
