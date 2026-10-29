typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const u8 UnitMenuLabels[];
extern u8 *SceneDisplayRoot;
extern u16 *GetWindowCell(u32,u32,u32,u32);
extern void DrawWindowTileRun(u32,u16 *,u32,u32,u32);
extern void DrawUnitMenuLabel(u8 *,u8 *,const u8 *,u32,u32);
__asm__(".global UnitMenuLabels\n.set UnitMenuLabels,0x085668b0\n"
        ".global SceneDisplayRoot\n.set SceneDisplayRoot,0x03002818\n"
        ".global GetWindowCell\n.thumb_set GetWindowCell,0x0808b8e5\n"
        ".global DrawWindowTileRun\n.thumb_set DrawWindowTileRun,0x0808b7c1\n"
        ".global DrawUnitMenuLabel\n.thumb_set DrawUnitMenuLabel,0x08015111");
void RefreshUnitByte6LabelStyle(u8 *unit) __asm__("CoreScene34_000750D8");
void RefreshUnitByte6LabelStyle(u8 *unit)
{
    register const u8 *label_root __asm__("r1") = UnitMenuLabels;
    register const u8 *label __asm__("r4");
    __asm__("" : "+r"(label_root) : "r"(unit));
    label = *(const u8 **)(label_root + 204);
    __asm__("" : "+r"(label) : "r"(unit));
    if (unit[6] <= 5) {
        register u16 *cell __asm__("r0");
        register u32 tile_word __asm__("r2");
        register u32 stored_tile __asm__("r1");
        register u16 *row __asm__("r1");
        register u32 tile_id __asm__("r2");
        register u8 *font __asm__("r0");
        register u32 font_offset __asm__("r1");
        register u8 *tile_destination __asm__("r1");
        cell = GetWindowCell(4,1,0,7);
        tile_word = 0xD00C;
        __asm__("" : "+r"(tile_word));
        stored_tile = tile_word;
        __asm__("" : "+r"(stored_tile));
        *cell = (u16)stored_tile;
        row = GetWindowCell(4,1,1,6);
        __asm__("" : "+r"(row));
        tile_id = 467;
        __asm__("" : "+r"(tile_id));
        DrawWindowTileRun(4,row,tile_id,10,0xC000);
        font = SceneDisplayRoot;
        __asm__("" : "+r"(font));
        font_offset = 0x68C;
        __asm__("" : "+r"(font_offset));
        font += font_offset;
        __asm__("" : "+r"(font));
        tile_destination = (u8 *)0x0600BA60;
        __asm__("" : "+r"(tile_destination));
        DrawUnitMenuLabel(font,tile_destination,label,0,1);
        return;
    } else {
        register u16 *cell __asm__("r0");
        register u32 tile_word __asm__("r2");
        register u32 stored_tile __asm__("r1");
        register u16 *row __asm__("r1");
        register u32 tile_id __asm__("r2");
        register u8 *font __asm__("r0");
        register u32 font_offset __asm__("r1");
        register u8 *tile_destination __asm__("r1");
        cell = GetWindowCell(4,1,0,7);
        tile_word = 0xD00C;
        __asm__("" : "+r"(tile_word));
        stored_tile = tile_word;
        __asm__("" : "+r"(stored_tile));
        *cell = (u16)stored_tile;
        row = GetWindowCell(4,1,1,6);
        __asm__("" : "+r"(row));
        tile_id = 467;
        __asm__("" : "+r"(tile_id));
        DrawWindowTileRun(4,row,tile_id,10,0xC000);
        font = SceneDisplayRoot;
        __asm__("" : "+r"(font));
        font_offset = 0x68C;
        __asm__("" : "+r"(font_offset));
        font += font_offset;
        __asm__("" : "+r"(font));
        tile_destination = (u8 *)0x0600BA60;
        __asm__("" : "+r"(tile_destination));
        DrawUnitMenuLabel(font,tile_destination,label,1,1);
    }
}
