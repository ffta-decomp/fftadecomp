typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GatherAbilityEquipmentItems(const u8 *unit, u16 *items);
__asm__(".global GatherAbilityEquipmentItems\n.thumb_set GatherAbilityEquipmentItems, 0x0812e4f5");
/* Keep the full producer count, even when a caller uses only its first item. */
u32 CollectBattleAbilityEquipmentItems(const u8 *unit, u16 *items)
{
    return GatherAbilityEquipmentItems(unit, items);
}
