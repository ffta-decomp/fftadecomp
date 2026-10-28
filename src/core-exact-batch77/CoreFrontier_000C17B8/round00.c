struct BattleActionRecord;
extern struct BattleActionRecord gCurrentBattleActionRecord;
extern void InitializeBattleActionSubmission(void *record);
__asm__(".global gCurrentBattleActionRecord\n.set gCurrentBattleActionRecord,0x020156c4\n.global InitializeBattleActionSubmission\n.thumb_set InitializeBattleActionSubmission,0x080c7611");
void SubmitCurrentBattleActionRecord(void)
{
    InitializeBattleActionSubmission(&gCurrentBattleActionRecord);
}
