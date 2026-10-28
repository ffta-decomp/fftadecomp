typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct TaskNode;
struct SelectionResult { s16 result; u8 unknown_02[2]; u8 mode; };
struct SelectionInput { u8 unknown_00[9]; u8 flags; };
struct SelectionState {
    u32 unknown_00;
    struct TaskNode *owner;
    u8 unknown_08[4];
    u8 controller[116];
    struct SelectionInput input;
};
extern u32 PollManagedSelectionInput(void *);
extern void SetManagedTaskState(struct TaskNode *, u16);
extern struct TaskNode *GetManagedUnitTaskHandle(u32);
extern void QueueManagedUnitTaskTransition(struct TaskNode *, u8, u8);

u32 RouteManagedSelectionResult(struct SelectionState *state)
{
    struct SelectionInput *input;
    struct TaskNode *owner;
    struct SelectionResult *current;
    s16 result;

    input = (struct SelectionInput *)((u8 *)state + 128);
    if ((u8)PollManagedSelectionInput(state->controller) != 0) {
        owner = state->owner;
        if (owner != 0) {
            result = (*(struct SelectionResult **)0x0200f438)->result;
            if (result > 0)
                SetManagedTaskState(owner, 259);
            else if (result == -1)
                SetManagedTaskState(owner, 263);
        } else {
            current = *(struct SelectionResult **)0x0200f438;
            if (current->result == -1)
                current->mode = 0;
        }
        return 1;
    }
    if ((input->flags & 16) != 0) {
        if ((*(struct SelectionResult **)0x0200f438)->result <= 0)
            QueueManagedUnitTaskTransition(GetManagedUnitTaskHandle(1), 1, 0);
    }
    return 0;
}
asm(".thumb_set PollManagedSelectionInput, 0x08017181\n"
    ".thumb_set SetManagedTaskState, 0x08005ba9\n"
    ".thumb_set GetManagedUnitTaskHandle, 0x0802d72d\n"
    ".thumb_set QueueManagedUnitTaskTransition, 0x0802b895\n");
