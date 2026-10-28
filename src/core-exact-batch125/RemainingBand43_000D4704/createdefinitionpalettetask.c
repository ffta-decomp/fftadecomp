#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void DefinitionPaletteCallback(TaskNode *,u16 *,void *);
TaskNode *CreateDefinitionPaletteTask(const void *sequence, TaskNode *parent)
{
    u32 event[7];
    ((u16 *)event)[10] = 0;
    event[1] = (u32)sequence;
    return CreateTaskInCurrentGroup(DefinitionPaletteCallback,24,event,parent);
}

asm(".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
    ".global DefinitionPaletteCallback\n.thumb_set DefinitionPaletteCallback,0x80d449d\n");
