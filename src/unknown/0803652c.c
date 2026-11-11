typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

extern volatile u8 gSaveData[];
extern u32 FindSceneSelectorFieldSlot(u32 selector_value);
extern u32 GetSceneSelectorCandidateIfUnused(u32 selector_value,
                                              u32 field_type);

/* Refresh a selected six-byte record while preserving its upper flag bits. */
void UpdateSceneSelectorRecordFields(u32 selector_value, u32 unused_fallback)
{
    /* Keep the retail compiler's register lifetimes across the helper calls. */
    register u32 selector __asm__("r6") = (u8)selector_value;
    register s32 record_index __asm__("r2") =
        (s32)FindSceneSelectorFieldSlot(selector);
    register u32 iteration __asm__("r3");
    register volatile u8 *record __asm__("r5");
    u32 upper_bits_mask;
    register volatile u8 *save_base __asm__("r1");
    register u32 field_offset __asm__("r1");
    register volatile u8 *record_base __asm__("r0");
    register u32 mask_seed __asm__("r0");

    if (record_index < 0)
        return;

    iteration = 0;
    save_base = gSaveData;
    __asm__ volatile ("" : "+r" (save_base));
    record_base = (volatile u8 *)((u32)(record_index * 6) + (u32)save_base);
    __asm__ volatile ("" : "+r" (record_base));
    field_offset = 0x2e36;
    __asm__ volatile ("" : "+r" (field_offset));
    record = record_base + field_offset;

    /* Materialize the high-three-bit mask before the four candidate calls. */
    mask_seed = 32;
    __asm__ volatile ("" : "+r" (mask_seed));
    mask_seed = (u32)-mask_seed;
    __asm__ volatile ("" : "+r" (mask_seed));
    upper_bits_mask = mask_seed;
    __asm__ volatile ("" : "+r" (upper_bits_mask));

    do {
        u32 field_type = iteration + 1;
        register u32 candidate __asm__("r1");
        register u32 current __asm__("r0");

        candidate = GetSceneSelectorCandidateIfUnused(selector, field_type);
        __asm__ volatile ("" : "+r" (candidate));
        if (candidate != 0) {
            candidate &= 0x1f;
            current = record[0];
            __asm__ volatile ("" : "+r" (current));
            current &= upper_bits_mask;
            current |= candidate;
            record[0] = (u8)current;
        }
        iteration = field_type;
    } while ((int)iteration <= 3);
}
