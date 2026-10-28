/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct AbilityEntry { u8 prefix[4]; u16 id; u8 kind; u8 requirement; };
struct UnitAbilityView { u8 prefix[6]; u8 list; u8 gap[45]; u8 count; u8 gap2[11]; u8 mastery[0]; };
extern u32 ReadUnitField(const void *unit, u8 selector);
extern const struct AbilityEntry *GetAbilityListEntry(u8 list, u8 index);
extern u16 RejectAbility(u16 id);
extern u32 ReadAbilityProperty(u16 id, u32 selector);

asm(".global RejectAbility\n.thumb_set RejectAbility,0x08133c01\n.global ReadAbilityProperty\n.thumb_set ReadAbilityProperty,0x080ccd51");
u16 CollectMasteredAbilityEntries(const struct AbilityEntry **output, const struct UnitAbilityView *unit)
{
    u32 limit = unit->count;
    u32 count = 0;
    u16 index;
    for (index = 1; index < limit; index++) {
        const struct AbilityEntry *entry = GetAbilityListEntry(ReadUnitField(unit, 3), index);
        if (entry->kind == 1 && !RejectAbility(entry->id) && ReadAbilityProperty(entry->id, 25) && !ReadAbilityProperty(entry->id, 22)) {
            u32 mastery = unit->mastery[index] & 127;
            if (mastery >= GetAbilityListEntry(unit->list, index)->requirement) {
                *output++ = entry;
                count++;
            }
        }
    }
    return count;
}
