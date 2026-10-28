typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *NativeDialogueRoot;
extern u32 FindNativeCountedControl(const u8 *,u8) asm("RetailCall_08014b84");
extern u32 UsesNativeExtendedProfile(u8) asm("RetailCall_0801843c");
extern u32 UsesNativeAlternateSurface(u8) asm("RetailCall_08018484");
extern void InitNativeTextContext(void *,const void *) asm("RetailCall_08013528");
extern void InitNativeTextContextFields(void *,const void *,u32,u32) asm("RetailCall_08013570");
extern void SetNativeTextStyle(void *,u32) asm("RetailCall_080137c0");
extern void ClearNativeDialogueRow(void *,u16) asm("RetailCall_08013a88");
#define WORD(p,o) (*(u32 *)((p)+(o)))
#define HALF(p,o) (*(u16 *)((p)+(o)))
void PopNativeDialogueTextLevel(void) asm("Source52_00012C30");
void PopNativeDialogueTextLevel(void)
{
    register u8 **root_address asm("r5")=&NativeDialogueRoot;
    u8 *state=*root_address;
    register u8 *depth_slot asm("r3")=state+42;
    register u32 raw_depth asm("r1")=*depth_slot;
    register u32 depth asm("r4")=raw_depth;
    u32 continuation;
    s32 row;
    asm("" : "+r"(root_address), "+r"(depth_slot), "+r"(raw_depth), "+r"(depth));
    if (depth==0) {
        WORD(state,776)=(u32)(state+1804);
        state[1804]=0x40;
        (*root_address)[1805]=0x63;
        {
            u8 *terminal_base=*root_address;
            register u32 terminal_offset asm("r2")=1806;
            asm("" : "+r"(terminal_offset));
            terminal_base[terminal_offset]=depth;
        }
        return;
    }
    {
        const u8 *source=state+780;
        raw_depth--;
        depth=0;
        asm("" : "+r"(depth));
        *depth_slot=raw_depth;
        continuation=FindNativeCountedControl(source,(u8)raw_depth);
    }
    state=*root_address;
    WORD(state,776)=continuation;
    WORD(state,772)=WORD(state,768);
    state[64]=depth;
    {
    u8 *reset_state=*root_address;
    {
        register u32 reset_flag asm("r0")=0x1000;
        asm("" : "+r"(reset_flag));
        HALF(reset_state,22)=reset_flag;
        reset_flag=0x8000;
        asm("" : "+r"(reset_flag));
        HALF(reset_state,24)=reset_flag;
    }
    if ((u8)UsesNativeExtendedProfile(reset_state[10])) {
        u8 *extended_state=*root_address;
        InitNativeTextContextFields(extended_state+112,(const void *)WORD(extended_state,772),extended_state[26],1);
    } else {
        u8 *default_state=*root_address;
        InitNativeTextContext(default_state+112,(const void *)WORD(default_state,772));
    }
    }
    if ((u8)UsesNativeAlternateSurface(NativeDialogueRoot[10]))
        SetNativeTextStyle(NativeDialogueRoot+112,5);
    row=0;
    while (row<(s32)(NativeDialogueRoot[17]>>1)) {
        u8 *row_state=NativeDialogueRoot;
        u32 *buffer_slot=(u32 *)(row_state+768);
        u32 row_width=row_state[26];
        u32 displacement=row*row_width;
        displacement <<= 6;
        ClearNativeDialogueRow((void *)(*buffer_slot+displacement),row_width<<1);
        row++;
    }
}
__asm__(".global NativeDialogueRoot\n.set NativeDialogueRoot,0x0200918c\n"
        ".global RetailCall_08014b84\n.thumb_set RetailCall_08014b84,0x08014b85\n"
        ".global RetailCall_0801843c\n.thumb_set RetailCall_0801843c,0x0801843d\n"
        ".global RetailCall_08018484\n.thumb_set RetailCall_08018484,0x08018485\n"
        ".global RetailCall_08013528\n.thumb_set RetailCall_08013528,0x08013529\n"
        ".global RetailCall_08013570\n.thumb_set RetailCall_08013570,0x08013571\n"
        ".global RetailCall_080137c0\n.thumb_set RetailCall_080137c0,0x080137c1\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n");
