typedef unsigned char u8;
typedef unsigned int u32;

void SetBattleWorkFlagSix(void) __asm__("CoreConsumer_000C7378");
void SetBattleWorkFlagSix(void)
{
    u8 *region = (u8 *)0x02015738;
    u32 current_flags;
    register u32 changed_flags __asm__("r1");
    /* Retain the native base literal plus ADD174; a defined read/write operand
     * constrains address formation and emits no instructions or memory effects. */
    __asm__("" : "+r"(region));
    current_flags = region[174];
    changed_flags = 64;
    /* RTL assigns the load to R1 and mask to R2 without this local constraint.
     * Keep the defined mask/result in native R1 and the loaded byte live beside it. */
    __asm__("" : "+r"(changed_flags) : "r"(current_flags));
    changed_flags |= current_flags;
    region[174] = (u8)changed_flags;
}
