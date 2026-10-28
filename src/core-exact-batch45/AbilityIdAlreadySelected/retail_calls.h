/* Local fixed-address aliases for helpers in the proven ability chain. */
#define RETAIL_THUMB_ALIAS(symbol, address) \
    __asm__(".global " #symbol "\n.thumb_set " #symbol ", " address "\n")

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed char s8;
typedef signed short s16;

RETAIL_THUMB_ALIAS(AiUnitField27HasBit12, "0x080c8299");
RETAIL_THUMB_ALIAS(AiSelectUnitAbilityList, "0x080cce61");
RETAIL_THUMB_ALIAS(AiIsAbilityInRoster, "0x08133bc5");
RETAIL_THUMB_ALIAS(AiMapSpecialItemIndex, "0x080cb389");
RETAIL_THUMB_ALIAS(AiGetInventoryAvailableQuantity, "0x080cb2b5");
RETAIL_THUMB_ALIAS(AiIsAbilityAvailable, "0x080cd561");
RETAIL_THUMB_ALIAS(AiCanEnumerateAbilityForMode, "0x08133e19");
RETAIL_THUMB_ALIAS(AiCollectAvailableAbilityIds, "0x08133f71");
RETAIL_THUMB_ALIAS(AiAbilityIdAlreadySelected, "0x08133f49");
RETAIL_THUMB_ALIAS(AiGetEquipmentItemsForUnit, "0x0812f0d9");
RETAIL_THUMB_ALIAS(AiGetAbilityCostForUnit, "0x0812ed99");
RETAIL_THUMB_ALIAS(AiGetAbilityProperty, "0x080ccd51");
RETAIL_THUMB_ALIAS(AiReadUnitField, "0x080c7ea5");
RETAIL_THUMB_ALIAS(AiUnitField19IsZero, "0x080c8281");
RETAIL_THUMB_ALIAS(AiUnitStateEBHasBit7, "0x080cdb9d");
RETAIL_THUMB_ALIAS(AiUnitStateECBit0, "0x080cdbb5");
RETAIL_THUMB_ALIAS(AiUnitStateE8HasBit7, "0x080cd945");
RETAIL_THUMB_ALIAS(AiUnitStateE9HasBit0, "0x080cd95d");
RETAIL_THUMB_ALIAS(AiUnitStateEBHasBit3, "0x080cdb3d");
RETAIL_THUMB_ALIAS(AiUnitStateEBHasBit4, "0x080cdb55");
RETAIL_THUMB_ALIAS(AiGetItemProperty, "0x080ca7a5");
RETAIL_THUMB_ALIAS(AiGetUnitCostModifier, "0x080cd50d");
RETAIL_THUMB_ALIAS(AiEquipmentHasAbilityGate, "0x080cd95d");
RETAIL_THUMB_ALIAS(AiFindAbilityEquipmentItems, "0x0812e4f5");

extern u32 AiUnitField27HasBit12(const u8 *unit);
extern const u8 *AiSelectUnitAbilityList(const u8 *unit, u8 slot,
                                         u8 *first_index, u8 *last_index);
extern u32 AiIsAbilityInRoster(const u8 *unit);
extern u32 AiMapSpecialItemIndex(u8 ability_index);
extern u32 AiGetInventoryAvailableQuantity(u16 item_id);
extern u32 AiIsAbilityAvailable(const u8 *unit, u8 ability_index);
extern u32 AiCanEnumerateAbilityForMode(const u8 *unit, u16 ability_id, s8 mode);
extern u32 AiCollectAvailableAbilityIds(u16 *output, const u8 *unit,
                                        u32 mode);
extern u32 AiAbilityIdAlreadySelected(u16 ability_id, const u16 *output,
                                      s32 count);
extern void AiGetEquipmentItemsForUnit(const u8 *unit, u16 *equipment_items);
extern u32 AiGetAbilityProperty(u16 ability_id, u8 selector);
extern u32 AiReadUnitField(const u8 *unit, u8 selector);
extern u32 AiUnitField19IsZero(const u8 *unit);
extern u32 AiUnitStateEBHasBit7(const u8 *unit);
extern u32 AiUnitStateECBit0(const u8 *unit);
extern u32 AiUnitStateE8HasBit7(const u8 *unit);
extern u32 AiUnitStateE9HasBit0(const u8 *unit);
extern u32 AiUnitStateEBHasBit3(const u8 *unit);
extern u32 AiUnitStateEBHasBit4(const u8 *unit);
extern u32 AiGetItemProperty(u16 item_id, u8 selector);
extern u32 AiGetUnitCostModifier(const u8 *unit);
extern u32 AiEquipmentHasAbilityGate(const u8 *unit);
extern u32 AiFindAbilityEquipmentItems(const u8 *unit, u16 *equipment_items);
extern s32 AiGetAbilityCostForUnit(const u8 *unit, u16 ability_id);
