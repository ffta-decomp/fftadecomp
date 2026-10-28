#include "task_tree_core.h"

extern u8 *gNativeMenuRoot;
extern void NativeMenuPayloadTaskCallback(TaskNode *node, u16 *event,
                                           void *payload);

TaskNode *CreateNativeMenuPayloadTask(u32 payload)
{
    /* The creator copies all seven words; retail initializes only word one. */
    u32 event[7];

    event[1] = payload;
    return CreateTaskNode_08005954(*(TaskGroup **)gNativeMenuRoot,
                                  NativeMenuPayloadTaskCallback,
                                  0x1098, event, (TaskNode *)0);
}

asm(".set gNativeMenuRoot, 0x0200F44C\n"
    ".thumb_set NativeMenuPayloadTaskCallback, 0x08060E31\n"
    ".thumb_set CreateTaskNode_08005954, 0x08005955\n");
