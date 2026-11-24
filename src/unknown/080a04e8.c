typedef unsigned int u32;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct Point3 {
    s16 x, y, z;
} __attribute__((packed, aligned(2))) Point3;
typedef struct CoordinateSegment {
    s16 start_x, start_z, end_x, end_z;
    s16 half_extent, extent, step_x, step_z;
    u16 absolute_x, absolute_z;
} CoordinateSegment;
/* An observed prefix, not a claim about the caller's whole allocation. */
typedef struct ProjectedSegment {
    CoordinateSegment vertical;
    CoordinateSegment horizontal;
    s16 absolute_x, absolute_y, absolute_z;
    u16 dominant_extent;
    Point3 start;
    u16 preserved_54;
    Point3 end;
} ProjectedSegment;
typedef char Point3HasSixBytes[sizeof(Point3) == 6 ? 1 : -1];
typedef char SegmentHasTwentyBytes[sizeof(CoordinateSegment) == 20 ? 1 : -1];
typedef char AbsoluteXAt40[(u32)&((ProjectedSegment *)0)->absolute_x == 40 ? 1 : -1];
typedef char StartAt48[(u32)&((ProjectedSegment *)0)->start == 48 ? 1 : -1];
typedef char EndAt56[(u32)&((ProjectedSegment *)0)->end == 56 ? 1 : -1];
extern void InitializeSegment(CoordinateSegment *segment, s32 start_x,
                              s32 start_z, s32 end_x, s32 end_z)
    __asm__("RetailCall_080a7fc4");

void CoreRegion30_000A04E8(ProjectedSegment *segment,
                         const Point3 *start, const Point3 *end)
{
    s32 delta;
    u16 extent;
    delta = end->x - start->x;
    if (delta < 0)
        delta = -delta;
    segment->absolute_x = delta;
    delta = end->y - start->y;
    if (delta < 0)
        delta = -delta;
    segment->absolute_y = delta;
    delta = end->z - start->z;
    if (delta < 0)
        delta = -delta;
    segment->absolute_z = delta;
    segment->start.x = start->x;
    segment->start.y = start->y;
    segment->start.z = start->z;
    segment->end.x = end->x;
    segment->end.y = end->y;
    segment->end.z = end->z;
    InitializeSegment(&segment->horizontal, start->x, start->z, end->x, end->z);
    /* Both coordinates and stored lengths remain live across the helper. */
    delta = end->y - start->y;
    if (delta < 0)
        delta = -delta;
    segment->absolute_y = delta;
    if (segment->absolute_x >= segment->absolute_z) {
        InitializeSegment(&segment->vertical, start->x, start->y, end->x, end->y);
        extent = (u16)segment->absolute_x;
    } else {
        InitializeSegment(&segment->vertical, start->z, start->y, end->z, end->y);
        extent = (u16)segment->absolute_z;
    }
    segment->dominant_extent = extent;
}

/* Callable Thumb binding only; the retained adapter body is not reproduced here. */
__asm__(".global RetailCall_080a7fc4\n.thumb_set RetailCall_080a7fc4,0x080a7fc5");
