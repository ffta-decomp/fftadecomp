typedef unsigned char u8;
typedef signed short s16;
struct GridRecord {
    u8 source_x : 4;
    u8 source_y : 4;
    u8 direction;
    s16 value;
    struct GridRecord *next;
};
/* Only the coordinate nibbles in byte zero are replaced. */
void SetBattleRecordSource(struct GridRecord *record, u8 x, u8 y)
{
    record->source_x = x;
    record->source_y = y;
}
