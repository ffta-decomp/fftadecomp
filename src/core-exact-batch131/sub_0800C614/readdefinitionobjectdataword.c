#include "../../../src/task_tree_core.h"

typedef signed short s16;

u32 ReadDefinitionObjectDataWord(const void *object)
{
    u16 present = ((const u16 *)object)[8];
    u32 data = 0;
    if (present != 0)
        data = ((const u32 *)object)[5];
    return data;
}
