#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

struct DefinitionStageStartup {
    u8 count;
    u8 position_mode;
    u16 delay;
    u16 flags;
    u16 reserved;
    const void *sequence;
};
typedef char DefinitionStageStartupMustBe12Bytes[
    sizeof(struct DefinitionStageStartup) == 12 ? 1 : -1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionStageCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionStageTask(const void *sequence, u8 count, u16 flags,
                                   u16 delay, TaskNode *parent)
{
    u32 event[7];
    struct DefinitionStageStartup startup;
    startup.count = count;
    startup.delay = delay;
    startup.position_mode = 0;
    startup.flags = flags;
    startup.sequence = sequence;
    if (flags & 8)
        startup.position_mode = 1;
    else if (flags & 16)
        startup.position_mode = 2;
    event[1] = (u32)&startup;
    return CreateTaskInCurrentGroup(DefinitionStageCallback,16,event,parent);
}

asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
    ".global DefinitionStageCallback\n.thumb_set DefinitionStageCallback,0x80dfb0d\n");
