/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0809B218.c
 * Original SHA-256: 8fd465d3a9cb0f8948137faa872f97b6c23922d55e405f55cb8f8a2407a021f9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef long long s64;

typedef struct {
    u8 x;
    u8 y;
    u8 z;
    u8 unknown_03;
} RoutePoint;

typedef struct {
    s32 x : 16;
    s32 z : 16;
    s32 y : 16;
} PackedPoint;

typedef struct {
    u8 unknown_00[4];
    RoutePoint *route;
    u8 unknown_08[0x12];
    s16 index;
    s16 step;
    u8 unknown_1e[8];
    u8 mode;
    u8 unknown_27[9];
    s64 times[3];
    u8 unknown_48[8];
    s64 heights[3];
    u8 unknown_68[8];
    s64 coefficients[4];
    s16 samples[32];
    s32 progress;
    s32 distance;
} CurveObject;

extern u8 data_0200F6F8[];
extern void func_08008480(s32 count, s64 *times, s64 *heights,
                          s64 *coefficients, void *scratch);
extern s64 func_080086D0(s64 time, s32 count, s64 *times,
                         s64 *heights, s64 *coefficients);

void func_0809B218(CurveObject *object)
{
    RoutePoint *first_route = &object->route[object->index];
    RoutePoint *second_route = &object->route[object->index + 1];
    PackedPoint first;
    PackedPoint second;
    s32 dx;
    s32 dy;
    s32 distance;
    u32 sample_index;

    first.x = first_route->x * 32 + 16;
    first.z = first_route->z * 16;
    first.y = first_route->y * 32 + 16;
    second.x = second_route->x * 32 + 16;
    second.z = second_route->z * 16;
    second.y = second_route->y * 32 + 16;

    dx = first.x - second.x;
    if (dx < 0)
        dx = -dx;
    dy = first.y - second.y;
    if (dy < 0)
        dy = -dy;
    distance = dx + dy;

    object->times[0] = 0;
    object->times[1] = (s64)(distance >> 1) << 16;
    object->times[2] = (s64)distance << 16;
    object->heights[0] = (s64)(s16)first.z << 16;

    switch (object->mode) {
    case 2:
    case 3:
        if ((s16)first.z > (s16)second.z)
            object->heights[1] = (s64)(s16)first.z << 16;
        else
            object->heights[1] = (s64)(s16)second.z << 16;
        break;
    case 1:
        object->heights[1] = (s64)((s16)first.z
            + (((u16)second.z - (s16)first.z) >> 1)) << 16;
        break;
    default:
        if (first.z > second.z)
            object->heights[1] = (s64)(first.z + 8) << 16;
        else
            object->heights[1] = (s64)(second.z + 8) << 16;
        if (first.z == second.z)
            object->heights[1] += 0x100000;
        break;
    }
    object->heights[2] = (s64)(second.z + 8) << 16;
    object->progress = 0;
    object->distance = distance;

    func_08008480(3, object->times, object->heights,
                  object->coefficients, data_0200F6F8);
    sample_index = 0;
    do {
        object->samples[sample_index] = func_080086D0((s64)object->progress << 16, 3,
            object->times, object->heights, object->coefficients) >> 16;
        sample_index++;
        object->progress += object->step;
    } while (object->progress <= object->distance);
    object->progress = 0;
}
