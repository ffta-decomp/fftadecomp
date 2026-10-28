typedef unsigned char u8;
typedef unsigned int u32;
extern unsigned char gBattleNodeWorkspace[];
extern u32 AdvanceNodeWorkspace(void *workspace);
asm(".global gBattleNodeWorkspace\n.set gBattleNodeWorkspace,0x02010130\n.global AdvanceNodeWorkspace\n.thumb_set AdvanceNodeWorkspace,0x080bb7ad");
u8 PollBattleNodeWorkspace(void)
{
    return (u8)AdvanceNodeWorkspace(gBattleNodeWorkspace);
}
