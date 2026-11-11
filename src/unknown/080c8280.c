typedef unsigned char u8;
typedef unsigned short u16;

/* Only the observed halfword at +0x18 is named by its storage offset. */
typedef struct {
    u8 bytes00[0x18];
    u16 field_19;
} UnitField19View;

/* Returns whether the observed unit field at +0x18 is clear. */
int UnitField19IsZero(const UnitField19View *unit)
{
    return unit != 0 && unit->field_19 == 0;
}
