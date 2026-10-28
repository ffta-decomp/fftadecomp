typedef unsigned char u8;
extern unsigned char gBattleNodeWorkspace[];
extern void ApplyRecordToWorkspace(void *workspace, void *record, u8 record_state, u8 mode);
asm(".global gBattleNodeWorkspace\n.set gBattleNodeWorkspace,0x02010130\n.global ApplyRecordToWorkspace\n.thumb_set ApplyRecordToWorkspace,0x080bb5c5");
void ApplyBattleRecordToWorkspace(void *ignored_node, void *record, u8 record_state, u8 mode)
{
    ApplyRecordToWorkspace(gBattleNodeWorkspace, record, record_state, mode);
}
