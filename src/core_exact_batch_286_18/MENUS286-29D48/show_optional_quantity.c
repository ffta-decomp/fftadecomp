typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Surface { u8 unknown00[20]; u16 *buffer20; };
extern struct Surface gSurface;
extern void RenderNumber(struct Surface*,u8,u8,u8,u32,u8);
__asm__(".global gSurface\n.set gSurface,0x030008b0\n.global RenderNumber\n.thumb_set RenderNumber,0x08029689");

void ShowOptionalQuantity(u8 x,u8 y,u8 value,u8 palette) __asm__("CoreGlobal36_00029D48");
void ShowOptionalQuantity(u8 x,u8 y,u8 value,u8 palette)
{
    u16 *buffer=gSurface.buffer20;
    u16 *cell;
    u16 *first;
    u32 byte_offset;
    u32 bank;
    /* Source captures the backing buffer before calculating this cell. */
    __asm__("" : : "r"(buffer));
    byte_offset=(y*32+x)*2;
    cell=(u16*)(byte_offset+(u32)buffer);
    first=cell+161;
    /* The first output address is materialized before the palette shift. */
    __asm__("" : : "r"(first));
    bank=(u32)palette<<12;
    *first=0x73|bank;
    cell[162]=0x74|bank;
    if (value!=0) {
        RenderNumber(&gSurface,(u8)(x+2),(u8)(y+5),2,value,palette);
    } else {
        cell[163]=0x75|bank;
        cell[164]=0x75|bank;
    }
}
