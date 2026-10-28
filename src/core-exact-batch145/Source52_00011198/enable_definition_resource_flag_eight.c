#include "../../../src/task_tree_core.h"
struct DefinitionFlagsPrefix {
    u8 unknown0[20];
    u16 flags;
};
void EnableDefinitionResourceFlagEight(struct DefinitionFlagsPrefix *resource)
{
    resource->flags |= 0x100;
}
