typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeShopLanguageRow { const u8 *graphics; u32 unknown04; };
/* Only the low two bits of this existing save byte select the resource row. */
struct NativeShopSaveLanguage { u8 unknown00[0x2FC2]; u8 language:2; u8 unknown_language_flags:6; };
extern struct NativeShopSaveLanguage gNativeShopSaveLanguage;
extern u32 DecodeNativeShopBytes(void *,const void *);
extern u32 DecodeNativeShopA7(const void *,void *,u16,u16);
extern void CopyNativeShopScreen(const void *,void *,u32);
extern u32 LoadNativeShopDescriptorTiles(void *,u16,u32);
extern void TransformNativeShopPalette(const u16 *,u16 *,u8,u8);
__asm__(".global gNativeShopSaveLanguage\n.set gNativeShopSaveLanguage,0x02000000\n"
        ".global DecodeNativeShopBytes\n.thumb_set DecodeNativeShopBytes,0x0800543D\n"
        ".global DecodeNativeShopA7\n.thumb_set DecodeNativeShopA7,0x08005319\n"
        ".global CopyNativeShopScreen\n.thumb_set CopyNativeShopScreen,0x0814186D\n"
        ".global LoadNativeShopDescriptorTiles\n.thumb_set LoadNativeShopDescriptorTiles,0x08018525\n"
        ".global TransformNativeShopPalette\n.thumb_set TransformNativeShopPalette,0x08070261\n");
void LoadNativeShopScreenResources(void) __asm__("SceneTaskDependency_0006E960");
void LoadNativeShopScreenResources(void)
{
    u8 *scratch = (u8 *)0x02003CB0;
    const u8 *shared_asset;
    const u8 *palette_source;
    const u8 *last_palette_source;
    u8 *palette_shadow;
    u32 language;
    /* The initialized native scratch carrier remains the base of later additions.
       Keep its runtime identity instead of folding base+offset into absolute pointers. */
    __asm__("" : "+r" (scratch));
    DecodeNativeShopBytes(scratch,(const void *)0x083B4214);
    CopyNativeShopScreen(scratch + 0xD40,(void *)0x06009800,1248);
    CopyNativeShopScreen(scratch + 0xA40,(void *)0x0600A1C0,384);
    CopyNativeShopScreen(scratch + 0x1880,(void *)0x0600A4C0,128);
    CopyNativeShopScreen(scratch + 0x1980,(void *)0x0600A5C0,112);
    CopyNativeShopScreen(scratch + 0x1A60,(void *)0x0600A6A0,128);
    CopyNativeShopScreen(scratch + 0x1B60,(void *)0x0600A7A0,128);
    CopyNativeShopScreen(scratch + 0x1700,(void *)0x0600A8E0,32);
    DecodeNativeShopA7((const void *)0x083A9CA4,scratch,0,0);
    CopyNativeShopScreen(scratch + 0x800,(void *)0x0600A8A0,32);
    {
        register u32 source_offset __asm__("r1") = 0x240;
        /* Native offset producer dies at the following pointer addition. */
        __asm__("" : "+r" (source_offset));
        CopyNativeShopScreen(scratch + source_offset,(void *)0x06015800,320);
    }
    DecodeNativeShopA7((const void *)0x083D3D64,scratch,0,0);
    {
        register u32 source_offset __asm__("r2") = 0x1280;
        /* Native offset producer dies at the following pointer addition. */
        __asm__("" : "+r" (source_offset));
        CopyNativeShopScreen(scratch + source_offset,(void *)0x0600A920,64);
    }
    shared_asset = (const u8 *)0x083AEEA4;
    DecodeNativeShopBytes(scratch,shared_asset);
    {
        register u32 source_offset __asm__("r1") = 0x220;
        /* Native offset producer dies at the following pointer addition. */
        __asm__("" : "+r" (source_offset));
        CopyNativeShopScreen(scratch + source_offset,(void *)0x06015A80,96);
    }
    LoadNativeShopDescriptorTiles(scratch,832,5);
    LoadNativeShopDescriptorTiles(scratch,838,6);
    LoadNativeShopDescriptorTiles(scratch,844,2);
    DecodeNativeShopBytes(scratch,shared_asset);
    {
        register u32 source_offset __asm__("r2") = 0x9A0;
        /* Native retained scratch pointer advances using this short-lived offset. */
        __asm__("" : "+r" (source_offset));
        scratch += source_offset;
    }
    CopyNativeShopScreen(scratch,(void *)0x0600E680,32);
    {
        register const struct NativeShopLanguageRow *language_rows __asm__("r1") = (const struct NativeShopLanguageRow *)0x08393E78;
        /* Native retains the initialized table base in R1 during selector extraction. */
        __asm__("" : "+r" (language_rows));
        language = gNativeShopSaveLanguage.language;
        palette_source = language_rows[language].graphics + 288;
    }
    palette_shadow = (u8 *)0x03003980;
    CopyNativeShopScreen(palette_source,palette_shadow,16);
    TransformNativeShopPalette((const u16 *)(palette_shadow + 128),(u16 *)(palette_shadow - 64),64,40);
    last_palette_source = palette_shadow + 160;
    palette_shadow -= 32;
    TransformNativeShopPalette((const u16 *)last_palette_source,(u16 *)palette_shadow,64,40);
}
