/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct UnitGrowthValues {
    u8 prefix[9];
    u8 progression;
    u8 fractional_progress;
    u8 unknown_11[15];
    u16 maximum_first;
    u16 unknown_28;
    u16 maximum_second;
    u16 stat_32;
    u16 stat_34;
    u16 stat_36;
    u16 stat_38;
    u8 unknown_40[170];
    s16 stat_210;
} UnitGrowthValues;
#define OFFSET(T,M) ((u32)&(((T*)0)->M))
typedef char ProgressOffset[OFFSET(UnitGrowthValues, progression)==9?1:-1];
typedef char FirstOffset[OFFSET(UnitGrowthValues, maximum_first)==26?1:-1];
typedef char SecondOffset[OFFSET(UnitGrowthValues, maximum_second)==30?1:-1];
typedef char LastOffset[OFFSET(UnitGrowthValues, stat_38)==38?1:-1];
typedef char SignedOffset[OFFSET(UnitGrowthValues, stat_210)==210?1:-1];
extern u32 UnitGrowthBypass(const UnitGrowthValues *);
extern u32 GetUnitProperty(const void *,u8);
extern s32 DivideSigned(s32,s32);
extern s32 ModuloSigned(s32,s32);
extern u32 NextRandom(void);
__asm__(".global UnitGrowthBypass\n.thumb_set UnitGrowthBypass, 0x080c8299");
__asm__(".global GetUnitProperty\n.thumb_set GetUnitProperty, 0x080c92f1");
__asm__(".global DivideSigned\n.thumb_set DivideSigned, 0x081426b9");
__asm__(".global ModuloSigned\n.thumb_set ModuloSigned, 0x08142951");
__asm__(".global NextRandom\n.thumb_set NextRandom, 0x08002805");


/* The byte counter advances before the bypass query. Growth fields retain
 * their original widths and are reloaded after every opaque arithmetic/RNG call. */
u32 AdvanceUnitProgressionAndGrowth(UnitGrowthValues *unit)
{
    s32 growth;
    unit->progression++;
    unit->fractional_progress = 0;
    if ((u8)UnitGrowthBypass(unit))
        return 1;
    if (unit->progression > 50) {
        unit->progression = 50;
        unit->fractional_progress = 99;
        return 0;
    }
    if (unit->maximum_first != 0) {
        growth = GetUnitProperty(unit, 41);
        unit->maximum_first += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->maximum_first++;
        }
        if (unit->maximum_first > 999)
            unit->maximum_first = 999;
    }
    if (unit->maximum_second != 0) {
        growth = GetUnitProperty(unit, 42);
        unit->maximum_second += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->maximum_second++;
        }
        if (unit->maximum_second > 999)
            unit->maximum_second = 999;
    }
    if (unit->stat_210 != 0) {
        growth = GetUnitProperty(unit, 43);
        unit->stat_210 += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->stat_210++;
        }
        if (unit->stat_210 > 999)
            unit->stat_210 = 999;
    }
    if (unit->stat_32 != 0) {
        growth = GetUnitProperty(unit, 44);
        unit->stat_32 += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->stat_32++;
        }
        if (unit->stat_32 > 999)
            unit->stat_32 = 999;
    }
    if (unit->stat_34 != 0) {
        growth = GetUnitProperty(unit, 45);
        unit->stat_34 += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->stat_34++;
        }
        if (unit->stat_34 > 999)
            unit->stat_34 = 999;
    }
    if (unit->stat_36 != 0) {
        growth = GetUnitProperty(unit, 46);
        unit->stat_36 += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->stat_36++;
        }
        if (unit->stat_36 > 999)
            unit->stat_36 = 999;
    }
    if (unit->stat_38 != 0) {
        growth = GetUnitProperty(unit, 47);
        unit->stat_38 += DivideSigned(growth, 10);
        growth = ModuloSigned(growth, 10);
        if (growth != 0) {
            if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth)
                unit->stat_38++;
        }
        if (unit->stat_38 > 999)
            unit->stat_38 = 999;
    }
    return 1;
}
