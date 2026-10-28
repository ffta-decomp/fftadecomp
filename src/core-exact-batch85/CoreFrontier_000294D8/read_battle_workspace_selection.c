typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleWorkspaceSelectionIndexView {
    u8 unknown_00[16];
    u16 selection_index;
};
extern struct BattleWorkspaceSelectionIndexView *gBattleWorkspaceSelection;
asm(".global gBattleWorkspaceSelection\n.set gBattleWorkspaceSelection,0x0200f438");

u32 ReadBattleWorkspaceSelection(void)
{
    return gBattleWorkspaceSelection->selection_index;
}
