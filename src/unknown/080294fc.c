typedef unsigned char u8;
struct TurnSelectionWorkspace {
    u8 unknown_0000[24];
    void *selected_unit;
};
extern struct TurnSelectionWorkspace *gTurnSelectionWorkspace;
asm(".global gTurnSelectionWorkspace\n.set gTurnSelectionWorkspace,0x0200f438");
void *GetSelectedBattleUnit(void)
{
    return gTurnSelectionWorkspace->selected_unit;
}
