typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gSaveSlotWindowContext;
extern u8 gSaveSlotWindowGraphics[];
extern u8 gSaveSlotWindowDisplay[];
extern u8 gSaveSlotWindowScratch[];
extern u8 *ConfigureNativeWindow(u32,u32,void*,void*,void*,void*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void CopyNativeHalfwords(const void*,void*,u32) asm("RetailCall_0814186c");
extern void DrawNativeTextContent(volatile u16*,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016344");
extern void FillNativeTextRows(volatile u16*,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016560");
extern u16 *NativeLayerCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern u32 LoadNativeWindowTiles(u8*,u32,u32) asm("RetailCall_08018524");
extern void WriteSequentialNativeTiles(u32,u16*,u32,u32) asm("RetailCall_08035678");
void InitializeSaveRestoreSlotWindow(u32 include_resource) asm("Remaining38_001384B0");
void InitializeSaveRestoreSlotWindow(u32 include_resource)
{
    register u32 retained_mode asm("r9");
    register u8 *scratch asm("r10");
    u8 *context;
    void *resource;
    void *header;
    u8 *graphics;
    u8 *tiles;
    u8 *display;
    u32 tile_offset;
    u16 *tile_destination;
    u16 zero;
    retained_mode=include_resource;
    /* Capture the only incoming word before defining the retained scratch root. */
    asm("" : "+r"(retained_mode));
    scratch=gSaveSlotWindowScratch;
    asm("" : "+r"(scratch));
    context=gSaveSlotWindowContext;
    resource=*(void**)(context+20);
    header=*(void**)(context+16);
    graphics=gSaveSlotWindowGraphics;
    asm("" : "+r"(graphics));
    tiles=*(u8**)(graphics+16);
    ConfigureNativeWindow(4,12,resource,header,tiles,tiles+364,
                          0,0,2,5,13,14,2,5,13,14,13,14);
    display=gSaveSlotWindowDisplay;
    display[356]=2;
    display[357]=5;
    tile_offset=318;
    /* The same real byte displacement forms the target and its initial tile. */
    asm("" : "+r"(tile_offset));
    /* One mixed instruction: original root-first word ADD, then ordinary C store.
       Both low-register inputs are defined; flags are an actual clobber. */
    asm("add %0,%1,%2" : "=l"(tile_destination)
        : "l"(display), "l"(tile_offset) : "cc");
    *tile_destination=(u16)(tile_offset+203);
    zero=0;
    CopyNativeHalfwords(&zero,(void*)0x0600C120,0x01000600);
    {
        volatile u16 *output=*(volatile u16**)(display+332);
        u32 columns=display[344];
        u32 rows=display[345];
        DrawNativeTextContent(output,columns,rows,192,columns,5,12);
    }
    FillNativeTextRows(*(volatile u16**)(display+328),13,14,192,13,1,12);
    if(retained_mode) {
        register u32 tile_attribute asm("r5");
        u16 *destination;
        u32 count;
        tile_attribute=0xC03E;
        /* Real attribute is defined before both resource/grid calls and consumed after. */
        asm("" : "+r"(tile_attribute));
        destination=NativeLayerCell(4,1,1,1);
        count=LoadNativeWindowTiles(scratch,62,31);
        WriteSequentialNativeTiles(tile_attribute,destination,count,1);
    }
}
__asm__(".global gSaveSlotWindowContext\n.set gSaveSlotWindowContext,0x030027d8\n.global gSaveSlotWindowGraphics\n.set gSaveSlotWindowGraphics,0x03002740\n.global gSaveSlotWindowDisplay\n.set gSaveSlotWindowDisplay,0x030009e0\n.global gSaveSlotWindowScratch\n.set gSaveSlotWindowScratch,0x02003cb0\n.global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n.global RetailCall_08016344\n.thumb_set RetailCall_08016344,0x08016345\n.global RetailCall_08016560\n.thumb_set RetailCall_08016560,0x08016561\n.global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n.global RetailCall_08018524\n.thumb_set RetailCall_08018524,0x08018525\n.global RetailCall_08035678\n.thumb_set RetailCall_08035678,0x08035679");
