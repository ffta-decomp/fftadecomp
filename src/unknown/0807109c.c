/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0807109C.c
 * Original SHA-256: a5d0188256f010f9f2ba31f5e668cdca82dcad37b41aa1c336aa372ab42f5318
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 *arena;
    u8 unknown_04[4];
    u8 *object;
    u8 unknown_0C[0x10];
    u8 *first_buffer;
    u8 *second_buffer;
    u8 unknown_024[0x2D48 - 0x24];
    u8 *first_workspace[3];
    u8 unknown_2D54[0x2E14 - 0x2D54];
    u8 *second_workspace[3];
    u8 workspace[0];
} ResourceOwner0807109C;

typedef struct {
    u16 capacity;
    u8 unknown_02[2];
    u16 *entries;
} SharedResource0807109C;

extern u8 *data_03002778;
extern u32 data_03000E54;
extern u8 *data_03000E98;
extern ResourceOwner0807109C *data_03002818;
extern SharedResource0807109C data_03000E30;
extern u8 *func_080070C8(u8 *arena, u32 bytes);
extern void *func_08007138(void *arena, u32 bytes);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete [0x0807109C, 0x08071234): 408 bytes, 137 instructions. */
void func_0807109C(u32 mode)
{
    u16 first_zero;
    u16 second_zero;
    u16 shared_zero;

    if (mode == 0) {
        data_03000E98 = func_080070C8(data_03002778, data_03000E54);
        data_03002818 = func_08007138(data_03000E98, 0x7240);
        first_zero = 0;
        func_0814186C(&first_zero, data_03002818, 0x01003920);
        data_03002818->arena = data_03000E98;
        data_03002818->second_buffer = func_08007138(data_03002818->arena, 0x440);
        data_03002818->object = func_080070C8(data_03002818->second_buffer, 0x400);
        data_03000E30.capacity = 0x40;
        data_03000E30.entries = func_08007138(data_03002818->arena, 0x740);
        data_03002818->first_buffer = func_08007138(data_03002818->arena, 0x3800);
    } else {
        data_03000E98 = func_080070C8(data_03002778, data_03000E54);
        data_03002818 = func_08007138(data_03000E98, 0x7240);
        second_zero = 0;
        func_0814186C(&second_zero, data_03002818, 0x01003920);
        data_03002818->arena = data_03000E98;
        data_03002818->second_buffer = func_08007138(data_03002818->arena, 0x440);
        data_03002818->object = func_080070C8(data_03002818->second_buffer, 0x400);
        data_03000E30.capacity = 0x40;
        data_03000E30.entries = func_08007138(data_03002818->arena, 0x740);
        data_03002818->first_buffer = func_08007138(data_03002818->arena, 0x2800);
    }
    shared_zero = 0;
    func_0814186C(&shared_zero, data_03000E30.entries, 0x010003A0);
    data_03002818->first_workspace[0] = data_03002818->workspace;
    data_03002818->second_workspace[0] = data_03002818->workspace + 0x4B0;
    data_03002818->first_workspace[1] = data_03002818->workspace + 0x960;
    data_03002818->second_workspace[1] = data_03002818->workspace + 0xF40;
    data_03002818->first_workspace[2] = data_03002818->workspace + 0x1520;
    data_03002818->second_workspace[2] = data_03002818->workspace + 0x2CA0;
}
