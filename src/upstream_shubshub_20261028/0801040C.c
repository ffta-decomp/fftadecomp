/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801040C.c
 * Original SHA-256: 1bb05f0689e41166bbc8f4429c4e70a90bdf5f1bf5992d983d0844688ffd7bc0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} RenderRange0801040C;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    RenderRange0801040C ranges[160];
    u16 horizontal_radius;
    u16 vertical_radius;
} RenderState0801040C;

RenderState0801040C *func_0800C614(void *object);
void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end);
void func_0800F860(s32 x, s32 y, u16 horizontal_radius, u16 vertical_radius,
                  RenderRange0801040C *ranges, u32 mode);

static inline void render_object(void *object)
{
    RenderState0801040C *state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F860(state->x, state->y, state->horizontal_radius,
                  state->vertical_radius, state->ranges, 1);
}

void func_0801040C(void *object, u16 radius)
{
    RenderState0801040C *state = func_0800C614(object);

    state->horizontal_radius = radius;
    render_object(object);
}
