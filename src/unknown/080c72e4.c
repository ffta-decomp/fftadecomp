typedef unsigned char u8;
typedef unsigned int u32;

u32 GetBattleWorkFlagOne(void) __asm__("CoreConsumer_000C72E4");
u32 GetBattleWorkFlagOne(void)
{
    u8 *region = (u8 *)0x02015738;
    /* Keep the observed base literal plus ADD174 instead of folding the address.
     * The initialized read/write operand emits no instruction or memory effect. */
    __asm__("" : "+r"(region));
    return (region[174] >> 1) & 1;
}
