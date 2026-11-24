typedef unsigned short u16;
typedef unsigned int u32;
extern const u16 gUnitStatusScaleByStep[];
__asm__(".global gUnitStatusScaleByStep\n.set gUnitStatusScaleByStep,0x08394358");
u32 LookupUnitStatusScale(int step) __asm__("IsolatedCore57_0009F958");
u32 LookupUnitStatusScale(int step)
{
    return gUnitStatusScaleByStep[step];
}
