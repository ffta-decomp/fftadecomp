typedef unsigned int u32;
struct BattleActionRecord;
extern struct BattleActionRecord gCurrentBattleActionRecord;
extern void (*const ClearBattleActionMemory)(void *destination, u32 bytes);
__asm__(".global gCurrentBattleActionRecord\n.set gCurrentBattleActionRecord,0x020156c4\n.global ClearBattleActionMemory\n.set ClearBattleActionMemory,0x0836d4b8\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
void ClearCurrentBattleActionRecord(void)
{
    ClearBattleActionMemory(&gCurrentBattleActionRecord, 24);
}
