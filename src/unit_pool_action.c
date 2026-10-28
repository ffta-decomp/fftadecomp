/* Clears observed unit-pool state and the associated persistent flags. */
typedef unsigned char u8;
typedef unsigned short u16;

/* Unit field 1 is checked by the shared unit-field predicate. */
struct UnitPoolEntry {
    u8 prefix[0x28];
    u16 status_bits;
    u8 middle[0xc6];
    u8 selected_state;
    u8 suffix[0x17];
};
typedef char UnitPoolEntrySize[(sizeof(struct UnitPoolEntry) == 0x108) ? 1 : -1];

extern u8 UnitField01Equals(const struct UnitPoolEntry *unit, u8 value);
extern void SetGameFlag(u16 flag, u16 value);

/* Field roles are storage-based until a gameplay caller is validated. */
void ProcessSelectedPoolUnit(struct UnitPoolEntry *unit)
{
    unit->selected_state = 0;
    unit->status_bits &= (u16)~8;
    unit->status_bits &= (u16)~16;
    if (UnitField01Equals(unit, 8)) SetGameFlag(56, 0);
    if (UnitField01Equals(unit, 94)) SetGameFlag(70, 0);
    if (UnitField01Equals(unit, 4)) SetGameFlag(71, 0);
    if (UnitField01Equals(unit, 12)) SetGameFlag(72, 0);
    if (UnitField01Equals(unit, 9)) SetGameFlag(73, 0);
}
