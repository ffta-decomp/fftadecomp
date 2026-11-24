extern void RunCurrentUnitTasks(void);
__asm__(".global RunCurrentUnitTasks\n.thumb_set RunCurrentUnitTasks,0x0802b6f1");
void AdvanceUnitTaskSceneFrame(void) __asm__("SceneRegisteredRoot_000231E8");
void AdvanceUnitTaskSceneFrame(void)
{
    RunCurrentUnitTasks();
}
