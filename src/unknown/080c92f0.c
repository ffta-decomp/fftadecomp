typedef unsigned char u8;
typedef unsigned int u32;

extern u32 GetJobProperty(u8 job_id, u8 fallback_job, u8 selector);

#define UNIT_JOB_ID_OFFSET 5
#define UNIT_FALLBACK_JOB_ID_OFFSET 7
#define UNIT_PROPERTY_ZERO_OVERRIDE_OFFSET 0x100

/* A nonzero unit override takes precedence for selector zero. */
u32 GetUnitProperty(const u8 *unit, u8 property)
{
    if (property == 0 && unit[UNIT_PROPERTY_ZERO_OVERRIDE_OFFSET] != 0)
        return unit[UNIT_PROPERTY_ZERO_OVERRIDE_OFFSET];
    return GetJobProperty(unit[UNIT_JOB_ID_OFFSET], unit[UNIT_FALLBACK_JOB_ID_OFFSET], property);
}
