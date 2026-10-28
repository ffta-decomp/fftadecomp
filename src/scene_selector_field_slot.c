typedef unsigned char u8;
typedef unsigned int u32;

extern volatile u8 gSaveData[];

/* Return the first of five selector-field slots, or 0xffffffff if absent. */
u32 FindSceneSelectorFieldSlot(u32 selector_value)
{
    register u32 selector __asm__("r2") = (u8)selector_value;
    register u32 slot __asm__("r1");
    register u32 field_offset __asm__("r4");
    register volatile u8 *record __asm__("r2");
    register u32 compared_selector __asm__("r3");
    register volatile u8 *save_base __asm__("r0");

    /* The separate success label retains the retail early-return layout. */
    if (selector != 0)
        goto scan_records;
    goto no_match;

record_found:
    return slot;

scan_records:
    slot = 0;
    /* Keep the save base, compared byte, and field offset in retail registers. */
    save_base = gSaveData;
    __asm__ volatile ("" : "+r" (save_base));
    compared_selector = selector;
    __asm__ volatile ("" : "+r" (compared_selector));
    field_offset = 0x2e36;
    __asm__ volatile ("" : "+r" (field_offset));
    record = save_base + field_offset;

    do {
        u32 stored_selector = *record;
        stored_selector = (stored_selector << 27) >> 27;
        if (stored_selector == compared_selector)
            goto record_found;
        record += 6;
        slot++;
    } while ((int)slot <= 4);

no_match:
    return 0xffffffff;
}
