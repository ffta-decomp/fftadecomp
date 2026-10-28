typedef unsigned char u8;
typedef unsigned short u16;
struct BattleWorkspaceActivation { u16 active; u8 unknown02[2]; u8 mode; };
extern struct BattleWorkspaceActivation *BattleWorkspaceActivationCell;
extern void BindWorkspaceUnit_080294E4(void *);
void BeginBattleWorkspaceUnit(void *unit)
{
    BindWorkspaceUnit_080294E4(unit);
    BattleWorkspaceActivationCell->mode = 10;
    BattleWorkspaceActivationCell->active = 1;
}
asm(".set BattleWorkspaceActivationCell,0x0200f438\n");
asm(".thumb_set BindWorkspaceUnit_080294E4,0x080294e5\n");
