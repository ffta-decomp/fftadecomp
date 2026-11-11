typedef unsigned char u8;
typedef unsigned int u32;

extern const u8 gMappedJobIds[];
extern const void *const gJobContentPointers[];
extern u32 GetJobProperty(u8 job, u8 fallback_job, u8 selector);

/* The caller supplies a byte-sized index into the retail job mapping. */
u8 ReadMappedJob(u8 index)
{
    return gMappedJobIds[index];
}

u8 ReadMappedJobProperty01(u8 index)
{
    u8 job = gMappedJobIds[index];
    return (u8)GetJobProperty(job, job, 1);
}

u8 ReadMappedJobProperty04(u8 index)
{
    u8 job = gMappedJobIds[index];
    return (u8)GetJobProperty(job, job, 4);
}

u8 ReadMappedJobProperty06(u8 index)
{
    u8 job = gMappedJobIds[index];
    return (u8)GetJobProperty(job, job, 6);
}

u8 ReadMappedJobProperty09(u8 index)
{
    u8 job = gMappedJobIds[index];
    return (u8)GetJobProperty(job, job, 9);
}

/* Job property zero indexes a separate table of content pointers. */
const void *ReadMappedJobContentPointer(u8 index)
{
    const void *const *content_pointers = gJobContentPointers;
    u8 job;
    u32 pointer_index;

    /* Keep the pointer-table base live across the property lookup. */
    __asm__ volatile("" : "+r"(content_pointers));
    job = gMappedJobIds[index];
    pointer_index = GetJobProperty(job, job, 0);
    return content_pointers[pointer_index];
}
