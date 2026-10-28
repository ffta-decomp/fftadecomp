typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *NativeLabelPanelContext;
extern u8 NativeLabelPanelWorkspace[];
extern u8 NativeLabelPanelLayouts[];
extern const u8 NativeLabelPanelMap[];
extern void *ConfigureNativeLabelPanel(u32,u8,u32,u32,u8 *,u8 *,u8 *,u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void TransferNativeLabelPanelHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u16 *ResolveNativeLabelPanelCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeLabelPanelTilePairs(u32,u16 *,u32,u32,u32) asm("RetailCall_0808b7c0");
extern void WriteNativeLabelPanelTileSequence(u32,u16 *,u32,u32) asm("RetailCall_08035678");
void InitializeNativePairedLabelPanels(void) asm("CoreScene34_000753C8");
void InitializeNativePairedLabelPanels(void)
{
    u8 **initial_root_cell;
    register u8 **root_cell asm("r8");
    register u8 **second_root_cell asm("r1");
    register u8 *initial_workspace asm("r1");
    register u8 *workspace asm("r9");
    register u8 *second_workspace asm("r1");
    register u32 tile_label asm("r5");
    u32 cleared_flag;
    u8 *context;
    u32 shared_context_12;
    u32 context_24;
    u32 context_20;
    u8 *buffer;
    u8 *layout_state;
    u16 *tiles;
    u32 pair_mask;
    register u32 first_tile asm("r2");
    initial_root_cell=&NativeLabelPanelContext;
    root_cell=initial_root_cell;
    asm("" : "+r"(root_cell));
    context=*initial_root_cell;
    shared_context_12=*(u32 *)(context+12);
    initial_workspace=NativeLabelPanelWorkspace;
    asm("" : "+r"(initial_workspace));
    workspace=initial_workspace;
    asm("" : "+r"(workspace));
    buffer=*(u8 **)(initial_workspace+8);
    ConfigureNativeLabelPanel(2,3,shared_context_12,shared_context_12,
        buffer,buffer,(u8 *)(cleared_flag=0),0,0,0,32,9,0,0,32,9,32,9);
    asm("" : "+r"(cleared_flag));
    layout_state=NativeLabelPanelLayouts;
    asm("" : "+r"(layout_state));
    layout_state[204]=cleared_flag;
    layout_state[205]=248;
    layout_state[200]=cleared_flag;
    layout_state[201]=cleared_flag;
    layout_state[202]=32;
    layout_state[203]=9;
    TransferNativeLabelPanelHalfwords(NativeLabelPanelMap,*(void **)(layout_state+180),288);
    tiles=ResolveNativeLabelPanelCell(2,1,6,2);
    first_tile=0x177;
    asm("" : "+r"(first_tile));
    pair_mask=0xc000;
    WriteNativeLabelPanelTilePairs(2,tiles,first_tile,12,pair_mask);
    tiles=ResolveNativeLabelPanelCell(2,1,6,4);
    WriteNativeLabelPanelTilePairs(2,tiles,0x18f,12,pair_mask);
    tile_label=0xf14e;
    asm("" : "+r"(tile_label));
    tiles=ResolveNativeLabelPanelCell(2,1,9,0);
    WriteNativeLabelPanelTileSequence(tile_label,tiles,2,1);
    tile_label += 2;
    tiles=ResolveNativeLabelPanelCell(2,1,9,1);
    WriteNativeLabelPanelTileSequence(tile_label,tiles,2,1);
    tile_label=0xe09e;
    asm("" : "+r"(tile_label));
    tiles=ResolveNativeLabelPanelCell(2,1,13,0);
    WriteNativeLabelPanelTileSequence(tile_label,tiles,2,1);
    tile_label += 2;
    tiles=ResolveNativeLabelPanelCell(2,1,13,1);
    WriteNativeLabelPanelTileSequence(tile_label,tiles,2,1);
    second_root_cell=root_cell;
    asm("" : "+r"(second_root_cell));
    context=*second_root_cell;
    context_24=*(u32 *)(context+24);
    context_20=*(u32 *)(context+20);
    second_workspace=workspace;
    asm("" : "+r"(second_workspace));
    buffer=*(u8 **)(second_workspace+12);
    ConfigureNativeLabelPanel(3,12,context_24,context_20,
        buffer,buffer+384,(u8 *)cleared_flag,(u8 *)cleared_flag,cleared_flag,7,16,12,cleared_flag,7,16,12,16,12);
    layout_state[280]=cleared_flag;
    layout_state[281]=7;
    layout_state[276]=cleared_flag;
    layout_state[277]=7;
    layout_state[278]=16;
    layout_state[279]=19;
}
__asm__(".global NativeLabelPanelContext\n.set NativeLabelPanelContext,0x03002818\n"
        ".global NativeLabelPanelWorkspace\n.set NativeLabelPanelWorkspace,0x03002740\n"
        ".global NativeLabelPanelLayouts\n.set NativeLabelPanelLayouts,0x030009e0\n"
        ".global NativeLabelPanelMap\n.set NativeLabelPanelMap,0x0894fd14\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n"
        ".global RetailCall_08035678\n.thumb_set RetailCall_08035678,0x08035679\n");
