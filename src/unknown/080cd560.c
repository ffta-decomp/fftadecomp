typedef unsigned char u8;

u8 IsAbilityAvailable(const u8 *unit, u8 ability)
{
    if (unit) {
        const u8 *states = unit + 0x40;
        if (states[ability] & 0x80) return 1;
    }
    return 0;
}

asm(".align 2, 0");
