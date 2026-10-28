typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneLifecycleState {
    void *task_group;
    u32 unknown04;
    void *script_task;
    u8 phase;
};
struct ContentSaveView {
    u8 unknown0000[0x2192];
    u16 script_id;
    u8 unknown2194[8];
    u8 pending;
};
struct SceneSystemView { u8 unknown00; u8 script_active; };
extern struct ContentSaveView gSceneContentSave;
extern struct SceneLifecycleState *gSceneLifecycle;
extern struct SceneSystemView gSceneSystem;
extern u8 GetContentFlag21F(void);
extern void CopySaveHalfword2194To2192AndSetFlag21F(void);
extern void ClearContentFlag21F(void);
extern void CreateScenePool(void);
extern void InitializeSceneState(void);
extern void *CreateSceneScriptTask(u32);
extern void RunSceneTaskGroup(void *);
extern u32 PollSceneRecordHandle(void);
extern void ReleaseSceneRecordHandle(void);
extern void ClearSceneHandles(void);
extern void ShiftSceneContentQueue(void);
extern void ApplyQueuedSceneState(void);
extern void DestroySceneState(void);
extern void DestroyScenePool(void);
/* Symbol-only bindings to the original helpers and state objects. */
asm(".global GetContentFlag21F\n.thumb_set GetContentFlag21F,0x08009fbd\n.global CopySaveHalfword2194To2192AndSetFlag21F\n.thumb_set CopySaveHalfword2194To2192AndSetFlag21F,0x08009fd1\n.global ClearContentFlag21F\n.thumb_set ClearContentFlag21F,0x08009ff9\n.global CreateScenePool\n.thumb_set CreateScenePool,0x08121e49\n.global InitializeSceneState\n.thumb_set InitializeSceneState,0x08121e9d\n.global CreateSceneScriptTask\n.thumb_set CreateSceneScriptTask,0x0812237d\n.global RunSceneTaskGroup\n.thumb_set RunSceneTaskGroup,0x08005a25\n.global PollSceneRecordHandle\n.thumb_set PollSceneRecordHandle,0x08121c39\n.global ReleaseSceneRecordHandle\n.thumb_set ReleaseSceneRecordHandle,0x08121c19\n.global ClearSceneHandles\n.thumb_set ClearSceneHandles,0x08121f81\n.global ShiftSceneContentQueue\n.thumb_set ShiftSceneContentQueue,0x08121f39\n.global ApplyQueuedSceneState\n.thumb_set ApplyQueuedSceneState,0x08121a49\n.global DestroySceneState\n.thumb_set DestroySceneState,0x08121ef1\n.global DestroyScenePool\n.thumb_set DestroyScenePool,0x08121e75\n.global gSceneContentSave\n.set gSceneContentSave,0x02000000\n.global gSceneLifecycle\n.set gSceneLifecycle,0x020159cc\n.global gSceneSystem\n.set gSceneSystem,0x0200f390");


/* One lifecycle step per invocation; phase updates never redispatch here.
 * The callback's first argument is unused. Helpers can replace the global state. */
void AdvanceSceneScriptLifecycle(void *unused, u8 *step)
{
    void *script_task;
    switch (*step) {
    case 0:
        if (gSceneContentSave.pending != 0)
            CopySaveHalfword2194To2192AndSetFlag21F();
        goto ready;
    case 1:
        if ((u8)GetContentFlag21F() == 0)
            break;
        CreateScenePool();
        InitializeSceneState();
        script_task = CreateSceneScriptTask(gSceneContentSave.script_id);
        gSceneLifecycle->script_task = script_task;
        gSceneSystem.script_active = 1;
        *step = 2;
        break;
    case 2:
        if (gSceneLifecycle->phase != 0)
            *step = 3;
        RunSceneTaskGroup(gSceneLifecycle->task_group);
        PollSceneRecordHandle();
        break;
    case 3:
        RunSceneTaskGroup(gSceneLifecycle->task_group);
        ReleaseSceneRecordHandle();
        ClearSceneHandles();
        *step = 4;
        break;
    case 4: {
        register struct SceneSystemView *system asm("r0") = &gSceneSystem;
        u32 inactive;
        /* Keep the original initialized system base through its actual store. */
        asm("" : "+r"(system));
        inactive = 0;
        system->script_active = inactive;
        ClearContentFlag21F();
        ShiftSceneContentQueue();
        ApplyQueuedSceneState();
        DestroySceneState();
        DestroyScenePool();
    }
    ready:
        *step = 1;
        break;
    }
}
