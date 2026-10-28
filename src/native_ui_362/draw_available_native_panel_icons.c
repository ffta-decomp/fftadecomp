typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Full channel and two full tile/attribute words; LOW8 coordinates/dimensions. */
extern void FillNativeWindowTileBlock(u32,u32,u32,u8,u8,u8,u8);
__asm__(".global FillNativeWindowTileBlock\n.thumb_set FillNativeWindowTileBlock,0x08089249");
void DrawAvailableNativePanelIcons(u32 selected_index, u16 *availability)
    __asm__("Source52_0008BE0C");
void DrawAvailableNativePanelIcons(u32 selected_index, u16 *availability)
{
    u16 column = 1;
    u32 selected_attributes = 0xf000;
    u32 ordinary_attributes = 0x9000;
    selected_index += 1;
    if (availability[0] != 0) {
        u32 attributes = ordinary_attributes;
        if (selected_index == 1)
            attributes = selected_attributes;
        FillNativeWindowTileBlock(5,230,attributes,1,0,2,2);
        column = 3;
    }
    if (availability[1] != 0) {
        u32 attributes = ordinary_attributes;
        if (selected_index == 2)
            attributes = selected_attributes;
        FillNativeWindowTileBlock(5,234,attributes,(u8)column,0,2,2);
        column = (u16)(column + 2);
    }
    if (availability[2] != 0) {
        u32 attributes = ordinary_attributes;
        if (selected_index == 3)
            attributes = selected_attributes;
        FillNativeWindowTileBlock(5,238,attributes,(u8)column,0,2,2);
        column = (u16)(column + 2);
    }
    if (availability[3] != 0) {
        u32 attributes = ordinary_attributes;
        if (selected_index == 4)
            attributes = selected_attributes;
        FillNativeWindowTileBlock(5,242,attributes,(u8)column,0,2,2);
        column = (u16)(column + 2);
    }
    if (availability[4] != 0) {
        u32 attributes = ordinary_attributes;
        if (selected_index == 5)
            attributes = selected_attributes;
        FillNativeWindowTileBlock(5,246,attributes,(u8)column,0,2,2);
        column = (u16)(column + 2);
    }
    if (availability[5] != 0) {
        u32 attributes = ordinary_attributes;
        if (selected_index == 6)
            attributes = selected_attributes;
        FillNativeWindowTileBlock(5,250,attributes,(u8)column,0,2,2);
    }
}
