/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081042C8.c
 * Original SHA-256: e7654336bab06e19d96fec121ed91081547208144adc9fa54eea965be8f6a38e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct InterpolationState;

extern s16 func_08007A60(u8 angle);
extern s32 func_08007A4C(u8 angle);
extern void func_080107D4(void *handle, s16 x, s16 y, u8 flags);
extern void func_080E064C(struct InterpolationState *state);
extern u8 func_080E0690(struct InterpolationState *state);
extern void func_080E0608(struct InterpolationState *state, s16 start,
                          s16 end, s16 duration);
extern u32 func_080D5F24(void **handles, u16 count);

/* Target: 0x081042C8..0x0810438A, 194 bytes, no literal pool or alignment. */
u8 func_081042C8(void **handles, struct InterpolationState *state,
                  s16 x, s16 y)
{
    u8 angle = *(u8 *)state;
    u8 lane;

    for (lane = 0; lane < 3; lane++, angle += 85) {
        if (handles[lane] != 0) {
            s16 offset_x = func_08007A60(angle) >> 3;
            s16 offset_y = (s16)func_08007A4C(angle) >> 4;

            func_080107D4(handles[lane], (s16)(x + offset_x),
                          (s16)(y + offset_y - 40), 0);
        }
    }

    func_080E064C(state);
    if (func_080E0690(state))
        func_080E0608(state, *(s16 *)state,
                      (s16)(*(u16 *)state + 256), 164);
    return func_080D5F24(handles, 3);
}
