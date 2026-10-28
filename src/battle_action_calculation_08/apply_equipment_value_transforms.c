/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
struct ItemDefinition { u8 prefix[26]; u8 abilities[3]; u8 tail[3]; };
extern const struct ItemDefinition itemDefinitions[];
extern unsigned ReadUnitField(void *unit, u8 field);
extern u16 CoreRegion_0012F914(u16 operation, u16 left, u16 right);
asm(".global itemDefinitions\n.set itemDefinitions,0x0851d180\n.global CoreRegion_0012F914\n.thumb_set CoreRegion_0012F914,0x0812f915\n");

u16 ApplyEquipmentAbilityValueTransforms(void *unit, u8 operation, u8 value)
{
    int slot;
    for (slot = 0; slot <= 4; slot++) {
        unsigned item = ReadUnitField(unit, (u8)(slot + 29));
        if (item) {
            const struct ItemDefinition *definition = &itemDefinitions[item];
            int index;
            for (index = 0; index <= 2; index++)
                value = CoreRegion_0012F914(operation, (u16)(s8)value, definition->abilities[index]);
        }
    }
    return (u16)(s8)value;
}
