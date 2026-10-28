typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern void *RetailCall_08022840(u32 size);
extern void RetailCall_08022854(void *allocation);
extern u32 CollectSourceAbilityRecords(void *buffer, void *source_unit);
extern u32 FindIncompleteUnitAbility(void *unit, void *buffer, s32 count, s32 *ordinal);
__asm__(".global CollectSourceAbilityRecords\n.thumb_set CollectSourceAbilityRecords,0x08133cc9");
__asm__(".global FindIncompleteUnitAbility\n.thumb_set FindIncompleteUnitAbility,0x08132e2d");


u8 HasIncompleteAbilityFromSourceUnit(void *unit, void *source_unit)
{
    void *records;
    u16 count;
    u16 incomplete;
    s32 ordinal;

    records = RetailCall_08022840(1024);
    count = CollectSourceAbilityRecords(records, source_unit);
    incomplete = FindIncompleteUnitAbility(unit, records, count, &ordinal);
    RetailCall_08022854(records);
    if (incomplete != 0)
        return 1;
    return 0;
}
