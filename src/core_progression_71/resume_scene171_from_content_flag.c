/* Method-local interface declarations from the frozen build. */
#ifndef SCENE171_FLOW_INTERFACES_H
#define SCENE171_FLOW_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct SceneRootView { u32 fields0[2]; void *task; } SceneRootView;
typedef struct TaskPayloadView { u32 fields0[2]; u32 field8; } TaskPayloadView;
typedef struct FlowSupervisorView { u8 fields0[148]; u16 flags; } FlowSupervisorView;
extern SceneRootView *gScene171Root;
extern FlowSupervisorView gScene171Supervisor;
__asm__(".global gScene171Root\n.set gScene171Root, 0x020159cc\n.global gScene171Supervisor\n.set gScene171Supervisor, 0x0200f390");
extern u8 GetContentFlag21F(void);
extern void CopySaveHalfword2194To2192AndSetFlag21F(void);
extern void *CreateSceneScriptTask_0812237C(u32 script_id);
extern TaskPayloadView *GetSceneTaskPayload(void *task);
extern void InitializeContentSelection(u16 content_id);
__asm__(".global GetSceneTaskPayload\n.thumb_set GetSceneTaskPayload, 0x08005bfd\n.global InitializeContentSelection\n.thumb_set InitializeContentSelection, 0x08009afd");
__asm__(".global GetContentFlag21F\n.thumb_set GetContentFlag21F, 0x8009fbd\n.global CopySaveHalfword2194To2192AndSetFlag21F\n.thumb_set CopySaveHalfword2194To2192AndSetFlag21F, 0x8009fd1\n.global CreateSceneScriptTask_0812237C\n.thumb_set CreateSceneScriptTask_0812237C, 0x812237d");
#endif


void ResumeScene171FromContentFlag(void)
{
    if (GetContentFlag21F()) {
        if (gScene171Root != 0 && gScene171Root->task != 0)
            GetSceneTaskPayload(gScene171Root->task)->field8 = 0;
        CreateSceneScriptTask_0812237C(171);
    } else {
        InitializeContentSelection(171);
        CopySaveHalfword2194To2192AndSetFlag21F();
    }
    gScene171Supervisor.flags |= 1024;
}
