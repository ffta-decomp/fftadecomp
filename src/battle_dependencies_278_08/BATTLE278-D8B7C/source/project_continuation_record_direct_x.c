typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef union CapturedGridPoint {
    struct { s16 x, y; } coordinate;
    u8 byte[4];
} CapturedGridPoint;
extern const s8 *GetContinuationRecord(const s8 *record);
extern u8 ReadMapCellPrimaryByte(u8 x, u8 y);
extern void ProjectMapPosition(s32 x, u32 height, s32 y,
                              u16 *out_x, u16 *out_height, u16 *out_y);
void RemainingBand43_000D8B7C(const s8 *record,
                            u16 *out_x, u16 *out_height, u16 *out_y)
{
    s16 coordinate[2];
    s16 *x = &coordinate[0];
    s16 *y = &coordinate[1];
    u8 height;
    record = GetContinuationRecord(record);
    *x = record[10];
    *y = record[11];
    height = ReadMapCellPrimaryByte(*(u8 *)&coordinate[0], (u8)*y);
    ProjectMapPosition(coordinate[0], height, *y, out_x, out_height, out_y);
}
asm(".global GetContinuationRecord\n.thumb_set GetContinuationRecord,0x080a880d\n"
    ".global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801cc19\n"
    ".global ProjectMapPosition\n.thumb_set ProjectMapPosition,0x0801ca79");
