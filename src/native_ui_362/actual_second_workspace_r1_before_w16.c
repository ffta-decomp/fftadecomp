typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *NativeDualPanelContext;
extern u8 NativeDualPanelWorkspace[];
extern u8 NativeDualPanelLayouts[];
extern const u8 NativeDualPanelUpperMap[];
extern const u8 NativeDualPanelLowerMap[];
extern void *ConfigureNativeDualPanel(u32,u8,u32,u32,u8 *,u8 *,u8 *,u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void TransferNativeDualPanelHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u16 *ResolveNativeDualPanelCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeDualPanelTilePairs(u32,u16 *,u16,u16,u16) asm("RetailCall_0808b7c0");
void InitializeNativeDualResourcePanels(void) asm("CoreScene34_000735E0");
void InitializeNativeDualResourcePanels(void)
{
    u8 **initial_root_cell;
    register u8 **root_cell asm("r9");
    register u8 **second_root_cell asm("r1");
    register u8 *initial_workspace asm("r1");
    register u8 *workspace asm("r8");
    register u8 *second_workspace asm("r1");
    u8 *context;
    u32 context_24;
    u32 context_20;
    u8 *buffer;
    u8 *layout_state;
    u16 *tiles;
    u16 zero;
    register u16 *zero_address asm("r0");
    initial_root_cell=&NativeDualPanelContext;
    root_cell=initial_root_cell;
    asm("" : "+r"(root_cell));
    context=*initial_root_cell;
    context_24=*(u32 *)(context+24);
    context_20=*(u32 *)(context+20);
    initial_workspace=NativeDualPanelWorkspace;
    asm("" : "+r"(initial_workspace));
    workspace=initial_workspace;
    asm("" : "+r"(workspace));
    buffer=*(u8 **)(initial_workspace+8);
    ConfigureNativeDualPanel(2,12,context_24,context_20,
        buffer,buffer+252,0,0,0,2,18,7,0,2,18,7,18,7);
    layout_state=NativeDualPanelLayouts;
    asm("" : "+r"(layout_state));
    layout_state[204]=238;
    layout_state[205]=2;
    layout_state[200]=0;
    layout_state[201]=2;
    layout_state[202]=18;
    layout_state[203]=9;
    TransferNativeDualPanelHalfwords(NativeDualPanelUpperMap,*(void **)(layout_state+180),126);
    TransferNativeDualPanelHalfwords(NativeDualPanelLowerMap,*(void **)(layout_state+176),126);
    tiles=ResolveNativeDualPanelCell(2,1,6,0);
    WriteNativeDualPanelTilePairs(2,tiles,0x177,12,0xc000);
    second_root_cell=root_cell;
    asm("" : "+r"(second_root_cell));
    context=*second_root_cell;
    context_24=*(u32 *)(context+24);
    context_20=*(u32 *)(context+20);
    second_workspace=workspace;
    asm("" : "+r"(second_workspace));
    buffer=*(u8 **)(second_workspace+16);
    ConfigureNativeDualPanel(4,12,context_24,context_20,
        buffer,buffer+60,0,0,0,0,30,1,0,0,30,1,30,1);
    layout_state[356]=0;
    layout_state[357]=0;
    zero_address=&zero;
    asm("" : "+r"(zero_address));
    *zero_address=0;
    TransferNativeDualPanelHalfwords(&zero,*(void **)(layout_state+328),0x0100000f);
}
__asm__(".global NativeDualPanelContext\n.set NativeDualPanelContext,0x03002818\n"
        ".global NativeDualPanelWorkspace\n.set NativeDualPanelWorkspace,0x03002740\n"
        ".global NativeDualPanelLayouts\n.set NativeDualPanelLayouts,0x030009e0\n"
        ".global NativeDualPanelUpperMap\n.set NativeDualPanelUpperMap,0x0894fb1c\n"
        ".global NativeDualPanelLowerMap\n.set NativeDualPanelLowerMap,0x0894fc18\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n");
