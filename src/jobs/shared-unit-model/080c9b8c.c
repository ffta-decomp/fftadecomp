/* Method-local interface declarations from the frozen build. */
#include "ffta/unsigned_types.h"
#include "jobs/unit_property_access.h"
typedef signed short s16;
typedef signed int s32;
typedef struct UnitGrowthValues {
    u8 prefix[9];
    u8 level;
    u8 experience;
    u8 unknown_11[15];
    u16 max_hp;
    u16 unknown_28;
    u16 max_mp;
    u16 base_weapon_attack;
    u16 base_weapon_defense;
    u16 base_magic_power;
    u16 base_magic_resistance;
    u8 unknown_40[170];
    s16 base_speed;
} UnitGrowthValues;
#define OFFSET(T,M) ((u32)&(((T*)0)->M))
typedef char LevelOffset[OFFSET(UnitGrowthValues, level)==9?1:-1];
typedef char MaxHpOffset[OFFSET(UnitGrowthValues, max_hp)==26?1:-1];
typedef char MaxMpOffset[OFFSET(UnitGrowthValues, max_mp)==30?1:-1];
typedef char MagicResistanceOffset[OFFSET(UnitGrowthValues, base_magic_resistance)==38?1:-1];
typedef char SpeedOffset[OFFSET(UnitGrowthValues, base_speed)==210?1:-1];
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


#define APPLY_STAT_GROWTH(field, read_growth) \
    do { \
        if (unit->field != 0) { \
            growth = read_growth(unit); \
            unit->field += DivideSigned(growth, 10); \
            growth = ModuloSigned(growth, 10); \
            if (growth != 0) { \
                if ((s16)ModuloSigned((s16)NextRandom(), 10) < growth) \
                    unit->field++; \
            } \
            if (unit->field > 999) \
                unit->field = 999; \
        } \
    } while (0)

/* The byte counter advances before the bypass query. Growth fields retain
 * their original widths and are reloaded after every opaque arithmetic/RNG call. */
u32 AdvanceUnitProgressionAndGrowth(UnitGrowthValues *unit)
{
    s32 growth;
    unit->level++;
    unit->experience = 0;
    if ((u8)UnitGrowthBypass(unit))
        return 1;
    if (unit->level > 50) {
        unit->level = 50;
        unit->experience = 99;
        return 0;
    }
    APPLY_STAT_GROWTH(max_hp, ReadUnitJobHpGrowthTenths);
    APPLY_STAT_GROWTH(max_mp, ReadUnitJobMpGrowthTenths);
    APPLY_STAT_GROWTH(base_speed, ReadUnitJobSpeedGrowthTenths);
    APPLY_STAT_GROWTH(base_weapon_attack, ReadUnitJobWeaponAttackGrowthTenths);
    APPLY_STAT_GROWTH(base_weapon_defense, ReadUnitJobWeaponDefenseGrowthTenths);
    APPLY_STAT_GROWTH(base_magic_power, ReadUnitJobMagicPowerGrowthTenths);
    APPLY_STAT_GROWTH(base_magic_resistance, ReadUnitJobMagicResistanceGrowthTenths);
    return 1;
}

#undef APPLY_STAT_GROWTH
