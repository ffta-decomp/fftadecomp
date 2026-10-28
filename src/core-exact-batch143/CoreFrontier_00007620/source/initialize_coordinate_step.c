typedef unsigned short u16;
typedef signed short s16;
struct CoordinateStep { u16 x,y,end_x,end_y,step_x,step_y,dx,dy,accumulator,half_dy,remaining; };
void InitializeCoordinateStep(struct CoordinateStep *p, u16 x, u16 y, u16 end_x, u16 end_y) __asm__("CoreFrontier_00007620");
void InitializeCoordinateStep(struct CoordinateStep *p, u16 x, u16 y, u16 end_x, u16 end_y)
{
    int difference;
    u16 distance;
    unsigned int shifted_distance;
    p->x=x; p->y=y; p->end_x=end_x; p->end_y=end_y;
    difference=(s16)end_x-(s16)x;
    p->dx=difference;
    if ((s16)difference<0) { p->dx=-difference; p->step_x=0xffff; }
    else p->step_x=1;
    difference=(s16)end_y-(s16)y;
    p->dy=difference;
    if ((s16)difference<0) { p->dy=-difference; p->step_y=0xffff; }
    else p->step_y=1;
    distance=p->dy;
    shifted_distance=(unsigned int)distance<<16;
    p->half_dy=(int)shifted_distance>>17;
    p->accumulator=0;
    p->remaining=distance;
    if (!shifted_distance) p->x=end_x;
}
