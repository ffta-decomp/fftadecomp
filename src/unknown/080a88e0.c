typedef unsigned char u8;
typedef unsigned int u32;
struct BattleActionListCount {
    u8 preceding_fields[9917];
    u8 count;
};
u32 ReadBattleActionTargetListCount(const struct BattleActionListCount *root)
    __asm__("CoreFrontier_000A88E0");

/* The consumer snapshots this byte before its list scan. */
u32 ReadBattleActionTargetListCount(const struct BattleActionListCount *root)
{
    return root->count;
}
