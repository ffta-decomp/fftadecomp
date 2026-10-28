#include "../../task_tree_core.h"

struct ActorParameterEvent {
    u32 unwritten_state;
    void *actor;
    u32 unwritten_words[3];
    u16 parameter;
    u16 selector;
    u32 unwritten_tail;
};
typedef char ActorParameterEventMustBe28Bytes[
    sizeof(struct ActorParameterEvent) == 28 ? 1 : -1];

extern TaskNode *CreateTaskInCurrentGroup(TaskCallback, u16, const u32 *, TaskNode *);
extern void ActorParameterCallback(TaskNode *, u16 *, void *);

TaskNode *RemainingBand43_000DF8E8(void *actor, u8 selector, u16 parameter,
                                  TaskNode *parent)
{
    struct ActorParameterEvent event;
    event.actor = actor;
    event.parameter = parameter;
    event.selector = selector;
    return CreateTaskInCurrentGroup(ActorParameterCallback, 20,
                                    (const u32 *)&event, parent);
}

asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global ActorParameterCallback\n.thumb_set ActorParameterCallback,0x080de61d\n");
