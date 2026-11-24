typedef unsigned char u8;
typedef unsigned int u32;
/* Snapshot once: either output may alias the packed input byte. */
void GetBattleRecordSource(const u8 *record, u8 *source_x, u8 *source_y)
{
    u32 packed_coordinates = record[0];
    /* Keep the actual packed snapshot at its extraction boundary. */
    __asm__("" : "+r"(packed_coordinates));
    *source_x = (packed_coordinates << 28) >> 28;
    *source_y = (packed_coordinates << 24) >> 28;
}
