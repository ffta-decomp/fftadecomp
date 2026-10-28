typedef unsigned char u8;
typedef signed short s16;
struct GridRecord { u8 packed_coordinates; u8 direction; s16 value; struct GridRecord *next; };
int GetBattleRecordValue(const struct GridRecord *record)
{
    return record->value;
}
