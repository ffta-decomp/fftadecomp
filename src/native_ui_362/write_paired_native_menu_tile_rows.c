typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gNativeMenuTileDisplays[];
void WritePairedNativeMenuTileRows(u32 index,u16 *destination,u16 tile,u16 width,u16 mask) asm("CoreRegion_0008B7C0");
void WritePairedNativeMenuTileRows(u32 index,u16 *destination,u16 tile,u16 width,u16 mask)
{
    u8 *display_base=gNativeMenuTileDisplays;
    u32 stride;
    /* Preserve the original display-root plus record-offset calculation;
       no value is fabricated, and no instruction is emitted here. */
    asm("" : "+r"(display_base));
    stride=(display_base+76*index)[40];
    if (width!=0) {
        u32 row_bytes=(u32)stride*2;
        u32 remaining=width;
        do {
            destination[0]=tile|mask;
            *(u16 *)(row_bytes+(u32)destination)=(tile+1)|mask;
            remaining--;
            destination++;
            tile+=2;
        } while (remaining!=0);
    }
}
__asm__(".global gNativeMenuTileDisplays\n.set gNativeMenuTileDisplays,0x030009e0");
