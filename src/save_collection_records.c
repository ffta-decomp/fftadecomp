typedef unsigned char u8;
typedef unsigned int u32;

extern u8 gSaveData[];

/* Each 16-byte save record is occupied when its first word is nonzero. */
u8 HasSaveCollectionRecord(void)
{
    u8 index = 0;
    u8 *base = gSaveData;
    u32 offset = 0x2e78;

    while (index < 20) {
        u8 *entry_base = (u8 *)((u32)(index * 16) + (u32)base);
        /* Preserve the retail order of the two address additions. */
        __asm__ volatile("" : "+r"(entry_base));
        if (*(u32 *)(entry_base + offset) != 0)
            return 1;
        index++;
    }
    return 0;
}

u8 CountSaveCollectionRecords(void)
{
    u8 index = 0;
    u8 count = 0;
    u8 *base = gSaveData;
    u32 offset = 0x2e78;

    while (index < 20) {
        u8 *entry_base = (u8 *)((u32)(index * 16) + (u32)base);
        __asm__ volatile("" : "+r"(entry_base));
        if (*(u32 *)(entry_base + offset) != 0)
            count++;
        index++;
    }
    return count;
}

/* Saturate the saved collection counter at 99. */
void IncrementSaveCounterBelow99(void)
{
    register u8 *base __asm__("r0") = gSaveData;
    register u32 offset __asm__("r2") = 0x1f68;
    u8 *counter;

    /* The named registers reproduce the separate retail base and offset. */
    __asm__ volatile("" : "+r"(base), "+r"(offset));
    counter = base + offset;
    if (*counter < 99)
        ++*counter;
}
