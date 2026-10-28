typedef unsigned char u8;

void ReadBattleRecordCoordinates(const u8 *record, u8 *first_out, u8 *second_out)
{
    /* The first output may alias the second input byte. */
    *first_out = record[265];
    *second_out = record[266];
}
