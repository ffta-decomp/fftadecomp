typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *NativeWindowContext;
extern u8 NativeWindowBufferState[];
extern u8 NativeWindowLayouts[];
extern void *ConfigureNativeWindowRecord(u32,u8,u32,u32,u8 *,u8 *,u8 *,u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void CopyNativeWindowPlaneRows(u32) asm("RetailCall_0808aa18");
extern void RenderNativeWindowFrame(volatile u16 *,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016800");
extern u16 *ResolveNativeWindowTilemap(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeWindowTilePairs(u32,u16 *,u16,u16,u16) asm("RetailCall_0808b7c0");
extern void FillNativeWindowHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
void InitializeNativeTwoRowTextWindow(void) asm("CoreRegion_00045BFC");
void InitializeNativeTwoRowTextWindow(void)
{
    u8 *context=NativeWindowContext;
    u32 context_148=*(u32 *)(context+148);
    u32 context_144=*(u32 *)(context+144);
    u8 *buffer;
    register u8 *buffer_state asm("r0");
    register u8 *layout_state asm("r2");
    u16 *tiles;
    register volatile u16 *frame_output asm("r0");
    u32 columns;
    u32 rows;
    u16 zero;
    register u16 *zero_address asm("r1");
    buffer_state=NativeWindowBufferState;
    asm("" : "+r"(buffer_state));
    buffer=*(u8 **)(buffer_state+24);
    ConfigureNativeWindowRecord(6,12,context_148,context_144,
        buffer,buffer+336,buffer+672,buffer+1008,
        1,8,28,6,1,8,30,6,28,6);
    CopyNativeWindowPlaneRows(6);
    layout_state=NativeWindowLayouts;
    asm("" : "+r"(layout_state));
    frame_output=*(volatile u16 **)(layout_state+480);
    asm("" : "+r"(frame_output));
    columns=layout_state[496];
    rows=layout_state[497];
    RenderNativeWindowFrame(frame_output,columns,rows,2048,columns,13,3,11);
    tiles=ResolveNativeWindowTilemap(6,1,1,1);
    WriteNativeWindowTilePairs(6,tiles,0x24f,24,0xb000);
    tiles=ResolveNativeWindowTilemap(6,1,1,3);
    WriteNativeWindowTilePairs(6,tiles,0x27f,24,0xb000);
    zero_address=&zero;
    asm("" : "+r"(zero_address));
    *zero_address=0;
    FillNativeWindowHalfwords(&zero,(void *)0x0600c9e0,0x01000780);
}
__asm__(".global NativeWindowContext\n.set NativeWindowContext,0x03002810\n"
        ".global NativeWindowBufferState\n.set NativeWindowBufferState,0x03002740\n"
        ".global NativeWindowLayouts\n.set NativeWindowLayouts,0x030009e0\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0808aa18\n.thumb_set RetailCall_0808aa18,0x0808aa19\n"
        ".global RetailCall_08016800\n.thumb_set RetailCall_08016800,0x08016801\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
);
