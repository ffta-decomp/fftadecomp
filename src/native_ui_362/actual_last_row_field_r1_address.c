typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *NativeChoiceWindowContext;
extern u8 NativeChoiceWindowWorkspace[];
extern u8 NativeChoiceWindowLayouts[];
extern void *ConfigureNativeChoiceWindow(u32,u8,u32,u32,u8 *,u8 *,u8 *,u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern u16 *ResolveNativeChoiceWindowCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeChoiceWindowTilePairs(u32,u16 *,u16,u16,u16) asm("RetailCall_0808b7c0");
void InitializeNativeModeChoiceWindow(u32) asm("CoreScene34_00074CE8");
void InitializeNativeModeChoiceWindow(u32 mode)
{
    u8 *context=NativeChoiceWindowContext;
    u32 context_24=*(u32 *)(context+24);
    u32 context_20=*(u32 *)(context+20);
    register u8 *workspace asm("r0");
    register u8 *layout_state asm("r2");
    register u32 cleared_flag asm("r1");
    register u32 panel_tile_base asm("r0");
    register u32 row_enabled asm("r1");
    u8 *buffer;
    u16 *tile_base_address;
    u8 *first_enabled_address;
    register u8 *last_row_address asm("r1");
    s32 previous_y;
    workspace=NativeChoiceWindowWorkspace;
    asm("" : "+r"(workspace));
    buffer=*(u8 **)(workspace+16);
    ConfigureNativeChoiceWindow(4,12,context_24,context_20,
        buffer,buffer+364,0,0,16,6,14,13,16,6,14,13,14,13);
    layout_state=NativeChoiceWindowLayouts;
    asm("" : "+r"(layout_state));
    layout_state[356]=mode;
    layout_state[357]=6;
    tile_base_address=(u16 *)(layout_state+318);
    cleared_flag=0;
    asm("" : "+r"(cleared_flag));
    panel_tile_base=423;
    asm("" : "+r"(panel_tile_base));
    *tile_base_address=panel_tile_base;
    layout_state[305]=cleared_flag;
    first_enabled_address=layout_state+376;
    row_enabled=1;
    asm("" : "+r"(row_enabled));
    *first_enabled_address=row_enabled;
    layout_state[377]=row_enabled;
    layout_state[378]=13;
    last_row_address=layout_state+379;
    asm("" : "+r"(last_row_address));
    *last_row_address=10;
    previous_y=0;
    do {
        s32 next_y=previous_y+2;
        u16 *tiles=ResolveNativeChoiceWindowCell(4,1,1,(u32)next_y);
        WriteNativeChoiceWindowTilePairs(4,tiles,(u16)(13*previous_y+423),13,0xc000);
        previous_y=next_y;
    } while (previous_y<=9);
}
__asm__(".global NativeChoiceWindowContext\n.set NativeChoiceWindowContext,0x03002818\n"
        ".global NativeChoiceWindowWorkspace\n.set NativeChoiceWindowWorkspace,0x03002740\n"
        ".global NativeChoiceWindowLayouts\n.set NativeChoiceWindowLayouts,0x030009e0\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n");
