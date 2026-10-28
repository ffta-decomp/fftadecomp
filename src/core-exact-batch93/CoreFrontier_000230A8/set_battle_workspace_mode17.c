typedef unsigned char u8;
typedef unsigned short u16;
struct BattleWorkspaceMode {
    u8 mode;
    u8 unknown_0001[149];
    u16 selector;
};
extern struct BattleWorkspaceMode gBattleWorkspaceMode;
asm(".global gBattleWorkspaceMode\n.set gBattleWorkspaceMode,0x0200f390");
void SetBattleWorkspaceMode17(void)
{
    gBattleWorkspaceMode.selector = 3;
    gBattleWorkspaceMode.mode = 17;
}
