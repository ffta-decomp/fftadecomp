typedef unsigned char u8;
typedef unsigned int u32;
/* Partial ordinary-RAM view; the high nibble drives the record advance loop. */
struct BattleActionProgressView { u8 prefix[0x54d4]; u8 progression; };
typedef char ProgressOffset[(u32)&((struct BattleActionProgressView *)0)->progression == 0x54d4 ? 1 : -1];
extern struct BattleActionProgressView gBattleActionProgressView;
__asm__(".global gBattleActionProgressView\n.set gBattleActionProgressView,0x020101f8");
u32 ReadBattleActionAdvanceCount(void)
{
    return gBattleActionProgressView.progression >> 4;
}
