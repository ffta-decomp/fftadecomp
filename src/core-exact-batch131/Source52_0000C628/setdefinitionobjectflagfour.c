#include "../../../src/task_tree_core.h"

typedef signed short s16;

void SetDefinitionObjectFlagFour(void *object,u8 enabled)
{
    u16 *fields = object;
    if (enabled) {
        u16 current = fields[6];
        u32 updated = 4;
        updated |= current;
        fields[6] = updated;
    } else
        fields[6] &= 0xfffb;
}
