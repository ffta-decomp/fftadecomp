typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *NativeLayerCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeTilePairs(u32,u16*,u16,u16,u16) asm("RetailCall_0808b7c0");
void RefreshSaveRestoreSlotTileStyles(u8 *context,u32 mode) asm("Remaining38_00138DA4");
void RefreshSaveRestoreSlotTileStyles(u8 *context,u32 mode)
{
    register u32 layer asm("r4")=4;
    u16 tile;
    u16 *destination;
    /* Actual layer carrier is initialized in R4 before the fullword mode tests. */
    asm("" : "+r"(layer));
    if(mode==1) {
        tile=0x209;
        /* Actual tile is defined before the grid-pointer call and survives it. */
        asm("" : "+r"(tile));
        destination=NativeLayerCell(4,1,1,3);
        WriteNativeTilePairs(4,destination,tile,11,0xB000);
    } else if(mode==2) {
        tile=0x269;
        asm("" : "+r"(tile));
        destination=NativeLayerCell(5,1,1,3);
        WriteNativeTilePairs(5,destination,tile,11,0xB000);
    } else {
        if(context[262]) {
            tile=0x269;
            layer=5;
        } else {
            tile=0x209;
        }
        destination=NativeLayerCell(layer,1,1,3);
        WriteNativeTilePairs(layer,destination,tile,11,0xC000);
        /* This independently fresh flag is read after both helper calls. */
        if(context[261]) {
            tile=0x269;
            layer=5;
        } else {
            tile=0x209;
            layer=4;
        }
        destination=NativeLayerCell(layer,1,1,3);
        WriteNativeTilePairs(layer,destination,tile,11,0xB000);
    }
}
__asm__(".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n.global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1");
