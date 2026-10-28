typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gSaveWindowContext;
extern u8 gSaveWindowDisplay[];
extern u8 gSaveWindowGraphics[];
extern u8 *ConfigureNativeWindow(u32,u32,void*,void*,void*,void*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void CopyNativeHalfwords(const void*,void*,u32) asm("RetailCall_0814186c");
extern u16 *NativeLayerCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeTilePairs(u32,u16*,u16,u16,u16) asm("RetailCall_0808b7c0");
extern void DrawNativeTextFrame(volatile u16*,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016800");
void InitializeSaveRestoreHeaderWindow(void) asm("Remaining38_00138284");
void InitializeSaveRestoreHeaderWindow(void)
{
    u8 *context=gSaveWindowContext;
    void *resource=*(void**)(context+8);
    void *header=*(void**)(context+16);
    u8 *graphics=gSaveWindowGraphics;
    u8 *tiles;
    u8 *display;
    u16 zero;
    u16 tile;
    u16 *tile_destination;
    /* Actual root definition precedes its +12 member load. */
    asm("" : "+r"(graphics));
    tiles=*(u8**)(graphics+12);
    ConfigureNativeWindow(3,12,resource,header,tiles,tiles+216,
                          0,0,2,1,27,4,2,1,27,4,27,4);
    display=gSaveWindowDisplay;
    display[280]=2;
    display[281]=1;
    tile_destination=(u16*)(display+242);
    /* The actual store address is formed before the retained tile definition. */
    asm("" : "+r"(tile_destination));
    tile=471;
    /* Actual halfword tile definition survives both intervening calls. */
    asm("" : "+r"(tile));
    *tile_destination=tile;
    zero=0;
    CopyNativeHalfwords(&zero,(void*)0x0600BAE0,0x01000320);
    WriteNativeTilePairs(3,NativeLayerCell(3,1,1,1),tile,25,0xB000);
    {
        volatile u16 *output=*(volatile u16**)(display+252);
        u32 columns=display[268];
        u32 rows=display[269];
        DrawNativeTextFrame(output,columns,rows,0x800,columns,13,3,11);
    }
}
__asm__(".global gSaveWindowContext\n.set gSaveWindowContext,0x030027d8\n.global gSaveWindowDisplay\n.set gSaveWindowDisplay,0x030009e0\n.global gSaveWindowGraphics\n.set gSaveWindowGraphics,0x03002740\n.global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n.global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n.global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n.global RetailCall_08016800\n.thumb_set RetailCall_08016800,0x08016801");
