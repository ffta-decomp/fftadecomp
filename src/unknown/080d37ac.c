typedef unsigned char u8;
struct TaskNode;
extern void *GetTaskPayload(struct TaskNode *node);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload, 0x08005bfd");

/* Only payload byte zero is cleared; its wider interpretation is unresolved. */
void ClearManagedTaskPayloadByte(void)
    __asm__("SceneActionDependency_000D37AC");
void ClearManagedTaskPayloadByte(void)
{
    u8 *payload = GetTaskPayload(*(struct TaskNode **)0x020159c0);
    payload[0] = 0;
}
