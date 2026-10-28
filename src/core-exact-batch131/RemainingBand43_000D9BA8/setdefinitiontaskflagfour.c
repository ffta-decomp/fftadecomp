#include "../../../src/task_tree_core.h"

typedef signed short s16;

extern void *GetTaskPayload(TaskNode *);
extern void SetDefinitionObjectFlagFour(void *,u8);
void SetDefinitionTaskFlagFour(TaskNode *task,u8 enabled)
{
    void *payload = GetTaskPayload(task);
    SetDefinitionObjectFlagFour(((void **)payload)[1],enabled);
}

asm(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x8005bfd\n"
    ".global SetDefinitionObjectFlagFour\n.thumb_set SetDefinitionObjectFlagFour,0x800c629\n");
