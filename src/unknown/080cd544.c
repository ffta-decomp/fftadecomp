typedef unsigned char u8;

struct UnitAbilityStateView { u8 prefix[0x40]; u8 states[0]; };

void SetAbilityAvailable(u8 *unit, u8 ability)
{
    if (unit)
        ((struct UnitAbilityStateView *)unit)->states[ability] |= 0x80;
}

asm(".align 2, 0");
