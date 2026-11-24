struct BattleActionRegistry;
struct SceneTaskRecord;
extern void ProcessSceneTaskRecord(struct SceneTaskRecord *record);
extern struct BattleActionRegistry *GetBattleActionRegistry(void);
extern void UpdateBattleActionSlots(struct BattleActionRegistry *registry);
extern void UpdateEnabledBattleTree(void);
extern void ProcessScheduledSceneObjects(void);
__asm__(".global ProcessSceneTaskRecord\n.thumb_set ProcessSceneTaskRecord,0x08024861\n.global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n.global UpdateBattleActionSlots\n.thumb_set UpdateBattleActionSlots,0x0809a48d\n.global UpdateEnabledBattleTree\n.thumb_set UpdateEnabledBattleTree,0x080a9421\n.global ProcessScheduledSceneObjects\n.thumb_set ProcessScheduledSceneObjects,0x0808f639");
/* The second registry query is a distinct live read in the original task. */
void UpdateRegisteredBattleSceneTask(void)
{
    ProcessSceneTaskRecord((struct SceneTaskRecord *)0x0200f3ac);
    if (GetBattleActionRegistry() != 0)
        UpdateBattleActionSlots(GetBattleActionRegistry());
    UpdateEnabledBattleTree();
    ProcessScheduledSceneObjects();
}
