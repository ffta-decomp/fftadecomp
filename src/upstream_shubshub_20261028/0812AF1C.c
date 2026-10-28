/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812AF1C.c
 * Original SHA-256: 81c7295ea1d4637d6b9376dc6f79de932212e33ab10ae995c9ab321fc506e9e1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0812AF1C, 0x0812B094), 376 bytes including literals. */
typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    u16 frame;
    u8 unknown_06[0x292];
    const void *resource;
    u8 unknown_29c[0x5a];
    s8 selector;
} State0812AF1C;

typedef struct {
    u32 unknown_00;
    u16 *destination;
} Destination0812AF1C;

extern const u8 data_083A8298[];
extern const u8 data_083A82AC[];
extern const u8 data_083A82BA[];
extern const u8 data_083A82C8[];
extern const u8 data_083A82EC[];
extern const u8 data_083A8295[];
extern Destination0812AF1C data_03000990;
extern Destination0812AF1C data_030008B0;
extern s32 func_0812B384(u16, u16, s16, s16);
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);
extern void func_08001CF0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);
extern void func_0812ADDC(State0812AF1C *, s16, s16);

u32 func_0812AF1C(State0812AF1C *state)
{
    s16 x;
    s16 negative_offset;
    u16 offset;
    u32 complete;

    state->frame++;
    x = func_0812B384(state->frame, 30, 240, 80);
    func_08001F34(data_083A8298, x, 128, 0, 0, 0, 0, 0, 0, 0, 0);
    func_0812ADDC(state, x + 12, 136);
    func_08001F34(state->resource, x + 160, 154, 0, 0, 1, 0, 0, 576, 0, 0);

    func_08001F34(data_083A82AC,
        (s16)func_0812B384(state->frame, 30, 240, 192),
        16, 0, 0, 0, 0, 0, 0, 0, 0);
    func_08001F34(data_083A82BA,
        (s16)func_0812B384(state->frame, 30, 240, 192),
        32, 0, 0, 0, 0, 0, 0, 0, 0);
    func_08001CF0(data_083A82C8,
        (s16)func_0812B384(state->frame, 30, 240, 192),
        48, 0, 0, 0, 0, 0, 0, 0, 0);

    offset = func_0812B384(state->frame, 30, 208, 0);
    *data_03000990.destination = offset;
    *data_030008B0.destination = offset;
    negative_offset = offset;
    negative_offset = -negative_offset;
    func_08001F34(data_083A82EC, negative_offset + data_083A8295[state->selector],
        8, 0, 0, 0, 0, 0, 0, 0, 0);

    if (state->frame < 30) {
        complete = 0;
    } else {
        state->frame = 0;
        complete = 1;
    }
    return complete;
}
