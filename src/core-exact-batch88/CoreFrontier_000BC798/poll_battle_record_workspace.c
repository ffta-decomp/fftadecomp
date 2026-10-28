typedef unsigned char u8;
typedef unsigned int u32;
extern unsigned char gBattleRecordWorkspace[];
extern u32 AdvanceRecordWorkspace(void *workspace);
asm(".global gBattleRecordWorkspace\n.set gBattleRecordWorkspace,0x02010060\n.global AdvanceRecordWorkspace\n.thumb_set AdvanceRecordWorkspace,0x080ba8e5");
u8 PollBattleRecordWorkspace(void)
{
    return (u8)AdvanceRecordWorkspace(gBattleRecordWorkspace);
}
