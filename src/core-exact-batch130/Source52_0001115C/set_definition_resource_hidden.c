#include "../../../src/task_tree_core.h"

struct DefinitionResourceFlags {
    u8 unknown_00[20];
    u16 flags;
};
void SetDefinitionResourceHidden(struct DefinitionResourceFlags *,u8)
    asm("Source52_0001115C");
void SetDefinitionResourceHidden(struct DefinitionResourceFlags *resource,u8 hidden)
{
    if (hidden!=0)
        resource->flags&=0xfffe;
    else
        resource->flags|=1;
}
