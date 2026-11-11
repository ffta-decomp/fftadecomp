typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
struct RecordGridPosition {
    u8 unknown_00[10];
    s8 column;
    s8 row;
};
extern const struct RecordGridPosition *GetRecordPositionReference(const void *record);
extern u8 ReadMapCellPrimaryByte(u8 column, u8 row);
extern void ProjectMapCellCoordinates(s16 column, s16 height, s16 row,
                                     s16 *out_x, s16 *out_height, s16 *out_y);
extern void ProjectBattlePoint(s16 x, s16 height, s16 y,
                              u16 *out_x, u16 *out_y, u16 *out_depth);
__asm__(".thumb_set GetRecordPositionReference,0x080a880d");
__asm__(".thumb_set ReadMapCellPrimaryByte,0x0801cc19");
__asm__(".thumb_set ProjectMapCellCoordinates,0x0801ca79");
__asm__(".thumb_set ProjectBattlePoint,0x0801c919");
void ProjectRecordMapPosition(const void *record, u16 *out_x,
                              u16 *out_y, u16 *out_depth)
    __asm__("RemainingBand43_000D8BD8");
void ProjectRecordMapPosition(const void *record, u16 *out_x,
                              u16 *out_y, u16 *out_depth)
{
    u8 height;
    s16 world_position[3];
    s16 grid_position[2];
    s16 *world_height = &world_position[1];
    s16 *world_y = &world_position[2];
    s16 *column = &grid_position[0];
    s16 *row = &grid_position[1];
    const struct RecordGridPosition *position;
    /* Preserve the four real addresses formed before the first retail call.
     * These input-only operands are initialized and emit no instructions. */
    __asm__("" : : "r"(world_height), "r"(world_y), "r"(column), "r"(row));
    position = GetRecordPositionReference(record);
    *column = position->column;
    *row = position->row;
    height = ReadMapCellPrimaryByte((u8)*column, (u8)*row);
    ProjectMapCellCoordinates(*column, height, *row,
                              &world_position[0], world_height, world_y);
    ProjectBattlePoint(world_position[0], *world_height, *world_y,
                       out_x, out_y, out_depth);
}
