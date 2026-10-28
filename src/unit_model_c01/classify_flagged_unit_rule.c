/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitView { u8 prefix[40]; u16 flags; };
extern u8 UnitField27HasBit15(const void *unit);
extern u8 UnitField01Equals(const void *unit, u8 value);
extern u8 ReadGameFlag(u32 index);
extern u32 ReadUnitField(const void *unit, u8 selector);

asm(".global ReadGameFlag\n.thumb_set ReadGameFlag,0x080c9541");
u32 ClassifyFlaggedUnitRule(const struct UnitView *unit)
{
    if (!unit)
        return 0;
    if (UnitField27HasBit15(unit) || !(unit->flags & 0x400) || UnitField01Equals(unit, 2))
        return 0;
    if (ReadGameFlag(0x226)) {
        switch ((u8)ReadUnitField(unit, 1)) {
        case 10: return 6;
        case 9: return 7;
        case 4: return 8;
        case 12: return 9;
        case 94: return 10;
        }
    }
    switch (ReadUnitField(unit, 3)) {
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    }
    return 0;
}
