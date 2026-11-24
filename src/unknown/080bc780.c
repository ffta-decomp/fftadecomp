typedef unsigned short u16;
extern unsigned char gBattleRecordWorkspace[];
extern void InitializeRecordWorkspace(void *workspace, void *record, u16 index);
asm(".global gBattleRecordWorkspace\n.set gBattleRecordWorkspace,0x02010060\n.global InitializeRecordWorkspace\n.thumb_set InitializeRecordWorkspace,0x080bab91");
void InitializeBattleRecordWorkspace(void *record, u16 index)
{
    InitializeRecordWorkspace(gBattleRecordWorkspace, record, index);
}
