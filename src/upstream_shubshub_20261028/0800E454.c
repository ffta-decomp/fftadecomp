/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800E454.c
 * Original SHA-256: 01858bb3bbf388d164ee490dfa8b903df3890cde9fece7f16511a22599c7456e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} Point0800E454;

typedef struct {
    u16 start;
    u16 end;
} Range0800E454;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u16 flags;
    Range0800E454 ranges[160];
    Point0800E454 vertices[3];
} RenderState0800E454;

extern u16 data_04000040[];
extern void func_0800F93C(void *object);
extern void *func_0800C3CC(void (*callback)(void *), u32 size, u32 type,
                          u16 *destination);
extern RenderState0800E454 *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count,
                          u8 start, u8 end);
extern void func_0800F308(const Point0800E454 *vertices, u32 count,
                          s32 x, s32 y, Range0800E454 *ranges, u32 mode);

static inline void initialize_vertices(RenderState0800E454 *state,
                                       const Point0800E454 *source)
{
    Point0800E454 *destination;
    s32 remaining;

    state->mode = 4;
    destination = state->vertices;
    for (remaining = 2; remaining >= 0; remaining--) {
        destination->x = source->x;
        destination->y = source->y;
        destination++;
        source++;
    }
}

/* 0800E454..0800E4DC: 136 bytes, 58 instructions. */
void *func_0800E454(u8 window, const Point0800E454 *source)
{
    void *object = func_0800C3CC(func_0800F93C, 0x298, 2,
                                data_04000040 + window);
    RenderState0800E454 *state;

    initialize_vertices(func_0800C614(object), source);
    state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F308(state->vertices, 3, state->x, state->y, state->ranges, 1);
    return object;
}
