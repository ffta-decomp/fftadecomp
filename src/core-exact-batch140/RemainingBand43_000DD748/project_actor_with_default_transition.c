#include "../../../src/task_tree_core.h"

typedef signed short s16;
extern void *ProjectActorAndApplyValue(void *,u16 *,u16 *,u16 *,s16);

void *ProjectActorWithDefaultTransition(void *record,u16 *x,u16 *y,u16 *z)
{
    return ProjectActorAndApplyValue(record,x,y,z,-2);
}

__asm__(".global ProjectActorAndApplyValue\n"
        ".thumb_set ProjectActorAndApplyValue,0x080dd761\n");
