#include "../../task_tree_core.h"

struct RecordDefinitionStartup {
    u16 selector;
    u16 flags;
    void *parameter;
    void *unwritten_record;
};
typedef char RecordDefinitionStartupMustBe12Bytes[
    sizeof(struct RecordDefinitionStartup) == 12 ? 1 : -1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback, u16, const u32 *, TaskNode *);
extern void RecordDefinitionCallback(TaskNode *, u16 *, void *);

TaskNode *RemainingBand43_000DF978(void *parameter, u16 flags, u16 event_parameter,
                                  TaskNode *parent)
{
    u32 event[7];
    struct RecordDefinitionStartup startup;
    startup.selector = 0xffff;
    startup.parameter = parameter;
    startup.flags = flags;
    ((u16 *)event)[10] = event_parameter;
    event[1] = (u32)&startup;
    return CreateTaskInCurrentGroup(RecordDefinitionCallback, 28, event, parent);
}
asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global RecordDefinitionCallback\n.thumb_set RecordDefinitionCallback,0x080def91\n");
