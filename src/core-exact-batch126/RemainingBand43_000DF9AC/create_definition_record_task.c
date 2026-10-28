#include "../../../src/task_tree_core.h"

struct DefinitionRecordStartup {
    u16 selector;
    u16 flags;
    u32 parameter;
    void *record;
};
typedef char DefinitionRecordStartupSize[
    sizeof(struct DefinitionRecordStartup)==12?1:-1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionRecordCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionRecordTask(u8 selector, u32 parameter, void *record,
                                    u16 flags, u32 delay, TaskNode *parent)
{
    u32 event[7];
    struct DefinitionRecordStartup startup;
    startup.selector=selector;
    startup.parameter=parameter;
    startup.record=record;
    startup.flags=flags;
    /* The callback consumes these fields; other event bytes stay unspecified. */
    ((u16 *)event)[10]=delay;
    event[1]=(u32)&startup;
    return CreateTaskInCurrentGroup(DefinitionRecordCallback,28,event,parent);
}
asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global DefinitionRecordCallback\n.thumb_set DefinitionRecordCallback,0x080def91\n");
