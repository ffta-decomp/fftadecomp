typedef unsigned char u8;

static inline u8 ReadAbilitySlot(const u8 *unit, u8 slot)
{
    if (unit) return unit[slot];
    return 0;
}

void ClearMatchingAbilitySlot(u8 *unit, u8 ability)
{
    if (ability == ReadAbilitySlot(unit, 0x3a)) unit[0x3a] = 0;
    else if (ability == ReadAbilitySlot(unit, 0x3b)) unit[0x3b] = 0;
    else if (ability == ReadAbilitySlot(unit, 0x3c)) unit[0x3c] = 0;
}
