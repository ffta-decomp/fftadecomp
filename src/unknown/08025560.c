typedef unsigned char u8;
typedef signed short s16;
struct BattleWorkspaceSelectionView {
    u8 unknown_00[18];
    s16 selection_value;
};
extern struct BattleWorkspaceSelectionView *gBattleWorkspaceSelection;
asm(".global gBattleWorkspaceSelection\n.set gBattleWorkspaceSelection,0x0200f438");

int ClassifyBattleWorkspaceSelection(void)
{
    int value = gBattleWorkspaceSelection->selection_value;
    if (value < 0)
        return -1;
    return value > 85;
}
