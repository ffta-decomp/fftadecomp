typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *NativePanelSceneContext;
extern u8 NativePanelBufferState[];
extern u8 NativePanelLayouts[];
extern u8 NativePanelResourceScratch[];
extern void *ConfigureNativePanelRecord(u32,u8,u32,u32,u8 *,u8 *,u8 *,u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void RenderNativePanelFrame(volatile u16 *,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016344");
extern void FillNativePanelRows(volatile u16 *,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016560");
extern u16 *ResolveNativePanelTilemap(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern u32 LoadNativePanelResource(void *,u32,u32) asm("RetailCall_08018524");
extern void WriteNativePanelTileSequence(u32,u16 *,u32,u32) asm("RetailCall_08035678");
void InitializeNativeResourcePanel(void) asm("CoreScene34_000734CC");
void InitializeNativeResourcePanel(void)
{
    register u8 *scratch asm("r8")=NativePanelResourceScratch;
    u8 *context;
    u32 context_24;
    u32 context_20;
    register u8 *buffer_state asm("r0");
    u8 *buffer;
    u8 *layout_state;
    register volatile u16 *frame_output asm("r0");
    register u32 tile_flags asm("r5");
    u32 columns;
    u32 rows;
    u16 *tiles;
    u32 resource;
    u16 *tile_base_address;
    u8 *first_enabled_address;
    register u32 cleared_flag asm("r1");
    register u32 row_enabled asm("r4");
    register u32 panel_tile_base asm("r0");
    asm("" : "+r"(scratch));
    context=NativePanelSceneContext;
    context_24=*(u32 *)(context+24);
    context_20=*(u32 *)(context+20);
    buffer_state=NativePanelBufferState;
    asm("" : "+r"(buffer_state));
    buffer=*(u8 **)(buffer_state+12);
    ConfigureNativePanelRecord(3,12,context_24,context_20,
        buffer,buffer+144,0,0,11,3,8,9,11,3,8,9,8,9);
    layout_state=NativePanelLayouts;
    asm("" : "+r"(layout_state));
    layout_state[280]=11;
    layout_state[281]=3;
    tile_base_address=(u16 *)(layout_state+242);
    cleared_flag=0;
    asm("" : "+r"(cleared_flag));
    panel_tile_base=375;
    asm("" : "+r"(panel_tile_base));
    *tile_base_address=panel_tile_base;
    layout_state[229]=cleared_flag;
    first_enabled_address=layout_state+300;
    row_enabled=1;
    asm("" : "+r"(row_enabled));
    *first_enabled_address=row_enabled;
    layout_state[301]=row_enabled;
    layout_state[302]=6;
    layout_state[303]=6;
    frame_output=*(volatile u16 **)(layout_state+256);
    asm("" : "+r"(frame_output));
    columns=layout_state[268];
    rows=layout_state[269];
    RenderNativePanelFrame(frame_output,columns,rows,192,columns,5,12);
    frame_output=*(volatile u16 **)(layout_state+252);
    asm("" : "+r"(frame_output));
    FillNativePanelRows(frame_output,8,9,192,8,row_enabled,12);
    tile_flags=0xc03e;
    asm("" : "+r"(tile_flags));
    tiles=ResolveNativePanelTilemap(3,1,1,1);
    resource=LoadNativePanelResource(scratch,62,3);
    WriteNativePanelTileSequence(tile_flags,tiles,resource,1);
}
__asm__(".global NativePanelSceneContext\n.set NativePanelSceneContext,0x03002818\n"
        ".global NativePanelBufferState\n.set NativePanelBufferState,0x03002740\n"
        ".global NativePanelLayouts\n.set NativePanelLayouts,0x030009e0\n"
        ".global NativePanelResourceScratch\n.set NativePanelResourceScratch,0x02003cb0\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_08016344\n.thumb_set RetailCall_08016344,0x08016345\n"
        ".global RetailCall_08016560\n.thumb_set RetailCall_08016560,0x08016561\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_08018524\n.thumb_set RetailCall_08018524,0x08018525\n"
        ".global RetailCall_08035678\n.thumb_set RetailCall_08035678,0x08035679\n");
