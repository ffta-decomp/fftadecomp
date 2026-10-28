#include "../../../include/task_group.h"

extern struct TaskGroup gMenuTaskGroup;
asm(".global gMenuTaskGroup\n.set gMenuTaskGroup,0x03002710");

TaskU8 CoreRegion_0004E008(void)
{
    return gMenuTaskGroup.slot_state[0];
}
