#include "../../../../src/task_tree_core.h"

TaskNode *Remaining38_00005B6C(TaskCallback callback, u16 payload_size,
                              const u32 *event_template, TaskNode *parent)
{
    TaskNode *node;
    node = CreateTaskNode_08005954(CURRENT_GROUP, callback, payload_size,
                                  event_template, parent);
    node->phase = CURRENT_GROUP->phase ^ 1U;
    return node;
}
asm(".global CreateTaskNode_08005954\n.thumb_set CreateTaskNode_08005954,0x08005955");
