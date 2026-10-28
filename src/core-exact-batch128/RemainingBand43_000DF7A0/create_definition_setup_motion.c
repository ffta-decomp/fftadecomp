#include "../../../src/task_tree_core.h"

struct DefinitionSetupStartup {
    void *record;
    u32 mode:8;
    u32 axis:8;
    u32 flags:8;
    u32 :8;
};
typedef char DefinitionSetupStartupSize[sizeof(struct DefinitionSetupStartup)==8?1:-1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionSetupCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionSetupMotion(void *,u8,u8,u8,u32,TaskNode *)
    asm("RemainingBand43_000DF7A0");
TaskNode *CreateDefinitionSetupMotion(void *record,u8 mode,u8 axis,u8 flags,
                                     u32 delay,TaskNode *parent)
{
    u32 event[7];
    struct DefinitionSetupStartup startup;
    startup.record=record;
    startup.mode=mode;
    startup.axis=axis;
    startup.flags=flags;
    /* The callback consumes only the three initialized packed byte fields. */
    event[1]=(u32)&startup;
    ((u16 *)event)[10]=delay;
    return CreateTaskInCurrentGroup(DefinitionSetupCallback,16,event,parent);
}
asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global DefinitionSetupCallback\n.thumb_set DefinitionSetupCallback,0x080debad\n");
