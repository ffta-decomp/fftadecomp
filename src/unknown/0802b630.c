typedef unsigned int u32;
struct UnitTaskContext;
extern struct UnitTaskContext *gCurrentUnitTasks;
__asm__(".global gCurrentUnitTasks\n.set gCurrentUnitTasks,0x0200f440");
u32 ResetCurrentUnitTaskContext(void) __asm__("CoreGlobal36_0002B630");
u32 ResetCurrentUnitTaskContext(void)
{
    gCurrentUnitTasks = 0;
    /* Preserve the native R0 value without assigning it a status meaning. */
    return 0;
}
