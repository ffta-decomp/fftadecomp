typedef unsigned char u8;
typedef unsigned int u32;
extern void ResetSerialSession(void);
__asm__(".global ResetSerialSession\n.thumb_set ResetSerialSession, 0x08004cd5");

void RequestBattleWorkSerialReset(void) __asm__("CoreFrontier_000C738C");
void RequestBattleWorkSerialReset(void)
{
    register u8 *region __asm__("r0") = (u8 *)0x02015738;
    register u8 *flags_address __asm__("r2");
    u32 current_flags;
    register u32 masked_flags __asm__("r0");
    /* Preserve the native R0 base followed by the R2 field-address lifetime. */
    __asm__("" : "+r"(region));
    flags_address = region + 174;
    __asm__("" : "+r"(flags_address));
    current_flags = *flags_address;
    masked_flags = 128;
    /* Defined mask/result in R0 keeps the original byte live in R1.
     * These constraints emit no instructions and cross no calls. */
    __asm__("" : "+r"(masked_flags) : "r"(current_flags));
    masked_flags &= current_flags;
    if (masked_flags == 0) {
        masked_flags = 192;
        __asm__("" : "+r"(masked_flags) : "r"(current_flags));
        masked_flags |= current_flags;
        *flags_address = (u8)masked_flags;
        ResetSerialSession();
    }
}
