typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
struct PositionedMarker {
    const void *descriptor;
    s16 x, y;
    s16 offset_x, offset_y;
    u8 depth, selector;
};
extern void DrawPositionedObject(const void *, int, int, u32,
                                u32, u32, u32, u32, u32, u32, u32);
__asm__(".global DrawPositionedObject\n.thumb_set DrawPositionedObject,0x08001cf1");
void DrawPositionedMarker(const struct PositionedMarker *marker)
{
    const void *descriptor = marker->descriptor;
    int x = marker->x + marker->offset_x;
    int y = marker->y + marker->offset_y;
    DrawPositionedObject(descriptor, x, y, 0,
                         0, 0, 0, 0, marker->depth, 0, marker->selector);
}
