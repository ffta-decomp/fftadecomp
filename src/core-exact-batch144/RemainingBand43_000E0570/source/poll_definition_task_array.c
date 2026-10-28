typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
extern u32 IsTaskNodeFinished(struct TaskNode *);
extern void ReleaseTaskNode(struct TaskNode *);

u32 PollDefinitionTaskArray(struct TaskNode **tasks, u16 count)
{
    u32 complete = 1;
    u16 index;
    for (index = 0; index < count; ++index) {
        /* The native sequence forms the byte offset before the base address. */
        u32 slot_offset = index * sizeof(*tasks);
        struct TaskNode **slot = (struct TaskNode **)(slot_offset + (u32)tasks);
        if (*slot != 0) {
            if (IsTaskNodeFinished(*slot) != 0) {
                /* The status call may change this slot; release its live value. */
                ReleaseTaskNode(*slot);
                *slot = 0;
            } else
                complete = 0;
        }
    }
    return complete;
}

asm(".global IsTaskNodeFinished\n.thumb_set IsTaskNodeFinished,0x08005BB1\n"
    ".global ReleaseTaskNode\n.thumb_set ReleaseTaskNode,0x08005B59\n");
