typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void PrepareSelectionContents(u8*);
extern void DrawSelectionAtOffset(u8*,u32);
asm(".global PrepareSelectionContents\n.thumb_set PrepareSelectionContents,0x08040d3d\n.global DrawSelectionAtOffset\n.thumb_set DrawSelectionAtOffset,0x08040da5\n");

void RefreshSelectionAtCurrentOffset(u32 unused_owner,u8 *object) __asm__("CoreRegion_00040E14");
void RefreshSelectionAtCurrentOffset(u32 unused_owner,u8 *object)
{
    PrepareSelectionContents(object);
    DrawSelectionAtOffset(object,(u16)(*(u16*)(object+26)<<1));
}
