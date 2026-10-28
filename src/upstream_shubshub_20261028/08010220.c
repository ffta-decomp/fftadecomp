/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010220.c
 * Original SHA-256: fd4c4b8dcd42ee76e81f2ddac185777dba6a00620fbf69ed14ed4a5a9281699e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} Point;

typedef struct {
    u16 start;
    u16 end;
} Range;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    Range ranges[160];
    Point vertices[3];
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count,
                          u8 start, u8 end);
extern void func_0800F308(const Point *vertices, u32 count, s32 x, s32 y,
                          Range *ranges, u32 mode);

/* 08010220..08010282: 98 bytes, 45 instructions. */
void func_08010220(void *object, const Point *source)
{
    Point *destination = func_0800C614(object)->vertices;
    RenderState *state;
    s32 remaining;

    for (remaining = 2; remaining >= 0; remaining--) {
        destination->x = source->x;
        destination->y = source->y;
        destination++;
        source++;
    }

    state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F308(state->vertices, 3, state->x, state->y, state->ranges, 1);
}
