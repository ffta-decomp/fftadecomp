#include "../../../src/task_tree_core.h"

struct DefinitionPaletteEvent {
    u32 unknown_00;
    const void *sequence;
    u32 unknown_08[3];
    u16 parameter;
    u16 unknown_16[3];
};
typedef char EventSize[sizeof(struct DefinitionPaletteEvent) == 28 ? 1 : -1];
extern void AdvanceDefinitionPaletteTask(TaskNode *,u16 *,void *);
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void SetDefinitionPaletteParameter(TaskNode *,u16);

TaskNode *CreateDefinitionPaletteTask(const void *sequence,TaskNode *parent,
                                      u16 parameter)
{
    struct DefinitionPaletteEvent event;
    TaskNode *created;
    event.parameter = 0;
    event.sequence = sequence;
    created = CreateTaskInCurrentGroup(AdvanceDefinitionPaletteTask,24,
                                       (const u32 *)&event,parent);
    SetDefinitionPaletteParameter(created,parameter);
    return created;
}

__asm__(".global AdvanceDefinitionPaletteTask\n"
        ".thumb_set AdvanceDefinitionPaletteTask,0x080d449d\n"
        ".global CreateTaskInCurrentGroup\n"
        ".thumb_set CreateTaskInCurrentGroup,0x08005b6d\n"
        ".global SetDefinitionPaletteParameter\n"
        ".thumb_set SetDefinitionPaletteParameter,0x080d4821\n");
