typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct MenuTileRows {
    u8 unknown_prefix[21];
    u8 width;
    u8 last_row;
    u8 unknown_23[5];
    u16 first_tile;
};
struct TileLayer { u8 unknown_prefix[16]; u8 *tiles; };
extern struct TileLayer MenuTileLayer;
extern u8 *MenuWorkspace;
extern u32 QuerySelectionIndex(struct MenuTileRows *, int relative_row);
extern int SignedModulo(int value, int divisor);
extern void ClearTileUnits(u8 *output, u16 count);
extern u32 ProcessText(void *context, u8 *destination, const u8 *text,
                       u8 glyph, u32 mode);
extern void DrawValue(void *context, u8 *destination, u32 value,
                      u8 width, u8 mode);
extern void DrawTileRowPair(struct MenuTileRows *, u16 map_offset,
                           u16 first_tile, u8 stride, u8 count,
                           u16 palette, u8 paired_tiles);
void RenderMenuValueRow(struct MenuTileRows *, u8, const u8 *, u32, u16, u8)
    __asm__("SceneTaskDependency_0006E848");
void RenderMenuValueRow(struct MenuTileRows *rows, u8 icon_kind,
                       const u8 *label, u32 value, u16 relative_row, u8 palette)
{
    u32 selection_index;
    u32 width;
    u16 first_tile;
    u8 *row_tiles;
    u16 map_offset;
    u16 icon_tile;
    void *live_text_context;
    int doubled_row;

    selection_index = (u16)QuerySelectionIndex(rows, (s8)relative_row);
    selection_index = SignedModulo(selection_index, rows->last_row + 1);
    {
        register u32 tile_width __asm__("r1") = rows->width;
        /* Original first-phase width remains in R1 through the clear count. */
        __asm__("" : : "r"(tile_width));
        first_tile = (u16)(selection_index * tile_width * 2 + rows->first_tile);
        row_tiles = MenuTileLayer.tiles + ((u32)first_tile << 5);
        ClearTileUnits(row_tiles, tile_width * 2);
    }
    ProcessText(MenuWorkspace + 0x39f4, row_tiles + 128, label, 0, 1);
    /* The label renderer may replace the workspace or row configuration. */
    live_text_context = MenuWorkspace + 0x39f4;
    row_tiles += ((int)rows->width - 5) * 64;
    DrawValue(live_text_context, row_tiles, value, 5, 0);
    width = rows->width;
    doubled_row = (int)((u32)relative_row << 16) >> 15;
    map_offset = (u16)(width * doubled_row);
    icon_tile = (u16)(icon_kind * 4 + 270);
    DrawTileRowPair(rows, map_offset, icon_tile, width, 2, palette, 0);
    map_offset = (u16)(map_offset + 2);
    first_tile = (u16)(first_tile + 4);
    {
        u32 inner_width = rows->width;
        DrawTileRowPair(rows, map_offset, first_tile, inner_width,
                        (u8)(inner_width - 2), 0, 1);
    }
}
__asm__(".global MenuTileLayer\n.set MenuTileLayer,0x030008B0\n"
        ".global MenuWorkspace\n.set MenuWorkspace,0x0200F428\n"
        ".global QuerySelectionIndex\n.thumb_set QuerySelectionIndex,0x08017B69\n"
        ".global SignedModulo\n.thumb_set SignedModulo,0x08142951\n"
        ".global ClearTileUnits\n.thumb_set ClearTileUnits,0x08013A89\n"
        ".global ProcessText\n.thumb_set ProcessText,0x08015111\n"
        ".global DrawValue\n.thumb_set DrawValue,0x0802979D\n"
        ".global DrawTileRowPair\n.thumb_set DrawTileRowPair,0x0802AB65\n");
