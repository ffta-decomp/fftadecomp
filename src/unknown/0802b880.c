typedef unsigned char u8;
typedef unsigned int u32;
struct TaskNode;
struct UnitTaskPayloadView { u8 unknown0[18]; u8 state; };
extern struct UnitTaskPayloadView *GetTaskPayload(struct TaskNode *);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd");
u32 ReadUnitTaskState(struct TaskNode *task)
{
    u32 state;
    if (task != 0)
        state = GetTaskPayload(task)->state;
    else
        state = 3;
    return state;
}
