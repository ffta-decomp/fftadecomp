extern void ReleaseNullableManagedWorkBuffer(void **buffer_cell);
extern void ReleasePublishedBattleRuntime(void);
extern void FinishBattleSceneTasks(void);
__asm__(".global ReleaseNullableManagedWorkBuffer\n.thumb_set ReleaseNullableManagedWorkBuffer,0x080247fd\n.global ReleasePublishedBattleRuntime\n.thumb_set ReleasePublishedBattleRuntime,0x08096cb9\n.global FinishBattleSceneTasks\n.thumb_set FinishBattleSceneTasks,0x08022dd1");
void ReleaseBattleSceneAndFinishTasks(void) __asm__("CoreRegion_00125560");
void ReleaseBattleSceneAndFinishTasks(void)
{
    ReleaseNullableManagedWorkBuffer((void **)0x0200f3ac);
    ReleasePublishedBattleRuntime();
    FinishBattleSceneTasks();
}
