typedef unsigned char u8;
typedef unsigned int u32;
/* Partial ordinary-RAM view used by the battle action seed snapshot. */
struct BattleActionSeedView { u8 prefix[0x54e0]; u32 seed; };
typedef char SeedOffset[(u32)&((struct BattleActionSeedView *)0)->seed == 0x54e0 ? 1 : -1];
extern struct BattleActionSeedView gBattleActionSeedView;
__asm__(".global gBattleActionSeedView\n.set gBattleActionSeedView,0x020101f8");
void StoreBattleActionSeedSnapshot(u32 seed)
{
    gBattleActionSeedView.seed = seed;
}
