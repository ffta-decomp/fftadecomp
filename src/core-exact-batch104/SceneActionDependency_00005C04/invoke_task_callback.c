typedef unsigned char u8;
typedef unsigned int u32;
struct TaskNode;
typedef u32 (*TaskCallback)(struct TaskNode *, void *, u8 *);
struct TaskNode { TaskCallback callback; u8 unknown4[20]; };
__asm__(".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
u32 InvokeTaskCallback(struct TaskNode *node, void *context) __asm__("SceneActionDependency_00005C04");
u32 InvokeTaskCallback(struct TaskNode *node, void *context)
{
    return node->callback(node, context, (u8 *)node + 24);
}
