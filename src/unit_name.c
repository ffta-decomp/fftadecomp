typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 GetJobProperty(u8 job_id, u8 fallback_job, u8 selector);

/* Converts the unit's override/job name code into the UI string-ID range. */
u16 GetUnitNameStringId(const u8 *unit)
{
    u32 name_code;

    if (unit[0x100] != 0)
        name_code = unit[0x100];
    else
        name_code = GetJobProperty(unit[5], unit[7], 0);
    return name_code + 0x247;
}
