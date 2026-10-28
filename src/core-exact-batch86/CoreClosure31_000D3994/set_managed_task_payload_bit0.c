typedef unsigned short u16;
struct TaskNode;
struct TaskPayloadFlags { u16 unknown_at_00; u16 flags; };
extern void *GetTaskPayload(struct TaskNode *node);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload, 0x08005bfd");
void SetManagedTaskPayloadBitZero(void) __asm__("CoreClosure31_000D3994");
void SetManagedTaskPayloadBitZero(void)
{
    struct TaskPayloadFlags *payload = GetTaskPayload(*(struct TaskNode **)0x020159c0);
    payload->flags |= 1;
}
