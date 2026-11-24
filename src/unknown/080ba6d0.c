extern void ClearBattleSceneWorkspace(void);
extern void ReleaseGlobalPoolAllocation(void *record);
__asm__(".global ClearBattleSceneWorkspace\n.thumb_set ClearBattleSceneWorkspace, 0x0802b9b5\n.global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation, 0x08022855");

void DestroyBattleSceneRecord(void *record)
{
    ClearBattleSceneWorkspace();
    ReleaseGlobalPoolAllocation(record);
}
