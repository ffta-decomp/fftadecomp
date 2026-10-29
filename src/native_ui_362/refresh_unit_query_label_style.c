typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const u8 UnitMenuLabels[];
extern u8 *SceneDisplayRoot;
extern u32 QueryUnitMenuField(const void *,u32);
extern u16 *GetWindowCell(u32,u32,u32,u32);
extern void DrawWindowTileRun(u32,u16 *,u32,u32,u32);
extern void DrawUnitMenuLabel(u8 *,u8 *,const u8 *,u32,u32);
__asm__(".global UnitMenuLabels\n.set UnitMenuLabels,0x085668b0\n"
        ".global SceneDisplayRoot\n.set SceneDisplayRoot,0x03002818\n"
        ".global QueryUnitMenuField\n.thumb_set QueryUnitMenuField,0x080c8195\n"
        ".global GetWindowCell\n.thumb_set GetWindowCell,0x0808b8e5\n"
        ".global DrawWindowTileRun\n.thumb_set DrawWindowTileRun,0x0808b7c1\n"
        ".global DrawUnitMenuLabel\n.thumb_set DrawUnitMenuLabel,0x08015111");
void RefreshUnitQueryLabelStyle(u8 *incoming) __asm__("CoreScene34_00074FA4");
void RefreshUnitQueryLabelStyle(u8 *incoming)
{
    register u8 *unit __asm__("r4") = incoming;
    register const u8 *label_root __asm__("r0") = UnitMenuLabels;
    register const u8 *label __asm__("r5");
    register u32 flags __asm__("r1");
    register u32 mask __asm__("r0");
    __asm__("" : "+r"(unit), "+r"(label_root));
    label = *(const u8 **)(label_root + 212);
    __asm__("" : "+r"(label));
    flags = *(u16 *)(unit + 40);
    mask = 28;
    __asm__("" : "+r"(flags), "+r"(mask));
    if (!(mask & flags) && (unit[4] == 1 ||
        (u8)QueryUnitMenuField(unit,94) != 0 ||
        (u8)QueryUnitMenuField(unit,10) != 0 ||
        (u8)QueryUnitMenuField(unit,9) != 0 ||
        (u8)QueryUnitMenuField(unit,4) != 0 ||
        (u8)QueryUnitMenuField(unit,12) != 0 ||
        (u8)QueryUnitMenuField(unit,6) != 0)) {
        register u16 *cell __asm__("r0");
        register u32 tile_word __asm__("r2");
        register u32 stored_tile __asm__("r1");
        register u16 *row __asm__("r1");
        register u32 tile_id __asm__("r2");
        register u8 *font __asm__("r0");
        register u32 font_offset __asm__("r1");
        register u8 *tile_destination __asm__("r1");
        cell = GetWindowCell(4,1,0,9);
        tile_word = 0xD00C;
        __asm__("" : "+r"(tile_word));
        stored_tile = tile_word;
        __asm__("" : "+r"(stored_tile));
        *cell = (u16)stored_tile;
        row = GetWindowCell(4,1,1,8);
        __asm__("" : "+r"(row));
        tile_id = 489;
        __asm__("" : "+r"(tile_id));
        DrawWindowTileRun(4,row,tile_id,10,0xC000);
        font = SceneDisplayRoot;
        __asm__("" : "+r"(font));
        font_offset = 0x68C;
        __asm__("" : "+r"(font_offset));
        font += font_offset;
        __asm__("" : "+r"(font));
        tile_destination = (u8 *)0x0600BD20;
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
        cell = GetWindowCell(4,1,0,9);
        tile_word = 0xD00C;
        __asm__("" : "+r"(tile_word));
        stored_tile = tile_word;
        __asm__("" : "+r"(stored_tile));
        *cell = (u16)stored_tile;
        row = GetWindowCell(4,1,1,8);
        __asm__("" : "+r"(row));
        tile_id = 489;
        __asm__("" : "+r"(tile_id));
        DrawWindowTileRun(4,row,tile_id,10,0xC000);
        font = SceneDisplayRoot;
        __asm__("" : "+r"(font));
        font_offset = 0x68C;
        __asm__("" : "+r"(font_offset));
        font += font_offset;
        __asm__("" : "+r"(font));
        tile_destination = (u8 *)0x0600BD20;
        __asm__("" : "+r"(tile_destination));
        DrawUnitMenuLabel(font,tile_destination,label,1,1);
    }
}
