#include "../../../src/task_tree_core.h"

struct DefinitionPaletteParameter {
    u32 unknown_00[2];
    u16 parameter;
};
extern struct DefinitionPaletteParameter *GetTaskPayload(TaskNode *);

void SetDefinitionPaletteParameter(TaskNode *task,u16 parameter)
{
    GetTaskPayload(task)->parameter = parameter;
}

__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd\n");
