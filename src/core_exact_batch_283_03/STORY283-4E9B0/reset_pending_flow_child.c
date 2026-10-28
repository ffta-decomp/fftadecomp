#include "../../task_tree_core.h"
struct PendingChildPrefix { u16 unknown00, unknown02, request_flags; signed short counter; };
extern struct PendingChildPrefix *GetTaskPayload(TaskNode *task);
void ResetPendingFlowChild(TaskNode *task)
{
 struct PendingChildPrefix *child=GetTaskPayload(task);
 child->counter=0;
 child->request_flags=64;
}
asm(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd");
