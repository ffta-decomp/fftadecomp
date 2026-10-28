typedef unsigned int u32;
extern u32 AdvanceCoordinateRecord(void *record);
__asm__(".global AdvanceCoordinateRecord\n.thumb_set AdvanceCoordinateRecord,0x0809fdc1");
u32 AdvanceGlobalCoordinateRecord(void) __asm__("CoreDependency29_000A83DC");
u32 AdvanceGlobalCoordinateRecord(void)
{
    return AdvanceCoordinateRecord((void *)0x0200f898);
}
