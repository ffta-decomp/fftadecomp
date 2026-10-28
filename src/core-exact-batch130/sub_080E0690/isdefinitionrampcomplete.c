#include "../../../src/task_tree_core.h"

typedef signed short s16;

u32 IsDefinitionRampComplete(const s16 *state)
{
    u32 complete = 0;
    if (state[1] == 0)
        complete = 1;
    return complete;
}
