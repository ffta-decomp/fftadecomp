typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct CoordinateSegment {
    s16 start_x;
    s16 start_z;
    s16 end_x;
    s16 end_z;
    s16 half_extent;
    s16 extent;
    s16 step_x;
    s16 step_z;
    u16 absolute_x;
    u16 absolute_z;
} CoordinateSegment;
typedef char SegmentMustBeTwentyBytes[sizeof(CoordinateSegment) == 20 ? 1 : -1];
extern s32 DivideSigned(s32 numerator, s32 denominator) __asm__("RetailCall_081426b8");

void CoreRegion30_000A0468(CoordinateSegment *segment, s32 start_x, s32 start_z,
                         s32 end_x, s32 end_z)
{
    s32 delta_x, delta_z, absolute_x, absolute_z, denominator;
    segment->start_x = start_x;
    segment->start_z = start_z;
    segment->end_x = end_x;
    segment->end_z = end_z;
    delta_x = segment->end_x - segment->start_x;
    delta_z = segment->end_z - segment->start_z;
    absolute_x = delta_x;
    if (delta_x < 0)
        absolute_x = -delta_x;
    segment->absolute_x = absolute_x;
    absolute_z = delta_z;
    if (delta_z < 0)
        absolute_z = -delta_z;
    segment->absolute_z = absolute_z;
    if ((s16)absolute_x >= (s16)absolute_z)
        segment->extent = absolute_x;
    else
        segment->extent = absolute_z;
    segment->half_extent = segment->extent >> 1;
    segment->step_x = 0;
    segment->step_z = 0;
    if (delta_x != 0) {
        denominator = delta_x;
        if (denominator < 0)
            denominator = -denominator;
        segment->step_x = DivideSigned(delta_x, denominator);
    }
    if (delta_z != 0) {
        denominator = delta_z;
        if (denominator < 0)
            denominator = -denominator;
        segment->step_z = DivideSigned(delta_z, denominator);
    }
}
