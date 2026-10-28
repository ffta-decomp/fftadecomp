/* Keep the real action-record processor and every delegated effect. */
extern void ProcessBattleActionRecord(void *record);
__asm__(".global ProcessBattleActionRecord\n.thumb_set ProcessBattleActionRecord,0x080a40a1\n");

void DispatchBattleActionRecord(void *record)
{
    ProcessBattleActionRecord(record);
}
