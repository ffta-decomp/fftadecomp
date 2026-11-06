/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08041224.c
 * Original SHA-256: a5187a1a61944a751ff0d2f237fda38fadd402d5f14c975a58835a2968cf3986
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* Complete target [0x08041224, 0x080412D0): 172 bytes, 76 instructions. */
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
} Descriptor08041224;

typedef struct {
    u8 unknown_00[12];
    Descriptor08041224 descriptor;
} Input08041224;

typedef struct {
    u8 unknown_00[0x14];
    u32 first;
    u8 unknown_18[0x14];
    u32 second;
    u16 renderer;
    u8 unknown_32[0x9A];
} Slot08041224;

typedef struct {
    u8 unknown_000[0x954];
    Slot08041224 slots[1];
} Menu08041224;

typedef struct {
    u8 unknown_00[0x28];
    u8 stride;
    u8 unknown_29[0x23];
} Renderer08041224;

extern Menu08041224 *g_state_03002810;
extern Renderer08041224 data_030009E0[];
extern void func_08017424(State08017424 *, u32, u32, u8, u8, u8, u8,
                          u16, u8, u16, u16, u8);
extern void func_08016C90(State08017424 *, u8);

void func_08041224(u32 index, State08017424 *output,
                  const Input08041224 *input, u8 first, u8 second)
{
    Descriptor08041224 descriptor = input->descriptor;
    u16 renderer = g_state_03002810->slots[index].renderer;
    u16 enabled;

    if (first != 0xFF) {
        descriptor.first = first;
        descriptor.second = second;
    }
    enabled = 1;
    func_08017424(output, g_state_03002810->slots[index].first,
                  g_state_03002810->slots[index].second,
                  descriptor.first, descriptor.second, descriptor.width,
                  descriptor.height, descriptor.flags,
                  data_030009E0[renderer].stride, 5, enabled, 12);
    func_08016C90(output, descriptor.appearance);
}
