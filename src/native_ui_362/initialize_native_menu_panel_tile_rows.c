typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *NativeLayerCell(u32,u32,u32,u32);
extern void WriteNativeTilePairs(u32,u16 *,u16,u16,u16);
extern void WriteNativeTileSequence(u32,u16 *,u16,u16,u16);
__asm__(".global NativeLayerCell\n.thumb_set NativeLayerCell,0x0808b8e5\n"
        ".global WriteNativeTilePairs\n.thumb_set WriteNativeTilePairs,0x0808b7c1\n"
        ".global WriteNativeTileSequence\n.thumb_set WriteNativeTileSequence,0x0808b80d");
void InitializeNativeMenuPanelTileRows(void) __asm__("CoreGlobal36_0008C9C4");
void InitializeNativeMenuPanelTileRows(void)
{
    u16 *destination;
    destination = NativeLayerCell(6,1,1,1);
    WriteNativeTilePairs(6,destination,0x30d,11,0xb000);
    destination = NativeLayerCell(6,1,1,5);
    WriteNativeTilePairs(6,destination,0x323,11,0xb000);
    destination = NativeLayerCell(6,1,1,9);
    WriteNativeTilePairs(6,destination,0x339,11,0xb000);
    destination = NativeLayerCell(6,1,1,13);
    WriteNativeTilePairs(6,destination,0x34f,11,0xb000);
    destination = NativeLayerCell(6,1,1,7);
    WriteNativeTileSequence(6,destination,0x365,4,0xc000);
    destination = NativeLayerCell(6,1,1,11);
    WriteNativeTileSequence(6,destination,0x36d,4,0xc000);
    destination = NativeLayerCell(6,1,1,15);
    WriteNativeTileSequence(6,destination,0x375,4,0xc000);
    destination = NativeLayerCell(6,1,7,3);
    WriteNativeTilePairs(6,destination,0x37d,5,0xe000);
}
