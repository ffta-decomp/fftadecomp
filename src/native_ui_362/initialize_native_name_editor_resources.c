typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 NameEditorScratch[] asm("0x02003cb0");
extern u8 NameEditorSurface[] asm("0x03000990");
extern u16 NameEditorPaletteBank[] asm("0x03003b00");
extern const u8 NameEditorPrimaryTiles[] asm("0x083c5024");
extern const u8 NameEditorSecondaryTiles[] asm("0x083c52a8");
extern const u16 NameEditorPageMap[] asm("0x083c4d38");
extern void DecodeNameEditorResource(void *,const void *) asm("RetailCall_0800543c");
extern void CopyNameEditorMap(void *,u32,u32,const void *,u32,u32) asm("RetailCall_0802b4a8");
extern const void *GetNameEditorPrimaryPalette(u32) asm("RetailCall_080cbabc");
extern const void *GetNameEditorSecondaryPalette(u32) asm("RetailCall_080cba84");
extern void BiosCopyNameEditorData(const void *,void *,u32) asm("RetailCall_0814186c");
asm(".global RetailCall_0800543c\n.thumb_set RetailCall_0800543c,0x0800543d\n.global RetailCall_0802b4a8\n.thumb_set RetailCall_0802b4a8,0x0802b4a9\n.global RetailCall_080cbabc\n.thumb_set RetailCall_080cbabc,0x080cbabd\n.global RetailCall_080cba84\n.thumb_set RetailCall_080cba84,0x080cba85\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n");
void InitializeNativeNameEditorResources(void) asm("CoreRegion_0012B258");
void InitializeNativeNameEditorResources(void)
{
    u8 saved_surface_byte;
    const void *palette;
    u16 *palette_destination;
    DecodeNameEditorResource(NameEditorScratch,NameEditorPrimaryTiles);
    BiosCopyNameEditorData(NameEditorScratch,(void *)0x06015800,1408);
    DecodeNameEditorResource(NameEditorScratch,NameEditorSecondaryTiles);
    BiosCopyNameEditorData(NameEditorScratch,(void *)0x06009c00,832);
    saved_surface_byte=NameEditorSurface[12];
    NameEditorSurface[12]=32;
    CopyNameEditorMap(NameEditorSurface,1,1,NameEditorPageMap,22,17);
    NameEditorSurface[12]=saved_surface_byte;
    palette=GetNameEditorPrimaryPalette(24);
    palette_destination=NameEditorPaletteBank;
    BiosCopyNameEditorData(palette,palette_destination,16);
    palette=GetNameEditorSecondaryPalette(11);
    palette_destination+=64;
    BiosCopyNameEditorData(palette,palette_destination,16);
}
