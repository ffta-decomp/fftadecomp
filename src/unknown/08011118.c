#include "engine/tasks/task_tree.h"

typedef signed short s16;

void SetDefinitionObjectOption(void *object, u8 option)
{
    ((u8 *)object)[40] = option;
}
