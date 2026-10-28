typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ItemAbilitySet {
    u8 count;
    u8 unknown_at_01;
    u8 entries[9][2];
};

typedef char ItemAbilitySetSizeMustBe20[(sizeof(struct ItemAbilitySet) == 20) ? 1 : -1];

struct UnitAbilityStateView { u8 prefix[0x40]; u8 states[0]; };

extern const struct ItemAbilitySet gItemAbilitySets[];
extern u32 GetItemProperty(u16 item, u8 property);
extern void SyncPairedAbilityState(u8 *unit, u8 ability);

static inline void MarkAbilityAvailable(u8 *unit, u8 ability)
{
    if (unit)
        ((struct UnitAbilityStateView *)unit)->states[ability] |= 0x80;
}

static inline void SetSpecialAbility(u8 *unit, u8 ability)
{
    unit[0x3d] = ability;
}

/* Applies item-granted abilities when an entry's observed job byte matches. */
void ApplyItemAbilityFlags(u8 *unit, u16 item)
{
    const struct ItemAbilitySet *set;
    int i;

    if (item == 0) return;
    set = &gItemAbilitySets[GetItemProperty(item, 18)];
    for (i = 0; i < set->count; i++) {
        if (unit[7] == set->entries[i][0]) {
            MarkAbilityAvailable(unit, set->entries[i][1]);
            SyncPairedAbilityState(unit, set->entries[i][1]);
        } else if (set->entries[i][0] == 255) {
            SetSpecialAbility(unit, set->entries[i][1]);
        }
    }
}
