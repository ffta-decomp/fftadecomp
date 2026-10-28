/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010284.c
 * Original SHA-256: c7936b39e871ab6b0e4bcba6b115393bf507d9734dae6a5df237af42057d91ef
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08010284..0x080102EA: 102 bytes. */
struct Range08010284 {
    u16 start;
    u16 end;
};

struct State08010284 {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    struct Range08010284 ranges[160];
    const u8 *data;
    u16 width;
};

extern struct State08010284 *func_0800C614(void *object);
extern void func_08010058(void *object, u32 first, u32 count,
                         u16 start, u16 end);
extern void func_0800F308(const u8 *data, u32 width, s32 x, s32 y,
                         struct Range08010284 *ranges, u32 mode);

static inline void render_object(void *object)
{
    struct State08010284 *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800F308(state->data, state->width, state->x, state->y,
                  state->ranges, 1);
}

void func_08010284(void *object, const u8 *data, u16 width)
{
    struct State08010284 *state = func_0800C614(object);

    state->data = data;
    state->width = width;
    render_object(object);
}
