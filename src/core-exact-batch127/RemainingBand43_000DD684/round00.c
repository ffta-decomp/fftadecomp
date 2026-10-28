typedef unsigned char u8;
typedef unsigned int u32;
struct BattleFlagRecord;
extern u32 TestExistingBattleRecordSelector(const struct BattleFlagRecord *, u8);
u32 ReadBattleRecordSelectorByte(const struct BattleFlagRecord *record, u8 selector)
{
    return (u8)TestExistingBattleRecordSelector(record, selector);
}
asm(".global TestExistingBattleRecordSelector\n.thumb_set TestExistingBattleRecordSelector,0x080a8859\n");
