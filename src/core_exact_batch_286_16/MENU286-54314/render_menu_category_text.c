typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MenuTileRows {
    u8 unknown_prefix[21];
    u8 width;
    u8 last_row;
    u8 unknown_23[5];
    u16 first_tile;
};
struct TileLayer {
    u8 unknown_prefix[16];
    u8 *tiles;
};
extern struct TileLayer MenuTileLayer;
extern const u8 MenuContentArchive[];
extern void LoadItemIconGraphic(u16 *output, u16 entry_index);
extern u32 QuerySelectionIndex(struct MenuTileRows *, int row);
extern int SignedModulo(int value, int divisor);
extern void ClearTileUnits(u8 *output, u16 count);
extern void BiosCpuSet(const void *source, void *destination, u32 control);
extern void ProcessText(void *context, u8 *destination, const u8 *text,
                        u8 glyph, u32 mode);
void RenderMenuCategoryText(struct MenuTileRows *, void *, u16, u16, u32)
    __asm__("CoreClosure31_00054314");
void RenderMenuCategoryText(struct MenuTileRows *rows, void *text_context,
                           u16 requested_row, u16 category_input, u32 glyph_input)
{
    u16 icon_pixels[64];
    u32 row_index;
    u32 width;
    u32 tile_offset;
    u8 *row_tiles;
    u8 *text_tiles;
    register u32 category_id __asm__("r5") = category_input;
    register u32 text_id __asm__("r0");
    u32 text_offset;
    const u8 *text;
    const u8 *content_archive;
    struct TileLayer *tile_layer;
    u8 glyph;

    /* This original category snapshot remains live across every helper. */
    __asm__("" : : "r"(category_id));
    glyph = (u8)glyph_input;
    if (category_id > 85)
        LoadItemIconGraphic(icon_pixels, 394);
    else
        LoadItemIconGraphic(icon_pixels, 393);
    row_index = (u16)QuerySelectionIndex(rows, (s8)requested_row);
    row_index = SignedModulo(row_index, rows->last_row + 1);
    width = rows->width;
    tile_offset = (row_index * width) << 17;
    tile_layer = &MenuTileLayer;
    tile_offset >>= 16;
    tile_offset += rows->first_tile;
    row_tiles = tile_layer->tiles + (tile_offset << 5);
    text_tiles = row_tiles + 128;
    ClearTileUnits(text_tiles, (u16)((width - 2) * 2));
    BiosCpuSet(icon_pixels, row_tiles, 64);
    text_id = category_id;
    /* Retain the working copy separately from the category predicate. */
    __asm__("" : "+r"(text_id) : "r"(category_id));
    if (category_id > 85)
        text_id = category_id - 85;
    text_offset = text_id << 16;
    content_archive = MenuContentArchive;
    text_offset >>= 14;
    text_offset += 0x9c4;
    text = *(const u8 *const *)(content_archive + text_offset);
    ProcessText(text_context, text_tiles, text, glyph, 1);
}
__asm__(".global MenuTileLayer\n.set MenuTileLayer,0x030008B0\n"
        ".global MenuContentArchive\n.set MenuContentArchive,0x08526680\n"
        ".global LoadItemIconGraphic\n.thumb_set LoadItemIconGraphic,0x080CB981\n"
        ".global QuerySelectionIndex\n.thumb_set QuerySelectionIndex,0x08017B69\n"
        ".global SignedModulo\n.thumb_set SignedModulo,0x08142951\n"
        ".global ClearTileUnits\n.thumb_set ClearTileUnits,0x08013A89\n"
        ".global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186D\n"
        ".global ProcessText\n.thumb_set ProcessText,0x08015111\n");
