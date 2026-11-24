typedef unsigned char u8;
typedef unsigned short u16;

/* This helper counts occupied entries in an observed 20-halfword queue. */
#define PENDING_HALFWORD_QUEUE ((const u16 *)0x02001f3c)

u8 CountPendingHalfwordRecords(void)
{
    u8 index = 0;
    u8 count = 0;

    while (index < 20) {
        if (PENDING_HALFWORD_QUEUE[index] != 0)
            count++;
        index++;
    }
    return count;
}
