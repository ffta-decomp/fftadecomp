typedef unsigned char u8;
typedef unsigned int u32;
struct BattleChoice;
extern u32 AdvanceBattleChoiceMode(struct BattleChoice *choice);
__asm__(".global AdvanceBattleChoiceMode\n.thumb_set AdvanceBattleChoiceMode,0x080c5321");
u32 PollBattleChoiceMode(struct BattleChoice *choice)
{
    return (u8)AdvanceBattleChoiceMode(choice);
}
