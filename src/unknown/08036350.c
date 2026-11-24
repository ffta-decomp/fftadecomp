typedef unsigned char u8;
typedef unsigned int u32;

/* A separate symbol preserves the retail second load of the EWRAM base. */
extern volatile u8 gEwramBase[];

/* Return the one-based record slot for a selector, or zero when unavailable. */
u32 ResolveCurrentSceneSelector(u32 selector_value)
{
    u8 selector = (u8)selector_value;
    register volatile u8 *record_table __asm__("r3") = (volatile u8 *)0x02002c10;
    register u32 first_flag_offset __asm__("r1");
    register volatile u8 *first_flag_ptr __asm__("r0");
    register volatile u8 *second_base __asm__("r0");
    register u32 second_flag_offset __asm__("r1");
    register u32 record_offset __asm__("r0");
    u8 slot;

    __asm__ volatile ("" : "+r" (record_table));
    if (selector == 0)
        return 0;

    /* Both tests read EWRAM 0x02002e58 through distinct retail address forms. */
    first_flag_offset = 146;
    __asm__ volatile ("" : "+r" (first_flag_offset));
    first_flag_offset <<= 2;
    first_flag_ptr = record_table + first_flag_offset;
    __asm__ volatile ("" : "+r" (first_flag_ptr));
    if ((*first_flag_ptr & 1) == 0 && selector == 9)
        return 0;

    second_base = gEwramBase;
    second_flag_offset = 0x2e58;
    __asm__ volatile ("" : "+r" (second_base), "+r" (second_flag_offset));
    if ((second_base[second_flag_offset] & 2) == 0 && selector == 28)
        return 0;

    for (slot = 0; slot <= 29; ++slot) {
        record_offset = (u32)slot * 12;
        record_offset = (u32)record_table + record_offset;
        if (*(volatile u8 *)(record_offset + 0xb3) == selector)
            return (u8)(slot + 1);
    }
    return 0;
}
