#include "../../../src/task_tree_core.h"
struct MotionRecord;
struct DefinitionSequenceStartup {
    void *actor;
    u8 count;
    u8 reserved5[3];
    u8 *completion;
    const struct MotionRecord *sequence;
    u16 delay;
    u16 flags;
    u8 state;
    u8 reserved21;
    u16 parameter;
};
typedef char StartupMustBe24Bytes[
    sizeof(struct DefinitionSequenceStartup)==24?1:-1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionSequenceCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionSequenceTask(void *actor, u8 count, u8 *completion,
    const struct MotionRecord *sequence, u16 unused_flags, u16 delay,
    TaskNode *parent)
{
    u32 event[7];
    struct DefinitionSequenceStartup startup;
    startup.actor = actor;
    startup.count = count;
    startup.completion = completion;
    startup.sequence = sequence;
    startup.delay = delay;
    /* The native producer leaves flags/state/parameter and other event bytes
     * unassigned. The unused fifth argument does not initialize flags. */
    event[1] = (u32)&startup;
    return CreateTaskInCurrentGroup(DefinitionSequenceCallback,44,event,parent);
}
asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global DefinitionSequenceCallback\n.thumb_set DefinitionSequenceCallback,0x080ddc19\n");
