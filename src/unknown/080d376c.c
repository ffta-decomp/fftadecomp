typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct TaskGroup;
typedef void (*TaskCallback)(struct TaskNode *, u16 *, void *);
typedef void (*ClearTaskEventBytes)(void *, u32);
extern struct TaskNode *CreateTaskNode(struct TaskGroup *, TaskCallback, u32,
                                     const u32 *, struct TaskNode *);
extern void ManagedTaskCallback(struct TaskNode *, u16 *, void *);
__asm__(".global CreateTaskNode\n.thumb_set CreateTaskNode, 0x08005955\n"
        ".global ManagedTaskCallback\n.thumb_set ManagedTaskCallback, 0x080d3209\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

void CreateManagedTask(void) __asm__("SceneActionDependency_000D376C");
void CreateManagedTask(void)
{
    u32 event[7];
    (*(ClearTaskEventBytes *)0x0836d4b8)(event, 28);
    /* The constructor retains its real linking, callback and state effects. */
    *(struct TaskNode **)0x020159c0 =
        CreateTaskNode(*(struct TaskGroup **)0x0200f430,
                       ManagedTaskCallback, 0xb28, event, 0);
}
