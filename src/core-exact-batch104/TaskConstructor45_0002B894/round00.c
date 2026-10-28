typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct UnitTaskCommandPayload { u8 unknown_00[19]; u8 parameter; };
extern struct UnitTaskCommandPayload *GetQueuedUnitTaskPayload(struct TaskNode *);
extern void SetQueuedUnitTaskState(struct TaskNode *, u16);

void QueueUnitTaskTransitionCommand(struct TaskNode *task, u8 action, u8 parameter)
{
    struct UnitTaskCommandPayload *payload;

    payload = GetQueuedUnitTaskPayload(task);
    if (action != 0)
        SetQueuedUnitTaskState(task, 265);
    else {
        payload->parameter = parameter;
        SetQueuedUnitTaskState(task, 264);
    }
}
asm(".thumb_set GetQueuedUnitTaskPayload, 0x08005bfd\n"
    ".thumb_set SetQueuedUnitTaskState, 0x08005ba9\n");
