/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801010C.c
 * Original SHA-256: d2a837851cef6a44745b5199efb6946ba9c3abe7dfb057cd525b60aea31d40c7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801010C..0x0801015E: 82 bytes / 37 instructions. */
struct Range0801010C {
    u16 start;
    u16 end;
};

struct State0801010C {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    struct Range0801010C ranges[160];
    u16 radius;
};

extern struct State0801010C *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count,
                         u8 start, u8 end);
extern void func_0800E718(s32 x, s32 y, u16 radius,
                         struct Range0801010C *ranges, u8 clip);

static inline void render_object(void *object)
{
    struct State0801010C *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800E718(state->x, state->y, state->radius, state->ranges, 1);
}

void func_0801010C(void *object, u16 radius)
{
    func_0800C614(object)->radius = radius;
    render_object(object);
}
