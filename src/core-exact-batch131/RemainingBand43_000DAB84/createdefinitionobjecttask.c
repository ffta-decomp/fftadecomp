#include "../../../src/task_tree_core.h"

typedef signed short s16;

extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionObjectCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionObjectTask(u8 mode,u8 variant,u8 flags,TaskNode *parent)
{
    u16 event[14];
    event[10] = mode;
    event[11] = variant;
    event[12] = flags;
    return CreateTaskInCurrentGroup(DefinitionObjectCallback,8,(const u32 *)event,parent);
}

asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
    ".global DefinitionObjectCallback\n.thumb_set DefinitionObjectCallback,0x80d9c59\n");
