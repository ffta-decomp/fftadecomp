/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct AbilityEntry { u32 prefix; u32 fields; };
struct UnitAbilityView { u8 before_list[6]; u8 list; u8 before_count[45]; u8 count; };
extern const struct AbilityEntry *GetAbilityListEntry(u8 list, u8 index);

u32 FindAbilityEntryFieldMatch(const struct UnitAbilityView *unit, const struct AbilityEntry *wanted)
{
    u32 count = unit->count;
    u16 index;
    for (index = 1; index < count; index++) {
        const struct AbilityEntry *entry = GetAbilityListEntry(unit->list, index);
        if ((entry->fields & 0xffffff) == (wanted->fields & 0xffffff))
            return index;
    }
    return 0;
}
