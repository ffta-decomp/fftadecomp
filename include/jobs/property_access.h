#ifndef FFTA_JOBS_PROPERTY_ACCESS_H
#define FFTA_JOBS_PROPERTY_ACCESS_H

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
