typedef unsigned char u8;
typedef unsigned int u32;
extern volatile u8 gSaveData[];

/* Read the selector byte at a one-based, 12-byte-spaced record index. */
u32 GetSceneSelectorValueByIndex(u32 one_based_index)
{
    u32 index = (u32)(u8)one_based_index;
    register volatile u8 *record_base __asm__("r2") = gSaveData;
    register u32 record_offset __asm__("r1");
    u32 field_offset;

    /* Materialize the two retail address terms in their observed order. */
    __asm__ volatile ("" : "+r" (record_base));
    index -= 1;
    record_offset = index * 12;
    __asm__ volatile ("" : "+r" (record_offset));
    record_offset += (u32)record_base;
    field_offset = 0x2cc3;
    __asm__ volatile ("" : "+r" (field_offset));

    return *(volatile u8 *)(record_offset + field_offset);
}
