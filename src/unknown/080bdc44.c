typedef unsigned char u8;
typedef unsigned int u32;
/* Coordinates retain their incoming word carriers until the byte-offset shifts. */
void ClearBattleGridSlot(u32 *slots, u32 x, u32 y)
{
    u32 shifted_x = x << 24;
    u32 shifted_y = y << 24;
    u32 column_bytes = shifted_x >> 22;
    u32 row_bytes = shifted_y >> 18;
    u8 *destination = (u8 *)slots + (column_bytes + row_bytes);
    *(u32 *)destination = 0;
}
