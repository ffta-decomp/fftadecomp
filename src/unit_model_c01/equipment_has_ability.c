/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct ItemDefinition { u8 prefix[26]; u8 abilities[3]; u8 tail[3]; };
extern const struct ItemDefinition itemDefinitions[];
extern unsigned ReadUnitField(void *unit, u8 field);
asm(".global itemDefinitions\n.set itemDefinitions,0x0851d180\n");

int UnitEquipmentHasAbility(void *unit, u16 ability)
{
    int slot;
    for (slot = 0; slot <= 4; slot++) {
        u16 item = ReadUnitField(unit, (u8)(slot + 29));
        if (item) {
            const struct ItemDefinition *definition = &itemDefinitions[item];
            u16 index = 0;
            const u8 *abilities = definition->abilities;
            for (; index <= 2; index++)
                if (abilities[index] == ability)
                    return 1;
        }
    }
    return 0;
}
