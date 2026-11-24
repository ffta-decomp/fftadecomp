typedef unsigned char u8;
typedef unsigned int u32;
struct BattleTargetListCount {
    u8 preceding_fields[704];
    u8 count;
};
u32 ReadBattleTargetRowCount(const struct BattleTargetListCount *list)
    __asm__("CoreConsumer_000A8830");

/* Read the observed count byte once; it does not prove row capacity. */
u32 ReadBattleTargetRowCount(const struct BattleTargetListCount *list)
{
    return list->count;
}
