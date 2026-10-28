typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gNativeJobMenuOwner;
extern u8 gNativeJobMenuBuffers[];
extern u8 gNativeJobMenuDisplays[];
extern void *ConfigureNativeJobMenuWindow(u32,u8,u32,u32,u8*,u8*,u8*,u8*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern u16 *ResolveNativeJobMenuTilemap(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void FillNativeJobMenuPairedRows(u32,u16*,u16,u16) asm("RetailCall_0808b858");
extern void CopyNativeJobMenuHalfwords(const void*,void*,u32) asm("RetailCall_0814186c");
extern void WriteNativeJobMenuTilePairs(u32,u16*,u16,u16,u16) asm("RetailCall_0808b7c0");
void InitializeNativeJobMenuWindow(u32) asm("CoreScene34_00085678");
void InitializeNativeJobMenuWindow(u32 configuration)
{
    u8 *owner=gNativeJobMenuOwner;
    u32 frame_resource=*(u32 *)(owner+12);
    u32 window_resource=*(u32 *)(owner+20);
    register u8 *buffer_root asm("r0")=gNativeJobMenuBuffers;
    u8 *buffer;
    register u8 *display asm("r2");
    u16 zero;
    asm("" : "+r"(buffer_root));
    buffer=*(u8 **)(buffer_root+16);
    ConfigureNativeJobMenuWindow(4,12,frame_resource,window_resource,
        buffer,buffer+52,0,0,16,18,13,2,16,18,13,2,13,2);
    display=gNativeJobMenuDisplays;
    asm("" : "+r"(display));
    display[356]=configuration;
    display[357]=18;
    {
        register u32 tile_offset asm("r0")=318;
        register u16 *tile_address asm("r3");
        register u32 clear asm("r1");
        /* The real byte-offset producer becomes the subsequent tile value. */
        asm("" : "+r"(tile_offset));
        tile_address=(u16 *)(display+tile_offset);
        /* Actual H318 address is live before the distinct postcall zero. */
        asm("" : "+r"(tile_address));
        clear=0;
        asm("" : "+r"(clear));
        *tile_address=tile_offset+81;
        display[305]=clear;
    }
    display[376]=1;
    display[377]=1;
    display[378]=12;
    display[379]=2;
    /* Retain the actual base through its last field-store consumer. */
    asm("" : : "r"(display));
    FillNativeJobMenuPairedRows(4,ResolveNativeJobMenuTilemap(4,1,0,0),0,12);
    zero=0;
    CopyNativeJobMenuHalfwords(&zero,(void *)0x0600B4E0,0x010002C0);
    WriteNativeJobMenuTilePairs(4,ResolveNativeJobMenuTilemap(4,1,0,0),423,12,0xC000);
}
__asm__(".global gNativeJobMenuOwner\n.set gNativeJobMenuOwner,0x03002818\n"
        ".global gNativeJobMenuBuffers\n.set gNativeJobMenuBuffers,0x03002740\n"
        ".global gNativeJobMenuDisplays\n.set gNativeJobMenuDisplays,0x030009e0\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b858\n.thumb_set RetailCall_0808b858,0x0808b859\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n");
