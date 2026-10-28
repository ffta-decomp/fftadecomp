typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct DialogResources {
    u8 opaque00[16];
    void *first;
    void *second;
} DialogResources;
typedef struct DialogWorkspace {
    u8 opaque00[20];
    u8 *buffer;
} DialogWorkspace;
typedef struct DialogState {
    u8 opaque00[394];
    u16 style;
    u8 opaque396[8];
    void *window404;
    void *window408;
    u8 opaque412[8];
    u8 coordinate420, coordinate421;
    u8 opaque422[10];
    u8 width432, height433;
} DialogState;
extern u8 NativeDialogScratch[];
extern DialogResources *DialogResourceRoot;
extern DialogWorkspace DialogWorkspaceState;
extern DialogState NativeDialogState;
extern void SetupDialogRecord(u32,u32,void *,void *,void *,void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_0808a268");
extern void FillNativeHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern void ConfigureDialogWindow(void *,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016344");
extern void ConfigureDialogFrame(void *,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016560");
extern u16 *GetDialogGridCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern u32 LoadDialogTileResource(void *,u32,u32) asm("RetailCall_08018524");
extern void FillNativeTileSequence(u32,u16 *,u32,u32) asm("RetailCall_08035678");
void InitNativeSaveRestoreDialog(void) asm("Remaining38_00138A3C");
void InitNativeSaveRestoreDialog(void)
{
    register void *scratch asm("r9") = NativeDialogScratch;
    DialogResources *resources;
    DialogState *state;
    void *resource_second, *resource_first;
    void *first_window;
    u32 first_coordinate, second_coordinate;
    u8 *workspace;
    u16 zero_half;
    u16 *cell;
    u32 count;
    asm("" : "+r"(scratch));
    resources = DialogResourceRoot;
    resource_second = resources->second;
    resource_first = resources->first;
    workspace = DialogWorkspaceState.buffer;
    SetupDialogRecord(5,12,resource_second,resource_first,
                      workspace,workspace+364,0,0,16,5,
                      13,14,16,5,13,14,13,14);
    state = &NativeDialogState;
    asm("" : "+r"(state));
    state->width432 = 16;
    state->height433 = 5;
    {
        u32 style_offset = 394;
        register u16 *style_field asm("r1");
        asm("" : "+r"(style_offset));
        style_field = (u16 *)((u32)state+style_offset);
        asm("" : "+r"(style_field), "+r"(style_offset));
        style_offset += 223;
        *style_field = style_offset;
    }
    zero_half = 0;
    FillNativeHalfwords(&zero_half,(void *)0x0600CD20,0x01000600);
    first_window = state->window408;
    first_coordinate = state->coordinate420;
    second_coordinate = state->coordinate421;
    ConfigureDialogWindow(first_window,first_coordinate,second_coordinate,
                          192,first_coordinate,5,12);
    ConfigureDialogFrame(state->window404,13,14,192,13,1,12);
    {
        register u32 pattern asm("r5") = 0xC044;
        asm("" : "+r"(pattern));
        cell = GetDialogGridCell(5,1,1,1);
        count = LoadDialogTileResource(scratch,68,32);
        FillNativeTileSequence(pattern,cell,count,1);
    }
}
__asm__(".global NativeDialogScratch\n.set NativeDialogScratch,0x02003CB0\n"
        ".global DialogResourceRoot\n.set DialogResourceRoot,0x030027D8\n"
        ".global DialogWorkspaceState\n.set DialogWorkspaceState,0x03002740\n"
        ".global NativeDialogState\n.set NativeDialogState,0x030009E0\n"
        ".global RetailCall_0808a268\n.thumb_set RetailCall_0808a268,0x0808a269\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_08016344\n.thumb_set RetailCall_08016344,0x08016345\n"
        ".global RetailCall_08016560\n.thumb_set RetailCall_08016560,0x08016561\n"
        ".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_08018524\n.thumb_set RetailCall_08018524,0x08018525\n"
        ".global RetailCall_08035678\n.thumb_set RetailCall_08035678,0x08035679\n");
