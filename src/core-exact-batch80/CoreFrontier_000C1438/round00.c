typedef unsigned char u8;
typedef unsigned int u32;
struct BattleSelection;
extern struct BattleSelection gCurrentBattleSelection;
extern u32 AdvanceBattleSelection(struct BattleSelection *selection);
__asm__(".global gCurrentBattleSelection\n.set gCurrentBattleSelection,0x020101f8\n.global AdvanceBattleSelection\n.thumb_set AdvanceBattleSelection,0x080c045d");
u32 PollCurrentBattleSelection(void)
{
    return (u8)AdvanceBattleSelection(&gCurrentBattleSelection);
}
