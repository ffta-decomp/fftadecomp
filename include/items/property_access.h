#ifndef FFTA_ITEMS_PROPERTY_ACCESS_H
#define FFTA_ITEMS_PROPERTY_ACCESS_H

/* Keep each caller's existing declaration of GetItemProperty. */
#define ITEM_PROPERTY_NAME_ID 0
#define ITEM_PROPERTY_EQUIPMENT_CATEGORY 3
#define ITEM_PROPERTY_PHYSICAL_ATTACK 10
#define ITEM_PROPERTY_PHYSICAL_DEFENSE 11
#define ITEM_PROPERTY_MAGIC_POWER 12
#define ITEM_PROPERTY_MAGIC_RESISTANCE 13
#define ITEM_PROPERTY_SPEED_MODIFIER 14
#define ITEM_PROPERTY_ABILITY_SET_INDEX 18

#define ReadItemNameId(item) \
    GetItemProperty(item, ITEM_PROPERTY_NAME_ID)
#define ReadItemEquipmentCategory(item) \
    GetItemProperty(item, ITEM_PROPERTY_EQUIPMENT_CATEGORY)
#define ReadItemPhysicalAttack(item) \
    GetItemProperty(item, ITEM_PROPERTY_PHYSICAL_ATTACK)
#define ReadItemMagicPower(item) \
    GetItemProperty(item, ITEM_PROPERTY_MAGIC_POWER)
#define ReadItemAbilitySetIndex(item) \
    GetItemProperty(item, ITEM_PROPERTY_ABILITY_SET_INDEX)

#endif
