typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Partial ordinary-RAM view; action meaning is limited to the C09 consumer. */
struct BattleRecordedActionView { u8 prefix[0x54d8]; u16 action; };
typedef char ActionOffset[(u32)&((struct BattleRecordedActionView *)0)->action == 0x54d8 ? 1 : -1];
extern struct BattleRecordedActionView gBattleRecordedActionView;
__asm__(".global gBattleRecordedActionView\n.set gBattleRecordedActionView,0x020101f8");
u32 ReadBattleRecordedAction(void)
{
    return gBattleRecordedActionView.action;
}
