typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

/* The row index is signed16; each row contains two independent byte values. */
void WriteBattleRowTrack(u8 *buffer, s16 index, u32 first, u32 second)
{
    s32 offset = index * 2;
    u8 *first_element = buffer + offset;
    *first_element = first;
    buffer += 1;
    buffer += offset;
    *buffer = second;
}
