typedef unsigned char u8;
typedef unsigned int u32;

struct UnitFieldView { u8 bytes00[4]; u8 bytes04[20]; };
extern u32 ReadUnitField(const struct UnitFieldView *unit, u8 selector);

/* Maps observed unit-field selector 3 values to five fixed content values. */
u32 SelectUnitAbilityValue(const u8 *unit)
{
    switch (ReadUnitField((const struct UnitFieldView *)unit, 3)) {
    case 1:
    case 23: return 313;
    case 2: return 312;
    case 3:
    case 20: return 314;
    case 4: return 315;
    default: return 316;
    }
}
