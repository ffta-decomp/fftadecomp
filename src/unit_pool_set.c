/* Sets observed unit-pool state and the associated persistent flags. */
typedef unsigned char u8;
typedef unsigned short u16;

struct UnitPoolEntry {
    u8 prefix[0x28];
    u16 status_bits;
    u8 middle[0xc6];
    u8 selected_state;
    u8 post_selection[0x0b];
    u8 action_scratch[8];
    u8 suffix[4];
};
typedef char UnitPoolEntrySize[(sizeof(struct UnitPoolEntry) == 0x108) ? 1 : -1];

extern u8 UnitField01Equals(const struct UnitPoolEntry *unit, u8 value);
extern void SetGameFlag(u16 flag, u16 value);

/* Field roles are storage-based until a gameplay caller is validated. */
void SetSelectedPoolUnitState(struct UnitPoolEntry *unit, u8 state)
{
    unit->selected_state = state;
    unit->action_scratch[6] = 0;
    unit->action_scratch[7] = 0;
    if (UnitField01Equals(unit, 8)) SetGameFlag(56, 1);
    if (UnitField01Equals(unit, 94)) SetGameFlag(70, 1);
    if (UnitField01Equals(unit, 4)) SetGameFlag(71, 1);
    if (UnitField01Equals(unit, 12)) SetGameFlag(72, 1);
    if (UnitField01Equals(unit, 9)) SetGameFlag(73, 1);
    unit->status_bits |= 8;
    unit->status_bits |= 16;
}
