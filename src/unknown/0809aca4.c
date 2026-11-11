typedef unsigned int u32;
struct FlagRecord { unsigned char unknown[48]; u32 flags; };
struct FlagUpdate { u32 clear_mask; u32 set_mask; };
u32 UpdateVisitedRecordFlags(struct FlagRecord *record,const struct FlagUpdate *update) __asm__("IsolatedCore57_0009ACA4");
u32 UpdateVisitedRecordFlags(struct FlagRecord *record,const struct FlagUpdate *update)
{
    u32 clear_mask = update->clear_mask;
    u32 flags = record->flags;
    flags &= ~clear_mask;
    flags |= update->set_mask;
    record->flags = flags;
    return 1;
}
