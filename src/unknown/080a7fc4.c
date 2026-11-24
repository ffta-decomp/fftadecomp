typedef signed short s16;
extern void InitializeCoordinateSegment(void *segment,int x0,int y0,int x1,int y1);
__asm__(".global InitializeCoordinateSegment\n.thumb_set InitializeCoordinateSegment,0x080a0469");
void InitializeSignedCoordinateSegment(void *segment,s16 x0,s16 y0,s16 x1,s16 y1) __asm__("CoreRegion30_000A7FC4");
void InitializeSignedCoordinateSegment(void *segment,s16 x0,s16 y0,s16 x1,s16 y1)
{
    InitializeCoordinateSegment(segment,x0,y0,x1,y1);
}
