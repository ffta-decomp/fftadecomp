typedef unsigned char u8;
typedef unsigned int u32;

/* Prefix views only: neither declaration claims the full allocation size. */
struct ProgressSnapshot {
    u8 prefix[100];
    u8 inner_counter;
    u8 outer_counter;
};
struct ProgressRuntime {
    u32 field_00;
    const struct ProgressSnapshot *snapshot;
};
struct SavedProgressCounters {
    u8 prefix[0x2fba];
    u8 outer_counter;
    u8 inner_counter;
};
extern struct ProgressRuntime *gProgressContext;
extern struct SavedProgressCounters gSavedProgress;

u32 SavedProgressCounterSnapshotChanged(void)
    __asm__("CoreRegion_00035FC4");
u32 SavedProgressCounterSnapshotChanged(void)
{
    const struct ProgressSnapshot *snapshot = gProgressContext->snapshot;
    const u8 *inner_snapshot = &snapshot->inner_counter;
    struct SavedProgressCounters *saved = &gSavedProgress;

    if (*inner_snapshot != saved->inner_counter)
        return 1;
    if (snapshot->outer_counter == saved->outer_counter)
        return 0;
    return 1;
}
__asm__(".global gProgressContext\n.set gProgressContext,0x03002810\n"
        ".global gSavedProgress\n.set gSavedProgress,0x02000000\n");
