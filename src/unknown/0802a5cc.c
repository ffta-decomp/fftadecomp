/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0802A5CC.c
 * Original SHA-256: 70373c2d8735a03dfd6b0e2da6eed2f4d605f9a8ecc514d7d9345d0f03a9c827
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* 0x0802A5CC..0x0802A6A0: 212 bytes. */
typedef struct {
    u8 unknown_00[0x38];
    void *buffer;
    u8 unknown_3C[0x38];
    u32 value_74;
    u8 unknown_78;
    u8 active;
    u8 mode;
    u8 field_7B;
    u8 field_7C;
    u8 unknown_7D;
    u16 value_7E;
    u8 field_80;
    u8 unknown_81;
    u8 content[1];
} State0802A5CC;

typedef struct {
    u8 unknown_00[0x14];
    u32 value_14;
} Resource0802A5CC;

extern Resource0802A5CC data_030008B0;
extern Resource0802A5CC data_03000990;
extern void func_08017424(void *, u32, u32, u8, u8, u8, u8,
                         u16, u8, u16, u16, u8);
extern void func_08016210(void *, const void *, u16, u16);
extern void func_0814186C(const void *, void *, u32);
extern void func_08016C90(void *, u8);
extern void func_0802A370(u8, u8, u8, u8);

void func_0802A5CC(State0802A5CC *state, u32 value, u16 index,
                   u16 field, u8 mode, u8 x, u8 y)
{
    u16 fill;

    state->active = 1;
    state->field_7B = 0;
    state->field_7C = 0;
    state->mode = mode;
    state->value_74 = value;
    state->value_7E = field;
    func_08017424(state, data_030008B0.value_14, data_03000990.value_14,
                  x, y, 5, 2, 0x800, 0x20, 13, 3, 11);
    func_08016210(state, state->content, index, 2);
    fill = 0;
    func_0814186C(&fill, state->buffer, 0x100000A);
    func_08016C90(state, 1);
    func_0802A370(x, y, 5, 2);
    state->field_80 = 0;
}
