typedef unsigned char u8;
typedef unsigned int u32;
/* Partial ordinary-RAM view of the option saved by the battle action controller. */
struct BattleActionOptionView { u8 prefix[0x54d5]; u8 action_option; };
typedef char OptionOffset[(u32)&((struct BattleActionOptionView *)0)->action_option == 0x54d5 ? 1 : -1];
extern struct BattleActionOptionView gBattleActionOptionView;
__asm__(".global gBattleActionOptionView\n.set gBattleActionOptionView,0x020101f8");
void StoreBattleActionOption(u32 option)
{
    gBattleActionOptionView.action_option = option;
}
