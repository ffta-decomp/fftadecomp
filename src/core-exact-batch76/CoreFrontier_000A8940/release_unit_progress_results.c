typedef unsigned char u8;
typedef unsigned int u32;
struct ProgressEntry;
struct UnitProgressResultView {
    u8 preceding_fields[60];
    struct ProgressEntry *entries;
};
typedef char ProgressEntriesOffset[((u32)&((struct UnitProgressResultView *)0)->entries == 60) ? 1 : -1];
extern void ReleaseProgressAllocation(void *allocation);
__asm__(".global ReleaseProgressAllocation\n.thumb_set ReleaseProgressAllocation,0x08022855\n");
void ReleaseUnitProgressResults(struct UnitProgressResultView *result)
    __asm__("CoreFrontier_000A8940");

/* The phase controller clears its result slot after both owned allocations. */
void ReleaseUnitProgressResults(struct UnitProgressResultView *result)
{
    ReleaseProgressAllocation(result->entries);
    ReleaseProgressAllocation(result);
}
