typedef unsigned char u8;
typedef unsigned int u32;

extern u32 UnsignedDivide(u32 dividend, u32 divisor);

/* Scale the tens count of byte +9 by byte +0xf0, capping at 99999. */
u32 CalculateUnitByteAmount(const u8 *unit)
{
    register u32 factor __asm__("r0");
    u32 multiplier;
    u32 amount;

    factor = (u8)UnsignedDivide(unit[9], 10) * 2 + 1;
    /* Keep the factor in r0 before evaluating the multiplier, as retail does. */
    __asm__ volatile("" : "+r" (factor));
    multiplier = (u32)unit[0xf0] * 1000;
    amount = factor * multiplier;
    if (amount > 99999)
        amount = 99999;
    return amount;
}
