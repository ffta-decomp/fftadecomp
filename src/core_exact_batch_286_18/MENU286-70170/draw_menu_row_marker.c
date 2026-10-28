typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct PanelTileOrigin { u8 unknown_prefix[19]; u8 column; u8 row; };
struct MenuTileMap { u8 unknown_prefix[12]; u8 stride; u8 unknown_13[7]; u16 *tiles; };
extern void StoreTileSequence(u16 *destination, u16 first_tile,
                              u8 palette, u16 count);
void DrawMenuRowMarker(struct PanelTileOrigin *, struct MenuTileMap *, u8)
    __asm__("CoreRegion_00070170");
void DrawMenuRowMarker(struct PanelTileOrigin *panel, struct MenuTileMap *map,
                       u8 relative_row)
{
    u32 byte_offset;
    byte_offset = (u32)(u16)(((relative_row * 2 + panel->row) * map->stride)
                             + panel->column) * 2;
    StoreTileSequence((u16 *)((u8 *)map->tiles + byte_offset), 329, 13, 2);
    /* The first stores may alias the map: reload its base and stride. */
    StoreTileSequence((u16 *)((u8 *)map->tiles + byte_offset
                              + map->stride * 2), 331, 13, 2);
}
__asm__(".global StoreTileSequence\n.thumb_set StoreTileSequence,0x0802ACA1\n");
