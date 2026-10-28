typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *NativeLayerCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void WriteNativeTilePairs(u32,u16 *,u16,u16,u16) asm("RetailCall_0808b7c0");
void ComposeSaveRestoreSlotTileRows(u32 layer,u16 tile) asm("Remaining38_001385CC");
void ComposeSaveRestoreSlotTileRows(u32 layer,u16 tile)
{
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,1,3),tile,11,0xC000);
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,1,5),(u16)(tile+22),3,0xC000);
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,4,5),(u16)(tile+28),3,0xC000);
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,7,5),(u16)(tile+34),2,0xC000);
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,9,5),(u16)(tile+38),3,0xC000);
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,1,8),(u16)(tile+44),11,0xC000);
    WriteNativeTilePairs(layer,NativeLayerCell(layer,1,8,11),(u16)(tile+66),3,0xC000);
}
__asm__(".global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n.global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5");
