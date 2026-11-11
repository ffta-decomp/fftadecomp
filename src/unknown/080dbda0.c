typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
struct NestedPositionView {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
};
extern void ProjectBattlePoint(s16 x, s16 height, s16 y,
                              u16 *out_x, u16 *out_y, u16 *out_depth);
__asm__(".thumb_set ProjectBattlePoint,0x0801c919");
void ProjectNestedRecordPosition(const struct NestedPositionView *record,
                                u16 *out_x, u16 *out_y, u16 *out_depth)
    __asm__("RemainingBand43_000DBDA0");
void ProjectNestedRecordPosition(const struct NestedPositionView *record,
                                u16 *out_x, u16 *out_y, u16 *out_depth)
{
    /* Capture all inputs before a projection output can alias the record. */
    int x = record->x;
    int height = record->height;
    int y = record->y;
    ProjectBattlePoint(x, height, y, out_x, out_y, out_depth);
}
