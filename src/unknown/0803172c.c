/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0803172C.c
 * Original SHA-256: 050e7c63244bfc5177150ba8c6a78edb4234afbdf964dd9a831856f97803d4e8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 active : 1;
    u8 unknown_bits : 4;
    u8 hidden : 1;
    u8 suppressed : 1;
    u8 other_bit : 1;
    u8 unknown_01[5];
    u16 first;
    u16 second;
    u8 unknown_0A[2];
    u16 third;
    u8 unknown_0E[2];
    u8 amount;
    u8 unknown_11[9];
    u8 position_a, position_b;
    u8 unknown_1C[0x71];
    u8 enabled;
} Display0803172C;

typedef struct {
    Display0803172C *current, *display;
    u8 unknown_08[0x78];
    u8 busy, phase;
    u8 unknown_82[0x5FA];
    const void *table;
} State0803172C;

typedef struct {
    u8 unknown_00[0x9A];
    u8 first : 3;
    u8 first_other : 5;
    u8 unknown_9B[0x4B];
    u8 second : 3;
    u8 second_other : 5;
} Modes0803172C;

extern State0803172C *g_state_03002810;
extern Display0803172C g_state_02002C10;
extern const u8 data_08391E40[];
extern Modes0803172C data_030009E0;
extern Table data_03002720, data_03000880;
extern u32 data_030009B0[];
extern u8 data_03000EC8[];
extern void *data_0200F38C;
extern void func_080311B0(void);
extern void func_08030E50(void);
extern void func_08031348(void);
extern void func_08031698(void);
extern void func_08031714(void);
extern void func_080316D0(void);
extern void func_08031264(void);
extern void func_08006A7C(void *, u32 *, u8 *, u8);
extern void func_080069F4(void *, u8);
extern void func_08006B8C(Table *, u8);
extern void func_08006B5C(void *);
extern void func_0800718C(void *);
extern void func_0803155C(u8, u8 *);
extern void func_0808B288(u8, u8 *);
extern void func_08035174(u8, u8 *);

/* Complete target [0x0803172C, 0x080318D0): 420 bytes. */
void func_0803172C(u8 index, u8 *phase)
{
    switch (*phase) {
    case 0:
        func_080311B0();
        func_08030E50();
        func_08031348();
        g_state_03002810->current = &g_state_02002C10;
        g_state_03002810->display = &g_state_02002C10;
        g_state_02002C10.enabled = 1;
        g_state_03002810->table = data_08391E40;
        g_state_03002810->display->hidden = 0;
        g_state_03002810->display->suppressed = 0;
        data_030009E0.second = 6;
        data_030009E0.first = 6;
        g_state_03002810->display->amount = 0x28;
        g_state_03002810->display->first = 0x78;
        g_state_03002810->display->second = 0xD8;
        g_state_03002810->display->third = 0x9C;
        func_08006A7C(&data_03002720, data_030009B0, data_03000EC8, 5);
        func_08031698();
        func_08006ADC(&data_03000880, 0, (u32)func_0803155C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        *phase = 2;
        break;
    case 2:
        func_08031714();
        g_state_03002810->display->active = 0;
        g_state_03002810->display->position_a = 0;
        g_state_03002810->display->position_b = 0;
        g_state_03002810->busy = 0;
        func_08006ADC(&data_03002720, 0, (u32)func_08035174);
        g_state_03002810->phase = 0xB;
        *phase = 0xB;
        break;
    case 0xB:
        func_080069F4(&data_03002720, 5);
        *phase = g_state_03002810->phase;
        break;
    case 0xFD:
        func_08006B8C(&data_03000880, 0);
        func_08006B8C(&data_03000880, 1);
        *phase = 0xFE;
        break;
    case 0xFE:
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_0800718C(data_0200F38C);
        *phase = 0xFF;
        break;
    case 0xFF:
        break;
    }
}
