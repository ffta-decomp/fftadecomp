#ifndef FFTA_JOBS_UNIT_PROPERTY_ACCESS_H
#define FFTA_JOBS_UNIT_PROPERTY_ACCESS_H

#include "jobs/property_access.h"

/* Use the caller's original GetUnitProperty declaration for job fallback. */
#define ReadUnitJobBaseHp(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_BASE_HP)
#define ReadUnitJobBaseMp(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_BASE_MP)
#define ReadUnitJobBaseWeaponAttack(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_BASE_WEAPON_ATTACK)
#define ReadUnitJobBaseWeaponDefense(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_BASE_WEAPON_DEFENSE)
#define ReadUnitJobBaseMagicPower(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_BASE_MAGIC_POWER)
#define ReadUnitJobBaseMagicResistance(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_BASE_MAGIC_RESISTANCE)

#define ReadUnitJobHpGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_HP_GROWTH_TENTHS)
#define ReadUnitJobMpGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_MP_GROWTH_TENTHS)
#define ReadUnitJobSpeedGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_SPEED_GROWTH_TENTHS)
#define ReadUnitJobWeaponAttackGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_WEAPON_ATTACK_GROWTH_TENTHS)
#define ReadUnitJobWeaponDefenseGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_WEAPON_DEFENSE_GROWTH_TENTHS)
#define ReadUnitJobMagicPowerGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_MAGIC_POWER_GROWTH_TENTHS)
#define ReadUnitJobMagicResistanceGrowthTenths(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_MAGIC_RESISTANCE_GROWTH_TENTHS)

#define ReadUnitJobEquipmentClassMaskIndex(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_EQUIPMENT_CLASS_MASK_INDEX)
#define ReadUnitJobFirstAbilityIndex(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_FIRST_ABILITY_INDEX)
#define ReadUnitJobLastAbilityIndex(unit) \
    GetUnitProperty(unit, JOB_PROPERTY_LAST_ABILITY_INDEX)

#endif
