typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct NativeRestoreMenuSelection {
    u8 opaque00[261];
    u8 current_row;
    u8 previous_row;
} NativeRestoreMenuSelection;
extern u16 *GetRestoreMenuCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void FillRestoreMenuColumnPairs(u32,u16 *,u32,u32,u32) asm("RetailCall_0808b7c0");
void RefreshNativeRestoreSelectionRows(NativeRestoreMenuSelection *) asm("Remaining38_00138E80");
void RefreshNativeRestoreSelectionRows(NativeRestoreMenuSelection *selection)
{
    u8 *row = &selection->previous_row;
    register u16 *destination asm("r1");
    if (*row != 255) {
        destination = GetRestoreMenuCell(2,1,1,(u32)*row * 2 + 2);
        asm("" : "+r"(destination));
        FillRestoreMenuColumnPairs(2,destination,(u32)*row * 22 + 427,11,0xC000);
    }
    row = &selection->current_row;
    destination = GetRestoreMenuCell(2,1,1,(u32)*row * 2 + 2);
    asm("" : "+r"(destination));
    FillRestoreMenuColumnPairs(2,destination,(u32)*row * 22 + 427,11,0xB000);
}
__asm__(".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n"
        ".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n");
