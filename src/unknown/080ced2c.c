typedef unsigned short u16;

/* Four observed callers compare this with CountSelectedRecordFlags;
 * a fifth stores it in a halfword field. The ID table has 300 entries,
 * although an optional flag can add one more to the count. */
u16 GetSelectedFlagMilestoneCount(void)
{
    return 300;
}
