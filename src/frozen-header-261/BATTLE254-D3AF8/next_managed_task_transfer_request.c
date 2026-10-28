#include "../../task_tree_core.h"

extern void *GetTaskPayload(TaskNode *node);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload, 0x08005bfd");

/* A task-owned ring supplies 28-byte requests to the existing transfer service. */
void *NextManagedTaskTransferRequest(void)
    __asm__("CoreClosure31_000D3AF8");
void *NextManagedTaskTransferRequest(void)
{
    u8 *payload = GetTaskPayload(*(TaskNode **)0x020159c0);
    u8 *request_cursor = payload + 0x914;

    ++*request_cursor;
    if (*request_cursor > 15)
        *request_cursor = 0;
    return payload + (0x918 + *request_cursor * 28);
}
