#ifndef FFTA_JOBS_PROPERTY_ACCESS_H
#define FFTA_JOBS_PROPERTY_ACCESS_H

/* Base values from the job record. */
#define JOB_PROPERTY_BASE_HP 23
#define JOB_PROPERTY_BASE_MP 24
#define JOB_PROPERTY_BASE_WEAPON_ATTACK 26
#define JOB_PROPERTY_BASE_WEAPON_DEFENSE 27
#define JOB_PROPERTY_BASE_MAGIC_POWER 28
#define JOB_PROPERTY_BASE_MAGIC_RESISTANCE 29

/* Growth rates in tenths. */
#define JOB_PROPERTY_HP_GROWTH_TENTHS 41
#define JOB_PROPERTY_MP_GROWTH_TENTHS 42
#define JOB_PROPERTY_SPEED_GROWTH_TENTHS 43
#define JOB_PROPERTY_WEAPON_ATTACK_GROWTH_TENTHS 44
#define JOB_PROPERTY_WEAPON_DEFENSE_GROWTH_TENTHS 45
#define JOB_PROPERTY_MAGIC_POWER_GROWTH_TENTHS 46
#define JOB_PROPERTY_MAGIC_RESISTANCE_GROWTH_TENTHS 47

/* Keep each caller's existing declaration of GetJobProperty. */
#define JOB_PROPERTY_EQUIPMENT_CLASS_MASK_INDEX 36
#define JOB_PROPERTY_FIRST_ABILITY_INDEX 37
#define JOB_PROPERTY_LAST_ABILITY_INDEX 38

#define ReadJobEquipmentClassMaskIndex(job, fallback) \
    GetJobProperty(job, fallback, JOB_PROPERTY_EQUIPMENT_CLASS_MASK_INDEX)

/* Ability list indices include both endpoints. */
#define ReadJobFirstAbilityIndex(job, fallback) \
    GetJobProperty(job, fallback, JOB_PROPERTY_FIRST_ABILITY_INDEX)
#define ReadJobLastAbilityIndex(job, fallback) \
    GetJobProperty(job, fallback, JOB_PROPERTY_LAST_ABILITY_INDEX)

#endif
