typedef unsigned char u8;
typedef signed short s16;
struct GridRecord { u8 packed_coordinates, direction; s16 value; struct GridRecord *next; };
void SetBattleRecordValue(struct GridRecord *record, int value)
{
    record->value = value;
}
