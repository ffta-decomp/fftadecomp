#include "../../../src/task_tree_core.h"

void SetDefinitionSecondaryOption(void *object,u8 option)
{
    ((u8 *)object)[41] = option;
}
