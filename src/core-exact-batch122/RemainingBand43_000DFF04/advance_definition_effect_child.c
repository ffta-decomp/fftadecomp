#include "../../../src/task_tree_core.h"

struct DefinitionEffectStartupView {
    u16 delay;
    u8 count;
    u8 reserved;
    void *sequence;
};
struct DefinitionEffectEvent {
    u16 state;
    u16 unknown_02;
    const struct DefinitionEffectStartupView *startup;
    u32 unknown_08[5];
};
struct DefinitionEffectChildState {
    u16 delay;
    u8 count;
    u8 reserved;
    void *sequence;
    TaskNode *child;
};
typedef char DefinitionStartupViewMustBe8Bytes[
    sizeof(struct DefinitionEffectStartupView) == 8 ? 1 : -1];
typedef char DefinitionEventMustBe28Bytes[
    sizeof(struct DefinitionEffectEvent) == 28 ? 1 : -1];
typedef char DefinitionChildStateMustBe12Bytes[
    sizeof(struct DefinitionEffectChildState) == 12 ? 1 : -1];
extern u32 QueryDefinitionEffectReadiness(void);
extern TaskNode *CreateManagedTaskChild(void *, u8, TaskNode *);
extern TaskNode *PollAndReleaseEffectFollowup(TaskNode *);

u32 AdvanceDefinitionEffectChild(TaskNode *task,
                                  struct DefinitionEffectEvent *event,
                                  struct DefinitionEffectChildState *payload)
{
    switch (event->state) {
    case 0: {
        const struct DefinitionEffectStartupView *startup = event->startup;
        payload->count = startup->count;
        payload->sequence = startup->sequence;
        payload->delay = startup->delay;
        break;
    }
    case 1:
        break;
    case 256:
        if ((u8)QueryDefinitionEffectReadiness() == 0) {
            if (payload->sequence != 0 && payload->count != 0)
                payload->child = CreateManagedTaskChild(
                    payload->sequence, payload->count, task);
            /* Creation may change the event; use its post-call state. */
            event->state++;
        }
        break;
    case 257:
        if (payload->delay != 0)
            payload->delay--;
        payload->child = PollAndReleaseEffectFollowup(payload->child);
        if (payload->child == 0 && payload->delay == 0)
            event->state = 2;
        break;
    }
    return 0;
}

asm(".global QueryDefinitionEffectReadiness\n.thumb_set QueryDefinitionEffectReadiness,0x080D8B4D\n"
    ".global CreateManagedTaskChild\n.thumb_set CreateManagedTaskChild,0x080D7A71\n"
    ".global PollAndReleaseEffectFollowup\n.thumb_set PollAndReleaseEffectFollowup,0x080D7ABD\n");
