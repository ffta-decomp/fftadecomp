typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
struct TaskNode;
struct SelectionInput { u8 unknown_00[9]; u8 flags; };
struct SelectionState {
    u8 unknown_00[11];
    s8 pending_command;
    u8 controller[116];
    struct SelectionInput input;
};
extern u32 PollManagedSelectionInput(void *);
extern void UpdateManagedSelectionState(struct SelectionState *, u8);
extern struct TaskNode *GetManagedUnitTaskHandle(u32);
extern void QueueManagedUnitTaskTransition(struct TaskNode *, u8, u8);

u32 DeliverManagedSelectionPendingCommand(struct SelectionState *state)
{
    struct SelectionInput *input;
    struct TaskNode *task;
    u32 completed;

    input = (struct SelectionInput *)((u8 *)state + 128);
    completed = (u8)PollManagedSelectionInput(state->controller);
    if (completed != 0) {
        UpdateManagedSelectionState(state, 1);
        return 1;
    }
    if ((input->flags & 16) != 0 && state->pending_command != 0) {
        task = GetManagedUnitTaskHandle(1);
        QueueManagedUnitTaskTransition(task, 0, (u8)state->pending_command);
        state->pending_command = completed;
    }
    return 0;
}
asm(".thumb_set PollManagedSelectionInput, 0x08017181\n"
    ".thumb_set UpdateManagedSelectionState, 0x08025dc9\n"
    ".thumb_set GetManagedUnitTaskHandle, 0x0802d72d\n"
    ".thumb_set QueueManagedUnitTaskTransition, 0x0802b895\n");
