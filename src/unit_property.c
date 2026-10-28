typedef unsigned char u8;
typedef unsigned int u32;

extern u32 GetJobProperty(u8 job_id, u8 fallback_job, u8 selector);

/* The complete unit layout remains unknown; these offsets are retail-observed. */
u32 GetUnitProperty(const u8 *unit, u8 property)
{
    if (property == 0 && unit[0x100] != 0)
        return unit[0x100];
    return GetJobProperty(unit[5], unit[7], property);
}
