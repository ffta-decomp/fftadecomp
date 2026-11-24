typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
/* The old counter is signed for indexing; only its stored increment wraps. */
void *AllocateBattleGridRecord(void *grid)
{
    u16 *counter = (u16 *)((u8 *)grid + 17664);
    u16 previous = *counter;
    *counter = previous + 1;
    return (u8 *)grid + (1280 + (s16)previous * 8);
}
