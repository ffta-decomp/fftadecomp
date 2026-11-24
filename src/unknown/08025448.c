typedef unsigned char u8;
typedef unsigned int u32;
struct TurnSelectionWorkspace {
    u8 unknown_0000[3];
    u8 active;
};
extern struct TurnSelectionWorkspace *gTurnSelectionWorkspace;
extern void BeginSelectionMode(u8 mode,u32 argument);
asm(".global gTurnSelectionWorkspace\n.set gTurnSelectionWorkspace,0x0200f438\n.global BeginSelectionMode\n.thumb_set BeginSelectionMode,0x080253b1");
void ActivateBattleSelectionMode(u8 mode)
{
    gTurnSelectionWorkspace->active = 1;
    BeginSelectionMode(mode,0);
}
