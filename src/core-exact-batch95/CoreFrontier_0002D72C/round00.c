typedef unsigned char u8;
typedef unsigned int u32;
struct TaskNode;
struct UnitTaskSlots { u8 unknown0[8]; struct TaskNode *primary; struct TaskNode *secondary; };
extern struct UnitTaskSlots *gUnitTaskContext;
__asm__(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200f440");
struct TaskNode *GetUnitTaskHandle(u32 selector)
{
    struct TaskNode *task;
    if ((u8)selector != 0)
        task = gUnitTaskContext->primary;
    else
        task = gUnitTaskContext->secondary;
    return task;
}
