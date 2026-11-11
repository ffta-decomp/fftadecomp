/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0804E6EC.c
 * Original SHA-256: 42fea193deda6ad220cb8e2f9cced78ecd7401b245ba35de434d1155316abae7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u16 code;
    u8 unknown_02[0x12];
    u16 parameter;
} Command0804E6EC;

typedef struct {
    void *source;
    u16 flags;
    u16 result;
    u8 mode;
    u8 unknown_09[3];
    void *small_buffer;
    void *large_buffer;
} State0804E6EC;

typedef struct {
    u8 unknown_0000[0x21b4];
    u8 option;
} Global0804E6EC;

extern void *data_0201F548;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern Global0804E6EC g_state_02000000;
extern void *func_08005B28(u32);
extern void func_08005B40(void *);
extern u8 func_0804F4D4(u8 *buffer);
extern void func_080185C8(void *, void *, void *, void *, u32);
extern void func_08018624(s32, u32, u32, u32, u32, u32);
extern u16 func_08018790(void);
extern void func_08018AA8(void);
extern void func_0804D91C(u32, u32, u32, u32);

/* 0x0804E6EC..0x0804E858: 364 bytes, 141 instructions. */
u32 func_0804E6EC(void *owner, Command0804E6EC *command, void *data)
{
    State0804E6EC *state = data;
    s32 code = command->code;
    u8 selection;

    switch (code) {
    case 1:
        if (state->small_buffer) {
            func_08005B40(state->small_buffer);
            state->small_buffer = 0;
        }
        if (state->large_buffer) {
            func_08005B40(state->large_buffer);
            state->large_buffer = 0;
        }
        break;
    case 0:
        state->mode = command->parameter;
        state->source = data_0201F548;
        break;
    case 0x100:
        {
            state->large_buffer = func_08005B28(0x3d8);
            state->small_buffer = func_08005B28(0x80);
            selection = func_0804F4D4(state->small_buffer);
            func_080185C8(state->large_buffer, state->small_buffer,
                          data_030008B0, data_03000990, code);
            func_08018624(-1, 1, 0xffff, selection,
                          g_state_02000000.option, 0);
            func_0804D91C(0, 1, 30, 2);
            command->code = 0x103;
        }
        break;
    case 0x103:
        if (func_08018790()) {
            if (state->flags & 0x40) {
                state->flags &= 0xffbf;
                command->code = 0x102;
            } else {
                command->code = 0x105;
            }
        }
        break;
    case 0x105:
        if (state->flags & 0x80) {
            state->flags &= 0xff7f;
            command->code = 3;
        } else if (state->flags & 0x40) {
            func_08018AA8();
            func_0804D91C(0, 0, 0, 0);
            command->code = 0x103;
        }
        break;
    case 0x102:
        func_08005B40(state->small_buffer);
        state->small_buffer = 0;
        func_08005B40(state->large_buffer);
        state->large_buffer = 0;
        state->result = 0xfffe;
        command->code = 0x105;
        break;
    }
    return 0;
}
