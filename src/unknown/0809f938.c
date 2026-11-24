typedef signed char s8;
typedef unsigned int u32;
struct Unit;
struct StatusCycle;
extern void AdvanceUnitStatusCycle(const struct Unit *, struct StatusCycle *);
__asm__(".global AdvanceUnitStatusCycle\n.thumb_set AdvanceUnitStatusCycle,0x0809dcc5");
u32 AdvanceUnitStatusAndCheckVisible(const struct Unit *, struct StatusCycle *) __asm__("IsolatedCore57_0009F938");
u32 AdvanceUnitStatusAndCheckVisible(const struct Unit *unit, struct StatusCycle *cycle)
{
    int phase;
    AdvanceUnitStatusCycle(unit, cycle);
    phase = *(s8 *)cycle;
    switch (phase) {
    case 2:
    case 3:
    case 4:
        return 1;
    default:
        return 0;
    }
}
