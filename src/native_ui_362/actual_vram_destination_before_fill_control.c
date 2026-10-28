typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *NativeWindowContext;
extern u8 NativeWindowBufferState[];
extern u8 NativeWindowLayouts[];
extern void *ConfigureNativeWindowRecord(u32,u8,u32,u32,u8 *,u8 *,u8 *,u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void RenderNativeFixedPanelFrame(volatile u16 *,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016344");
extern void FillNativeFixedPanelRows(volatile u16 *,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016560");
extern u32 BeginNativeFixedPanelOperation(u32,u16) asm("RetailCall_0808a604");
extern u16 *ResolveNativeWindowTilemap(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeWindowTilePairs(u32,u16 *,u16,u16,u16) asm("RetailCall_0808b7c0");
extern void FillNativeWindowHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
void InitializeNativeFixedPanelWindow(void) asm("CoreRegion_00039D1C");
void InitializeNativeFixedPanelWindow(void)
{
    u8 *context=NativeWindowContext;
    u32 context_148=*(u32 *)(context+148);
    u32 context_144=*(u32 *)(context+144);
    register u8 *buffer_state asm("r0");
    u8 *layout_state;
    register volatile u16 *frame_output asm("r0");
    register u16 *zero_address asm("r0");
    register void *fill_destination asm("r1");
    u8 *buffer;
    u32 columns;
    u32 rows;
    u16 zero;
    u16 *tiles;
    buffer_state=NativeWindowBufferState;
    asm("" : "+r"(buffer_state));
    buffer=*(u8 **)(buffer_state+20);
    ConfigureNativeWindowRecord(5,12,context_148,context_144,
        buffer,buffer+120,0,0,9,9,12,5,9,9,12,5,12,5);
    layout_state=NativeWindowLayouts;
    asm("" : "+r"(layout_state));
    frame_output=*(volatile u16 **)(layout_state+408);
    asm("" : "+r"(frame_output));
    columns=layout_state[420];
    rows=layout_state[421];
    RenderNativeFixedPanelFrame(frame_output,columns,rows,192,columns,5,12);
    frame_output=*(volatile u16 **)(layout_state+404);
    asm("" : "+r"(frame_output));
    FillNativeFixedPanelRows(frame_output,12,5,192,12,1,12);
    zero_address=&zero;
    asm("" : "+r"(zero_address));
    *zero_address=0;
    fill_destination=(void *)0x0600afe0;
    asm("" : "+r"(fill_destination));
    FillNativeWindowHalfwords(zero_address,fill_destination,0x01000180);
    tiles=ResolveNativeWindowTilemap(5,1,1,2);
    WriteNativeWindowTilePairs(5,tiles,0x185,10,0xc000);
    BeginNativeFixedPanelOperation(5,2);
}
__asm__(".global NativeWindowContext\n.set NativeWindowContext,0x03002810\n"
        ".global NativeWindowBufferState\n.set NativeWindowBufferState,0x03002740\n"
        ".global NativeWindowLayouts\n.set NativeWindowLayouts,0x030009e0\n"
        ".global RetailCall_08016344\n.thumb_set RetailCall_08016344,0x08016345\n"
        ".global RetailCall_08016560\n.thumb_set RetailCall_08016560,0x08016561\n"
        ".global RetailCall_0808a604\n.thumb_set RetailCall_0808a604,0x0808a605\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
);
