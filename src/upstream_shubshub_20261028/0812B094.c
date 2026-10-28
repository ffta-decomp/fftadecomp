/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812B094.c
 * Original SHA-256: 24edc27e8c71ffc8fb50a3d20d76193fe6c588d860fd3d156b11a33a63ab2271
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0812B094, 0x0812B184), 240 bytes including literals. */
typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    u16 frame;
    u8 unknown_06[0x292];
    const void *resource;
    u8 unknown_29c[0x5A];
    s8 selector;
} TransitionState;

typedef struct {
    u32 unknown_00;
    u16 *destination;
} TransitionDestination;

extern const u8 data_083A8298[];
extern const u8 data_083A82EC[];
extern const u8 data_083A8295[];
extern TransitionDestination data_03000990;
extern TransitionDestination data_030008B0;
extern s32 func_0812B3CC(u16 frame, u16 duration, s16 start, s16 end);
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                         u32, u32, u32, u32);
extern void func_08001CF0(const void *, s32, s32, u32, u32, u32, u32,
                         u32, u32, u32, u32);
extern void func_0812ADDC(TransitionState *, s16, s16);

u32 func_0812B094(TransitionState *state)
{
    s16 x;
    s16 negative_offset;
    u16 offset;
    u32 complete;

    state->frame++;
    x = func_0812B3CC(state->frame, 30, 80, 240);
    func_08001F34(data_083A8298, x, 128, 0, 0, 0, 0, 0, 0, 0, 0);
    func_0812ADDC(state, x + 12, 136);
    func_08001CF0(state->resource, x + 160, 154, 0, 0, 1, 0, 0, 576, 0, 0);

    offset = func_0812B3CC(state->frame, 30, 0, 208);
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
