/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080615E0.c
 * Original SHA-256: f2f55517ed78dac6213b0701738eeac16e0d709f9858d87ab137a7763576f575
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 busy;
    u8 unknown_01[0x93];
    u16 flags;
} TransitionControl;

typedef struct {
    u16 state;
    u8 unknown_02[0xEE];
    u8 payload[0];
} TransitionData;

typedef struct {
    u8 unknown_00[0x45];
    u8 command;
} __attribute__((packed)) TransitionEntry;

typedef struct {
    u8 index;
    u8 event;
    u16 value;
    u16 parameter;
    u8 unknown_06[6];
} TransitionCommand;

extern TransitionControl g_state_0200F390;
extern TransitionData *data_0200F450;
extern u8 data_03000ED0[];
typedef struct {
    u8 unknown_00[0x219E];
    u16 selected;
    u8 unknown_21A0[0x1A84];
    u32 pending;
    u16 selected_copy;
    u8 command_copy;
} GlobalTransitionState;
extern GlobalTransitionState g_state_02000000;
extern TransitionEntry g_table_0855AE4C[];
extern TransitionCommand g_table_08563A70[];
extern void func_08061720(void);
extern void func_08061778(void);
extern u8 func_080617C4(void);
extern u8 func_08061804(void);
extern void func_08022874(void);
extern void func_08022B24(void);
extern void func_08066168(u32 value);
extern u32 func_0800A5EC(void);
extern void func_080C9574(u16 index, u16 enabled);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);
extern void func_080C95C0(u16 index, u32 value);
extern void func_08009C18(const TransitionCommand *command, u8 index);
extern void func_08096DB4(void);

void func_080615E0(void *context, u8 *state)
{
    switch (*state) {
    case 0:
        func_08061720();
        *state = 4;
        break;
    case 0xFF:
        func_08061778();
        break;
    case 1:
        if (func_080617C4())
            *state = 3;
        break;
    case 2:
        switch (func_08061804()) {
        case 1:
            *state = 0xFF;
            break;
        case 2:
            *state = 1;
            break;
        }
        break;
    case 4:
        if (g_state_0200F390.busy == 0) {
            func_08022874();
            func_08022B24();
            func_08066168((u32)data_0200F450->payload);
            data_0200F450->state = 0;
            if (g_state_0200F390.flags & 0x100)
                *state = 2;
            else
                *state = 1;
        }
        break;
    case 3:
        data_03000ED0[5] = 1;
        if (func_0800A5EC() == 0) {
            func_080C9574(0x40, 0);
            func_08009AFC(0xA7);
            func_08009FD0();
            g_state_02000000.pending = 0;
        } else {
            u16 selected = g_state_02000000.selected;
            TransitionEntry *entry = &g_table_0855AE4C[selected];
            TransitionCommand *command = &g_table_08563A70[entry->command];
            g_state_02000000.selected_copy = selected;
            g_state_02000000.command_copy = entry->command;
            func_080C95C0(8, 0);
            func_08009C18(command, command->index);
            func_08009FD0();
            g_state_02000000.pending = 0;
            func_08096DB4();
        }
        *state = 0xFF;
        break;
    }
}
