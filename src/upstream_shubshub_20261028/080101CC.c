/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080101CC.c
 * Original SHA-256: 48ac727ab53ee41d03ae20882e8e6df0e227f2e96d2706fe74c0295050f8f85d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} RenderRange080101CC;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    RenderRange080101CC ranges[160];
    u16 radius;
} RenderState080101CC;

RenderState080101CC *func_0800C614(void *object);
void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end);
void func_0800F068(s32 x, s32 y, u16 radius,
                  RenderRange080101CC *ranges, u32 mode);

static inline void render_object(void *object)
{
    RenderState080101CC *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800F068(state->x, state->y, state->radius, state->ranges, 1);
}

void func_080101CC(void *object, u16 radius)
{
    RenderState080101CC *state = func_0800C614(object);

    state->radius = radius;
    render_object(object);
}
