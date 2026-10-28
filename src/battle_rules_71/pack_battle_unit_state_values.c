/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Retail stores this unaligned record byte by byte; field labels retain
 * the verified unit selector until their game meaning is established. */
struct PackedUnitState {
    u32 reference;
    u8 present;
    u8 unit_field_06;
    u8 preserved_06[2];
    u32 unit_field_20 : 10;
    u32 unit_field_22 : 10;
    u32 unit_field_23 : 11;
    u32 unit_field_24 : 11;
    u32 unit_field_25 : 11;
    u32 unit_field_26 : 11;
} __attribute__((packed));
typedef char PackedStateSizeCheck[sizeof(struct PackedUnitState) == 16 ? 1 : -1];
typedef char PresenceOffsetCheck[(unsigned)&((struct PackedUnitState *)0)->present == 4 ? 1 : -1];
extern u32 ReadUnitField(const u8 *unit, u8 selector);
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x080c7ea5");

void PackBattleUnitStateValues(struct PackedUnitState *output, const u8 *unit);
void PackBattleUnitStateValues(struct PackedUnitState *output, const u8 *unit)
{
    output->reference = ReadUnitField(unit, 0);
    output->present = 1;
    output->unit_field_06 = ReadUnitField(unit, 6);
    output->unit_field_20 = (u16)ReadUnitField(unit, 20);
    output->unit_field_22 = (u16)ReadUnitField(unit, 22);
    output->unit_field_23 = (u16)ReadUnitField(unit, 23);
    output->unit_field_24 = (u16)ReadUnitField(unit, 24);
    output->unit_field_25 = (u16)ReadUnitField(unit, 25);
    output->unit_field_26 = (u16)ReadUnitField(unit, 26);
}
