typedef unsigned char u8;

void WriteBattleRecordCoordinates(u8 *record, int first, int second)
{
    /* These requested fields differ from the readback pair at 265/266. */
    record[267] = (u8)first;
    record[268] = (u8)second;
}
