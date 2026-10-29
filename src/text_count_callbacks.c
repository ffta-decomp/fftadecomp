typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 WriteNumericPrefix(u8 *output, u8 value);
extern u16 WriteUnsignedNumberText(u8 *output, u32 value);
extern u8 CountStatusRecordsWithBits0And1(void);
extern u16 CountSelectedRecordFlags(void);
extern u16 GetSelectedFlagMilestoneCount(void);

/* The owner of these EWRAM counters has not been established. */
#define INDEXED_COUNTER_BYTES ((volatile const u8 *)0x0200216a)
#define STORED_COUNTER_BYTE (*(volatile const u8 *)0x020021b5)

#if defined(INDEXED_COUNTER)
u32 WriteIndexedCounterAsNumber(u8 *output, u32 selector)
{
    volatile const u8 *selected_count = INDEXED_COUNTER_BYTES + (u8)selector * 2;
    if (*selected_count <= 9)
        output += (u16)WriteNumericPrefix(output, 8);
    WriteUnsignedNumberText(output, *selected_count);
    return 0;
}
#elif defined(STORED_COUNTER)
u32 WriteStoredCounterByteAsNumber(u8 *output)
{
    if (STORED_COUNTER_BYTE <= 9)
        output += (u16)WriteNumericPrefix(output, 8);
    WriteUnsignedNumberText(output, STORED_COUNTER_BYTE);
    return 0;
}
#elif defined(STATUS_RECORD_COUNT)
u32 WriteStatusRecordCountAsNumber(u8 *output)
{
    u8 count = CountStatusRecordsWithBits0And1();
    if (count != 30) {
        if (count <= 9)
            output += (u16)WriteNumericPrefix(output, 8);
        WriteUnsignedNumberText(output, count);
    }
    return 0;
}
#elif defined(DISTINCT_SELECTED_COUNT)
u32 WriteDistinctSelectedFlagCountAsNumber(u8 *output)
{
    u16 count = CountSelectedRecordFlags();
    u16 milestone_count = GetSelectedFlagMilestoneCount();
    if (count != milestone_count) {
        if (count <= 99)
            output += (u16)WriteNumericPrefix(output, 8);
        /* The retail path emits a second prefix when the count is one digit. */
        if (count <= 9)
            output += (u16)WriteNumericPrefix(output, 8);
        WriteUnsignedNumberText(output, count);
    }
    return 0;
}
#else
#error Select one text count callback
#endif
