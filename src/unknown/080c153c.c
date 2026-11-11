typedef unsigned char u8;
typedef unsigned int u32;
/* Raw option remains a full byte; boolean and nibble use occur in consumers. */
struct BattleRawOptionView { u8 prefix[0x54bb]; u8 option; };
typedef char RawOptionOffset[(u32)&((struct BattleRawOptionView *)0)->option == 0x54bb ? 1 : -1];
extern struct BattleRawOptionView gBattleRawOptionView;
__asm__(".global gBattleRawOptionView\n.set gBattleRawOptionView,0x020101f8");
u32 ReadBattleRawOption(void)
{
    return gBattleRawOptionView.option;
}
