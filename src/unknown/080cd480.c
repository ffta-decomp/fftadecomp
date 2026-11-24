typedef unsigned char u8;
typedef unsigned int u32;

struct AbilityListEntry {
    u8 unknown_at_00[4];
    u8 value_at_04;
    u8 unknown_at_05;
    u8 category;
    u8 requirement;
};

extern const struct AbilityListEntry *const gAbilityLists[];

const struct AbilityListEntry *GetAbilityListEntry(u8 list, u8 index)
{
    return &gAbilityLists[list][index];
}

static inline u8 ReadAbilitySlot(const u8 *unit, u8 offset)
{
    u8 value;
    if (unit) value = unit[offset];
    else value = 0;
    return value;
}

u8 ReadAbilitySlotA(const u8 *unit) { return ReadAbilitySlot(unit, 0x3a); }
u8 ReadAbilitySlotB(const u8 *unit) { return ReadAbilitySlot(unit, 0x3b); }
u8 ReadAbilitySlotC(const u8 *unit) { return ReadAbilitySlot(unit, 0x3c); }

u8 ReadAbilitySlotAValue(const u8 *unit)
{
    if (!ReadAbilitySlot(unit, 0x3a)) return 0;
    else {
        u8 list = unit[6];
        u8 index = unit[0x3a];
        const struct AbilityListEntry *entry = &gAbilityLists[list][index];
        return entry->value_at_04;
    }
}

u8 ReadAbilitySlotBValue(const u8 *unit)
{
    if (!ReadAbilitySlot(unit, 0x3b)) return 0;
    else {
        u8 list = unit[6];
        u8 index = unit[0x3b];
        const struct AbilityListEntry *entry = &gAbilityLists[list][index];
        return entry->value_at_04;
    }
}

asm(".align 2, 0");
