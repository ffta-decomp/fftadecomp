#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

struct DefinitionRecordStartup {
    void *record;
    u8 *completion;
    u8 mode;
    s8 selector;
    u8 option;
    u8 countdown;
    u16 delay;
    u16 reserved;
};
typedef char DefinitionRecordStartupMustBe16Bytes[
    sizeof(struct DefinitionRecordStartup) == 16 ? 1 : -1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionRecordCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionRecordTask(void *record, u8 *completion, u8 mode,
                                    s8 selector, u8 option, u8 countdown,
                                    u16 delay, TaskNode *parent)
{
    u32 event[7];
    struct DefinitionRecordStartup startup;
    startup.record = record;
    startup.completion = completion;
    startup.mode = mode;
    startup.selector = selector;
    startup.option = option;
    startup.countdown = countdown;
    startup.delay = delay;
    event[1] = (u32)&startup;
    return CreateTaskInCurrentGroup(DefinitionRecordCallback,16,event,parent);
}

asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
    ".global DefinitionRecordCallback\n.thumb_set DefinitionRecordCallback,0x80dda95\n");
