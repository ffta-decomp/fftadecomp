/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct UnitView { u8 prefix[6]; u8 list; u8 gap[53]; u8 slot; u8 gap2[171]; u8 flags[8]; };
struct AbilityEntry { u8 prefix[4]; u16 id; u8 tail[2]; };
struct AbilityProperty { u8 fields[3]; u8 chance; };
extern const struct AbilityProperty gAbilityProperties[];
extern u8 UnitPredicate_000C8298(const void *unit);
extern const struct AbilityEntry *GetAbilityListEntry(u8 list, u8 slot);
extern u8 CheckAbilityState(const u8 *flags, u16 ability_id);
extern s16 ReadRandomValue(void);
extern s16 EvaluateRandomValue(s16 value, int bound);

asm(".global gAbilityProperties\n.set gAbilityProperties,0x0852736c\n.global UnitPredicate_000C8298\n.thumb_set UnitPredicate_000C8298,0x080c8299\n.global CheckAbilityState\n.thumb_set CheckAbilityState,0x08133b3d\n.global ReadRandomValue\n.thumb_set ReadRandomValue,0x08002805\n.global EvaluateRandomValue\n.thumb_set EvaluateRandomValue,0x08142951");
int ReadBoundedAbilityRuleValue(const struct UnitView *unit, u32 unused, u32 options)
{
    const struct AbilityEntry *entry;
    int chance;
    u32 ability_id;
    u32 property_offset;
    options = (u8)options;
    if (UnitPredicate_000C8298(unit))
        goto failure;
    entry = GetAbilityListEntry(unit->list, unit->slot);
    if (!entry->id || !CheckAbilityState(unit->flags, entry->id))
        goto failure;
    ability_id = entry->id;
    property_offset = ability_id * sizeof(struct AbilityProperty);
    chance = ((const struct AbilityProperty *)((const u8 *)gAbilityProperties + property_offset))->chance;
    options &= 4;
    if (options)
        chance += EvaluateRandomValue(ReadRandomValue(), 15);
    if (chance < 0)
        chance = 0;
    if (chance > 100)
        chance = 100;
    return chance;
failure:
    return 0;
}
