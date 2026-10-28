/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010358.c
 * Original SHA-256: bf6073e55e61fcf8f61d59543e1530f8b393f427481bb881978e69fd6bb581c9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct RenderState {
    s16 x;
    s16 y;
    u8 unknown_04[4];
    u8 ranges[0x280];
    u16 first;
    u16 second;
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_08010058(void *object, u32 first, u32 count,
                         u16 start, u16 end);
extern void func_0800F770(s32 x, s32 y, u32 first, u32 second,
                         void *ranges, u32 mode);

static inline void render_object(void *object)
{
    RenderState *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800F770(state->x, state->y, state->first, state->second,
                  state->ranges, 1);
}

/* 08010358..080103B0: 88 bytes, 40 instructions. */
void func_08010358(void *object, u16 value)
{
    func_0800C614(object)->first = value;
    render_object(object);
}
