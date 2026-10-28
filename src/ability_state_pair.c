typedef unsigned char u8;
typedef unsigned int u32;

struct UnitFieldView { u8 bytes00[4]; u8 field03; };
extern u32 ReadUnitField(const struct UnitFieldView *unit, u8 selector);

/* Pairing is observed only for unit-field selector 3 value four. */
void SyncPairedAbilityState(u8 *unit, u8 ability)
{
    u32 other;
    u8 *states;

    if (ReadUnitField((const struct UnitFieldView *)unit, 3) == 4) {
        if (ability == 26) other = 33;
        else if (ability == 33) other = 26;
        else return;
        states = unit + 0x40;
        states[other] = states[ability];
    }
}
