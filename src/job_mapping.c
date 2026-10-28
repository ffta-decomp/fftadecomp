typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 key;
    u8 value;
} __attribute__((packed)) JobMappingEntry;
typedef char JobMappingEntryHasTwoBytes[(sizeof(JobMappingEntry) == 2) ? 1 : -1];

typedef struct {
    u8 preceding_fields[4];
    u8 category;
    u8 remaining_fields[47];
} JobCategoryRecord;
typedef char JobCategoryRecordHasFiftyTwoBytes[(sizeof(JobCategoryRecord) == 52) ? 1 : -1];

typedef struct {
    u8 preceding_fields[5];
    u8 job_id;
    u8 field06;
    u8 fallback_job_id;
} UnitJobView;

extern const JobMappingEntry gJobMapping[];
extern const JobCategoryRecord gJobs[];
extern void SetGameFlag(u16 flag, u16 value);
extern void ApplyUnitJob(u8 *unit, u8 job_id);
extern u32 GetJobProperty(u8 job, u8 fallback_job, u8 property);
extern u32 ReadUnitField(const UnitJobView *unit, u8 property);
extern u32 ReadJobRelatedValue(u8 value);
extern u8 ReadClassValue(u8 index);

/* Set the observed fixed progression flags. Their narrative names remain
 * unknown; retain numeric IDs until individual callers establish meaning. */
void EnableFixedJobFlags(void)
{
    SetGameFlag(5, 1);
    SetGameFlag(8, 1);
    SetGameFlag(10, 1);
    SetGameFlag(11, 1);
    SetGameFlag(14, 1);
    SetGameFlag(16, 1);
    SetGameFlag(20, 1);
    SetGameFlag(23, 1);
    SetGameFlag(24, 1);
    SetGameFlag(28, 1);
    SetGameFlag(31, 1);
    SetGameFlag(34, 1);
    SetGameFlag(36, 1);
    SetGameFlag(39, 1);
    SetGameFlag(42, 1);
    SetGameFlag(45, 1);
}

void ApplyUnitJobWithFlag(u8 *unit, u8 job_id)
{
    /* Flag 62 brackets the existing unit-job writer and is cleared after it. */
    SetGameFlag(62, 1);
    ApplyUnitJob(unit, job_id);
    SetGameFlag(62, 0);
}

u8 ReadJobMappingValue(u8 index)
{
    const JobMappingEntry *entry = &gJobMapping[index];
    return entry->value;
}

u8 FindJobMappingKey(u8 value)
{
    int index;
    const JobMappingEntry *entry = gJobMapping;
    for (index = 0; index < 43; ++index, ++entry)
        if (entry->value == value) return entry->key;
    return 0;
}

u32 ReadUnitJobRelatedValue(const UnitJobView *unit)
{
    /* Property 40 bit 0 gates an offset-4 unit value; -1 means unavailable. */
    u8 flags = GetJobProperty(unit->job_id, unit->fallback_job_id, 40);
    if (!(flags & 1)) return -1;
    else return ReadJobRelatedValue(ReadUnitField(unit, 4));
}

u32 ReadMappedClassValue(u16 value)
{
    /* Values 202-210 select sparse class indices; other values use index 0. */
    u8 index = 0;
    switch (value) {
    case 202: index = 0; break;
    case 203: index = 2; break;
    case 204: index = 5; break;
    case 205: index = 7; break;
    case 206: index = 10; break;
    case 207: index = 12; break;
    case 208: index = 14; break;
    case 209: index = 16; break;
    case 210: index = 18; break;
    }
    return ReadClassValue(index);
}

u8 FindJobForAbilityRange(u8 category, u16 ability)
{
    /* Job properties 37/38 delimit the accepted ability-number interval. */
    u16 index;
    if (!ability) return 0;
    for (index = 0; index < 116; ++index) {
        const JobCategoryRecord *job = &gJobs[index];
        if (job->category == category) {
            u8 job_id = index;
            u16 first = GetJobProperty(job_id, job_id, 37);
            u16 last = GetJobProperty(job_id, job_id, 38);
            if (first <= ability && last >= ability) return job_id;
        }
    }
    return 0;
}
