/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
struct Unit;
extern u32 AbilityProperty(u16,u8);
extern s32 MissionAdjustedField(const struct Unit *,u16);
extern s32 AdjustValueByKind(const struct Unit *,s32,u8);
extern s32 AdjustValueByStatus(const struct Unit *,s32,u8);
extern s32 AddEquipmentValue(const struct Unit *,s32,u8);
__asm__(".thumb_set AbilityProperty,0x080ccd51");
__asm__(".thumb_set MissionAdjustedField,0x0812f705");
__asm__(".thumb_set AdjustValueByKind,0x0812f771");
__asm__(".thumb_set AdjustValueByStatus,0x0812f799");
__asm__(".thumb_set AddEquipmentValue,0x0812f875");


/* Keep the original ordered value-transform chain and its full-width values. */
s32 CalculateOrderedUnitValue(void *unused, const struct Unit *unit, u16 ability)
{
    s32 alternate;
    s32 value;
    if (ability == 0 || AbilityProperty(ability, 29) != 0)
        alternate = 0;
    else
        alternate = 1;
    value = MissionAdjustedField(unit, alternate);
    value = AdjustValueByKind(unit, value, alternate);
    value = AdjustValueByStatus(unit, value, alternate);
    value = AddEquipmentValue(unit, value, alternate);
    return value;
}
