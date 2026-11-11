#include "engine/tasks/task_tree.h"

void SetDefinitionSecondaryOption(void *object,u8 option)
{
    ((u8 *)object)[41] = option;
}
