#include "../../task_tree_core.h"

struct DefinitionLayerExitEvent {
    u32 unwritten_state;
    void *record;
    u32 unwritten_words[3];
    u16 range_gate;
    u16 range_parameter;
    u16 layer;
    u16 unwritten_tail;
};
typedef char DefinitionLayerExitEventMustBe28Bytes[
    sizeof(struct DefinitionLayerExitEvent) == 28 ? 1 : -1];
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback, u16, const u32 *, TaskNode *);
extern void DefinitionLayerExitCallback(TaskNode *, u16 *, void *);

TaskNode *RemainingBand43_000DC2F0(void *record, u8 gate, u16 parameter,
                                  TaskNode *parent)
{
    struct DefinitionLayerExitEvent event;
    event.record = record;
    event.range_gate = gate;
    event.range_parameter = parameter;
    event.layer = 3;
    return CreateTaskInCurrentGroup(DefinitionLayerExitCallback, 16,
                                    (const u32 *)&event, parent);
}
asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
    ".global DefinitionLayerExitCallback\n.thumb_set DefinitionLayerExitCallback,0x080db6d1\n");
