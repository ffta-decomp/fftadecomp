typedef unsigned char u8;
typedef unsigned int u32;

extern volatile u8 gEwramBase[];

/* Find a one-based slot in a caller-provided 30-record table. */
u32 FindSceneSelectorRecord(u32 selector_value, volatile u8 *record_table)
{
    u8 selector;
    register volatile u8 *table __asm__("r4") = record_table;
    register volatile u8 *flag_base __asm__("r2");
    register u32 flag_offset __asm__("r1");
    register volatile u8 *flag_ptr __asm__("r0");
    register u32 record_offset __asm__("r0");
    u8 slot;

    /* Keep the caller's table pointer before the selector's byte truncation. */
    __asm__ volatile ("" : "+r" (table));
    selector = (u8)selector_value;
    __asm__ volatile ("" : "+r" (selector));

    /* Both gates read 0x02002e58; retail loads the offset twice. */
    flag_base = gEwramBase;
    flag_offset = 0x2e58;
    __asm__ volatile ("" : "+r" (flag_base), "+r" (flag_offset));
    flag_ptr = flag_base + flag_offset;
    __asm__ volatile ("" : "+r" (flag_ptr));
    if ((*flag_ptr & 1) == 0 && selector == 9)
        return 0;

    flag_offset = 0x2e58;
    __asm__ volatile ("" : "+r" (flag_offset));
    flag_ptr = flag_base + flag_offset;
    __asm__ volatile ("" : "+r" (flag_ptr));
    if ((*flag_ptr & 2) == 0 && selector == 28)
        return 0;

    for (slot = 0; slot <= 29; ++slot) {
        record_offset = (u32)slot * 12;
        record_offset = (u32)table + record_offset;
        if (*(volatile u8 *)(record_offset + 0xb3) == selector)
            return (u8)(slot + 1);
    }
    return 0;
}
