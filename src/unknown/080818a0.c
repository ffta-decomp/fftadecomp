/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080818A0.c
 * Original SHA-256: 36ce9f502b7022f44272308f52409578504d964eae21f35d1fd67ddf81b5167d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* Complete target [0x080818A0, 0x08081960): 192 bytes, 84 instructions. */
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
    u8 first;
    u8 second;
    u8 width;
    u8 height;
    u32 unknown_04;
    u16 flags;
    u8 appearance;
    u8 unknown_0B;
} Descriptor080818A0;

typedef struct {
    u8 unknown_00[12];
    Descriptor080818A0 descriptor;
} Input080818A0;

typedef struct {
    u8 unknown_00[0x14];
    u32 first;
    u8 unknown_18[0x14];
    u32 second;
    u16 renderer;
    u8 unknown_32[0x9A];
} Slot080818A0;

typedef struct {
    u8 unknown_000[0x2C88];
    Slot080818A0 slots[1];
} Menu080818A0;

typedef struct {
    u8 unknown_00[0x28];
    u8 stride;
    u8 unknown_29[0x23];
} Renderer080818A0;

extern Menu080818A0 *data_03002818;
extern Renderer080818A0 data_030009E0[];
extern void func_08017424(State08017424 *, u32, u32, u8, u8, u8, u8,
                          u16, u8, u16, u16, u8);
extern void func_08016C90(State08017424 *, u8);

void func_080818A0(u32 index, State08017424 *output,
                  const Input080818A0 *input, u8 first, u8 second)
{
    Descriptor080818A0 descriptor = input->descriptor;
    u16 renderer = data_03002818->slots[index].renderer;
    u16 enabled;

    if (first != 0xFF) {
        descriptor.first = first;
        descriptor.second = second;
    }
    enabled = 1;
    func_08017424(output, data_03002818->slots[index].first,
                  data_03002818->slots[index].second,
                  descriptor.first, descriptor.second, descriptor.width,
                  descriptor.height, descriptor.flags,
                  data_030009E0[renderer].stride, 5, enabled, 12);
    output->field_1C |= 1;
    func_08016C90(output, descriptor.appearance);
}
