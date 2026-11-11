typedef unsigned char u8;
typedef unsigned short u16;
struct Resource {u8 before[20];u16 flags;};
void Source52_000112A4(struct Resource *resource,u8 enabled)
{
 if(enabled) resource->flags |= 0x1000;
 else resource->flags &= 0xefff;
}
