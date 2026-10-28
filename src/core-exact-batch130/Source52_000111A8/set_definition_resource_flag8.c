#include "../../../src/task_tree_core.h"

struct DefinitionResourceFlags {
    u8 unknown_00[20];
    u16 flags;
};
void SetDefinitionResourceFlag8(struct DefinitionResourceFlags *,u8)
    asm("Source52_000111A8");
void SetDefinitionResourceFlag8(struct DefinitionResourceFlags *resource,u8 enabled)
{
    if (enabled!=0)
        resource->flags|=8;
    else
        resource->flags&=0xfff7;
}
