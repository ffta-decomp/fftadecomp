typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct TaskPayloadFlags {
    u16 unknown_at_00;
    u16 flags;
};
extern void *GetTaskPayload(struct TaskNode *node);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload, 0x08005bfd");

/* The broader meaning of payload flag bit zero remains unresolved. */
u32 HasManagedTaskPayloadBitZero(void)
    __asm__("SceneActionDependency_000D3970");
u32 HasManagedTaskPayloadBitZero(void)
{
    struct TaskPayloadFlags *payload = GetTaskPayload(*(struct TaskNode **)0x020159c0);
    if ((payload->flags & 1) != 0)
        return 1;
    return 0;
}
