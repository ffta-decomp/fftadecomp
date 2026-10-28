typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeShopIconSurface { u8 unknown00[12]; u8 stride; u8 unknown13[7]; u16 *tilemap; };
extern u32 ReadNativeShopIconPalette(u32);
extern void LoadNativeShopIconPixels(u8 *,u32);
extern void CopyNativeShopIconPixels(const void *,void *,u32);
extern void FillNativeShopIconTiles(u16 *,u16,u8,u16);
__asm__(".global ReadNativeShopIconPalette\n.thumb_set ReadNativeShopIconPalette,0x080CBA15\n"
        ".global LoadNativeShopIconPixels\n.thumb_set LoadNativeShopIconPixels,0x080CB9E1\n"
        ".global CopyNativeShopIconPixels\n.thumb_set CopyNativeShopIconPixels,0x0814186D\n"
        ".global FillNativeShopIconTiles\n.thumb_set FillNativeShopIconTiles,0x0802ACA1\n");
void DrawNativeShopResourceIcon(struct NativeShopIconSurface *,void *,u32,u8,u8,u8)
    __asm__("SceneTaskDependency_000701BC");
void DrawNativeShopResourceIcon(struct NativeShopIconSurface *surface,void *destination,
                                u32 raw_graphics_id,u8 palette_flag,u8 x,u8 y)
{
    u8 pixels[256];
    u8 palette;
    u16 tile_index;
    u16 *second_row;
    u32 graphics_id = (u8)raw_graphics_id;
    palette = ReadNativeShopIconPalette(graphics_id);
    if (!palette_flag)
        palette -= 6;
    LoadNativeShopIconPixels(pixels,graphics_id);
    CopyNativeShopIconPixels(pixels,destination,128);
    tile_index = ((u32)destination - 0x06008000U) >> 5;
    FillNativeShopIconTiles(surface->tilemap + (y * surface->stride + x),tile_index,palette,4);
    second_row = surface->tilemap + (surface->stride * (y + 1) + x);
    tile_index += 4;
    FillNativeShopIconTiles(second_row,tile_index,palette,4);
}
