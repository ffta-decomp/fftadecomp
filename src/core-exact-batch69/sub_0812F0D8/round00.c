typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetEquipmentItemsForUnit(const u8 *unit, u16 *items)
    __asm__("ReactionPolicyCall_0812E55C");
/* Preserve the full count returned by the existing equipment rule. */
u32 CollectBattleUnitEquipmentItems(const u8 *unit, u16 *items)
{
    return GetEquipmentItemsForUnit(unit, items);
}
