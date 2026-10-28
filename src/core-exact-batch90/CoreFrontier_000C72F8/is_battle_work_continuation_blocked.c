typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 PollSerialSession(void);
__asm__(".global PollSerialSession\n.thumb_set PollSerialSession, 0x08004d69");

u32 IsBattleWorkContinuationBlocked(void) __asm__("CoreFrontier_000C72F8");
u32 IsBattleWorkContinuationBlocked(void)
{
    register u8 *region __asm__("r1") = (u8 *)0x02015738;
    u32 flags;
    register u32 masked_flags __asm__("r0");
    register u8 *flags_address __asm__("r0");
    /* Preserve the native base-plus-field address and its R1 lifetime.
     * The initialized operand is not used after the real serial-service call. */
    __asm__("" : "+r"(region));
    flags = region[174];
    if ((flags & 64) != 0) {
        masked_flags = 128;
        /* lreg otherwise consumes the dying flags register. Keep the defined
         * native mask/result in R0, with the original byte value as an input. */
        __asm__("" : "+r"(masked_flags) : "r"(flags));
        masked_flags &= flags;
        if (masked_flags != 0)
            return PollSerialSession() != 1;
        return 0;
    }
    masked_flags = 32;
    __asm__("" : "+r"(masked_flags) : "r"(flags));
    masked_flags &= flags;
    if (masked_flags != 0 || region[172] > 13) {
        register u8 *serial_state __asm__("r2") = (u8 *)0x030028a0;
        register u32 counter_offset __asm__("r3");
        /* Keep the native serial-state base separate from its 288/290 offsets. */
        __asm__("" : "+r"(serial_state));
        counter_offset = 288;
        /* RTL otherwise forms two constants. Retain the observed shared offset
         * as a defined value, then advance it by two for the second halfword. */
        __asm__("" : "+r"(counter_offset) : "r"(serial_state));
        if (*(u16 *)(serial_state + counter_offset) != 0)
            return 1;
        if (serial_state[2] != 3) {
            register u16 *counter_address __asm__("r0");
            counter_offset += 2;
            counter_address = (u16 *)(serial_state + counter_offset);
            /* Keep the native load address in R0 instead of consuming R2. */
            __asm__("" : "+r"(counter_address));
            if (*counter_address > 16)
                return 1;
        }
    }
    flags_address = region + 174;
    /* Preserve the original R0 address result instead of consuming base R1. */
    __asm__("" : "+r"(flags_address));
    if ((*flags_address & 8) != 0)
        return 1;
    return 0;
}
