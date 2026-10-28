typedef unsigned char u8;
typedef unsigned int u32;
struct TaskNode;
extern u32 IsTaskStateTwo(const struct TaskNode *node);
__asm__(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo, 0x08005bb1");

u32 PollTaskStateByte(const struct TaskNode *node)
    __asm__("SceneActionDependency_000D3878");
u32 PollTaskStateByte(const struct TaskNode *node)
{
    return (u8)IsTaskStateTwo(node);
}
