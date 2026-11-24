typedef unsigned char u8;
typedef signed short s16;
struct GridRecord { u8 packed_coordinates, direction; s16 value; struct GridRecord *next; };
unsigned int GetBattleRecordDirection(const struct GridRecord *record)
{
    return record->direction;
}
