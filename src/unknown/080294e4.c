typedef unsigned char u8;
struct BattleWorkspaceUnitView {
    u8 unknown_00[24];
    void *unit;
};
extern struct BattleWorkspaceUnitView *gBattleWorkspace;
asm(".global gBattleWorkspace\n.set gBattleWorkspace,0x0200f438");

void BindBattleWorkspaceUnit(void *unit)
{
    gBattleWorkspace->unit = unit;
}
