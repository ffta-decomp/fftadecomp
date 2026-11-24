typedef unsigned char u8;
typedef unsigned int u32;
/* The all-ones rejected-cell sentinel has no list head. */
u32 ReadBattleGridHead(const u32 *slots, u32 x, u32 y)
{
    u32 shifted_x = x << 24;
    u32 shifted_y = y << 24;
    u32 column_bytes = shifted_x >> 22;
    u32 row_bytes = shifted_y >> 18;
    const u8 *cell = (const u8 *)slots + (column_bytes + row_bytes);
    u32 head = *(const u32 *)cell;
    if (head == ~0u) return 0;
    return head;
}
