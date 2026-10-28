/* Source-derived two-record battle eligibility exclusion. */
typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRecordView { void *unit; u8 reserved04[124]; u8 *owner; };
typedef char record_owner_offset_check[((u32)&(((struct BattleRecordView *)0)->owner)==128)?1:-1];
u32 IsReservedBattleUnitRecord(const struct BattleRecordView *record) asm("CoreFrontier_0009AA10");
u32 IsReservedBattleUnitRecord(const struct BattleRecordView *record)
{
    const u8 *current;
    const void *unit;
    int index;
    current = record->owner;
    unit = record->unit;
    index = 0;
    current += 64;
    for (; index <= 1; index++) {
        if (current == unit)
            return 1;
        current += 264;
    }
    return 0;
}
