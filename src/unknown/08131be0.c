typedef unsigned char u8;
typedef unsigned int u32;
struct UnitTerrainView { u8 unknown_00_to_fc[253]; u8 terrain_adjustment; };
extern u32 ReadMapCellPrimaryByte(u8 x, u8 y);
extern u32 ReadBattleGridCellHighByte(u8 x, u8 y);
asm(".global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801cc19\n.global ReadBattleGridCellHighByte\n.thumb_set ReadBattleGridCellHighByte,0x0801cd09");
int ReadUnitAdjustedCellValue(struct UnitTerrainView *unit, u8 x, u8 y)
    asm("CoreContinuation_00131BE0");
/* The map result is a byte snapshot; the unit flag remains live across both queries. */
int ReadUnitAdjustedCellValue(struct UnitTerrainView *unit, u8 x, u8 y)
{
    u8 value;
    u8 cell_flags;
    value = ReadMapCellPrimaryByte(x, y);
    cell_flags = ReadBattleGridCellHighByte(x, y);
    if ((cell_flags & 2) != 0) {
        if (unit->terrain_adjustment == 2)
            goto adjusted_cell;
    }
    return value;
adjusted_cell:
    return value - 1;
}
