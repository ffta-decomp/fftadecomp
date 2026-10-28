/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit;
extern u32 GetUnitProperty(const struct Unit *,u8);
extern int UnitField27HasBit14(const struct Unit *);
extern u8 UnitField01Equals(const struct Unit *,u8);
extern u8 GetGameFlag(u16);
extern u8 UnitProperty22HasHighBit(const struct Unit *);
asm(".global UnitProperty22HasHighBit\n.thumb_set UnitProperty22HasHighBit,0x0812c961");
asm(".global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9");


u8 ResolveUnitActionProperty22(const struct Unit *unit, u16 action, u32 *value)
{
    *value = GetUnitProperty(unit, 22) & 127;
    if ((u8)UnitField27HasBit14(unit)) {
        switch (action) {
        case 44:
        case 46:
        case 50:
            goto force_value;
        }
    }
    if (action == 44) {
        if (UnitField01Equals(unit, 4) && GetGameFlag(602))
            goto force_value;
        if (UnitField01Equals(unit, 12) && GetGameFlag(603))
            goto force_value;
    }
    if (UnitProperty22HasHighBit(unit)) {
        switch (action) {
        case 4:
        case 5:
        case 6:
        case 12:
        case 18:
        case 19:
        case 22:
        case 24:
        case 27:
        case 41:
        case 42:
        case 44:
        case 46:
        case 50:
        case 56:
        case 61:
        case 71:
        case 80:
force_value:
            *value = 100;
            return 1;
        }
    }
    return 0;
}
