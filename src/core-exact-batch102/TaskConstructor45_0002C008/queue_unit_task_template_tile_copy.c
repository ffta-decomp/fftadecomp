typedef unsigned short u16;
typedef unsigned int u32;
extern void *NextRequest(void);
extern void QueueCopy32(void *, u32, u32, u16);
__asm__(".global NextRequest\n.thumb_set NextRequest, 0x0802BA09\n.global QueueCopy32\n.thumb_set QueueCopy32, 0x08000ADD");
void TaskConstructor45_0002C008(u32 source_offset, u32 destination_offset)
{
    u32 source = (u16)source_offset;
    u32 destination = (u16)destination_offset;
    void *request = NextRequest();
    source += 0x06013900;
    destination += 0x06013900;
    QueueCopy32(request, source, destination, 8);
}
