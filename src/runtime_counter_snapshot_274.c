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

void CaptureSavedProgressCounterSnapshot(void)
    __asm__("CoreRegion_00035F8C");
void CaptureSavedProgressCounterSnapshot(void)
{
    const struct ProgressSnapshot *snapshot = gProgressContext->snapshot;
    struct SavedProgressCounters *saved = &gSavedProgress;
    u8 inner_counter = saved->inner_counter;

    ((struct ProgressSnapshot *)snapshot)->inner_counter = inner_counter;
    /* Original reload follows the first byte store; do not cache the old root. */
    ((struct ProgressSnapshot *)gProgressContext->snapshot)->outer_counter =
        saved->outer_counter;
}
__asm__(".global gProgressContext\n.set gProgressContext,0x03002810\n"
        ".global gSavedProgress\n.set gSavedProgress,0x02000000\n");
