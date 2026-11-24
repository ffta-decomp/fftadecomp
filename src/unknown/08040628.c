/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08040628.c
 * Original SHA-256: 38b0a2c98d277e01610ad83e47a8a0efd9154636f43962a7974cb7e5e39d358b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 field_03;
    u32 unknown_04;
    u16 field_08;
    u8 field_0A;
    u8 unknown_0B;
} Descriptor08040628;

typedef struct {
    u8 unknown_00[0xC];
    Descriptor08040628 descriptor;
} Configuration08040628;

typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
    u8 unknown_18[0x14];
    u32 field_2C;
    u16 field_30;
    u8 unknown_32[0x9A];
} Record08040628;

typedef struct {
    u8 unknown_00[0x954];
    Record08040628 records[0];
} Root08040628;

typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource08040628;

extern Root08040628 *g_state_03002810;
extern Resource08040628 data_030009E0[];
extern void func_08017424(State08017424 *, u32, u32,
                          u8, u8, u8, u8, u16, u8, u16, u16, u8);
extern void func_08016C90(State08017424 *, u8);

void func_08040628(u32 index, State08017424 *state,
                   const Configuration08040628 *configuration,
                   u8 first, u8 second)
{
    Descriptor08040628 descriptor = configuration->descriptor;
    u16 identifier = g_state_03002810->records[index].field_30;
    u16 enabled;

    if (first != 0xFF) {
        descriptor.field_00 = first;
        descriptor.field_01 = second;
    }
    enabled = 1;
    func_08017424(state, g_state_03002810->records[index].field_14,
                   g_state_03002810->records[index].field_2C,
                   descriptor.field_00, descriptor.field_01,
                   descriptor.field_02, descriptor.field_03,
                   descriptor.field_08, data_030009E0[identifier].field_28,
                   5, enabled, 12);
    func_08016C90(state, descriptor.field_0A);
}
