typedef unsigned char u8;
typedef signed short s16;
struct GridRecord { u8 packed_coordinates, direction; s16 value; struct GridRecord *next; };
void SetBattleRecordDirection(struct GridRecord *record, unsigned int direction)
{
    record->direction = direction;
}
