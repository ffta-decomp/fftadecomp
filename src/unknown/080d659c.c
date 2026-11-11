typedef unsigned char u8;
typedef unsigned short u16;
struct TaskNode;
struct TransitionTarget {void *slot;u16 offset;u16 reserved;};
struct TransitionTargetPrefix {u8 unknown0[38];u8 count;u8 unknown39;struct TransitionTarget targets[4];};
typedef char TargetSize[sizeof(struct TransitionTarget)==8?1:-1];
typedef char TargetsOffset[(unsigned int)&((struct TransitionTargetPrefix*)0)->targets==40?1:-1];
extern struct TransitionTargetPrefix *GetTransitionTaskPayload(struct TaskNode*);
void AppendDefinitionTransitionTarget(struct TaskNode*,void*,u16) __asm__("RemainingBand43_000D659C");
void AppendDefinitionTransitionTarget(struct TaskNode *task,void *slot,u16 offset)
{
    struct TransitionTargetPrefix *state=GetTransitionTaskPayload(task);
    if(state->count<=3) {
        state->targets[state->count].slot=slot;
        state->targets[state->count].offset=offset;
        state->count++;
    }
}
__asm__(".global GetTransitionTaskPayload\n.thumb_set GetTransitionTaskPayload,0x08005bfd");
