typedef unsigned char u8;
typedef unsigned int u32;

static volatile u32 *const gSceneSelectorStatePointer =
    (volatile u32 *)0x03002810;

/* Test a selector against the active scene or six 52-byte state records.
 * Named registers and empty constraints retain the retail load/compare order
 * without replacing the recovered decision logic with assembly. */
u32 TestSceneSelectorState(u32 selector_value, u32 selector_mode)
{
    register u32 selector __asm__("r4") = (u8)selector_value;
    volatile u8 *selector_record;
    register volatile u8 *flag_record __asm__("r3");
    register volatile u8 *last_record __asm__("r5");
    register u32 record_index __asm__("r2");
    register volatile u8 *scan_state __asm__("r1");
    register u32 selector_field_offset __asm__("r1");
    register u32 flag_offset __asm__("r3");
    register u32 flag_base __asm__("r0");

    if (selector == 0)
        return 0;
    if (selector_mode == 1) {
        u32 scene_address = *gSceneSelectorStatePointer;
        register u32 observed __asm__("r1");
        register u32 expected __asm__("r0");
        observed = *(volatile u8 *)(scene_address + 0x7bb);
        __asm__ volatile("" : "+r" (observed));
        expected = selector - 1;
        __asm__ volatile("" : "+r" (expected));
        if (observed == expected)
            return 1;
        return 0;
    }

    /* Every other nonzero mode skips record zero. */
    if (selector_mode != 0)
        selector_mode = 1;
    record_index = selector_mode;
    __asm__ volatile("" : "+r" (record_index));
    if ((int)record_index > 5)
        return 0;
    scan_state = (volatile u8 *)*gSceneSelectorStatePointer;
    __asm__ volatile("" : "+r" (scan_state));
    record_index *= 52;
    /* Form the flag offset before adding the state base, as in retail. */
    flag_offset = 0x7b8;
    __asm__ volatile("" : "+r" (flag_offset));
    flag_base = record_index + flag_offset;
    __asm__ volatile("" : "+r" (flag_base));
    flag_record = (volatile u8 *)(flag_base + (u32)scan_state);
    selector_record = (volatile u8 *)(record_index + (u32)scan_state);
    last_record = scan_state + 5 * 52;
    do {
        if (((u32)*flag_record << 31) != 0) {
            register u32 field_address __asm__("r0");
            register u32 observed __asm__("r1");
            register u32 expected __asm__("r0");
            selector_field_offset = 0x7bb;
            __asm__ volatile("" : "+r" (selector_field_offset));
            field_address = (u32)selector_record + selector_field_offset;
            __asm__ volatile("" : "+r" (field_address));
            observed = *(volatile u8 *)field_address;
            __asm__ volatile("" : "+r" (observed));
            expected = selector - 1;
            __asm__ volatile("" : "+r" (expected));
            if (observed == expected)
                return 1;
        }
        flag_record += 52;
        selector_record += 52;
    } while ((int)(u32)selector_record <= (int)(u32)last_record);
    return 0;
}
