#include "ffta/unsigned_types.h"
#include "items/property_access.h"

struct ItemDefinition {
    u16 name_id;
    u16 unknown_at_02;
    u16 unknown_at_04;
    u16 unknown_at_06;
    u8 properties_at_08[6];
    u16 unknown_at_0e;
    signed char modifiers[8];
    u8 unknown_at_18[5];
    u8 ability_set;
    u8 unknown_at_1e[2];
};

typedef char ItemDefinitionSizeMustBe32[(sizeof(struct ItemDefinition) == 32) ? 1 : -1];

extern const struct ItemDefinition gItems[];
extern u8 ReadSaveByte(u16 index);

/* The bypass sign-extends the byte. The unsigned cap applies after any bonus. */
#define ITEM_STAT_WITH_SAVE_BONUS_CASE(selector, index, bonus_item, bonus_save_byte) \
    case selector: \
        if (ReadSaveByte(13)) return item->modifiers[index]; \
        else { \
            u32 value = item->modifiers[index]; \
            if (item_id == bonus_item) value += ReadSaveByte(bonus_save_byte); \
            if (value > 255) value = 255; \
            return value; \
        }

/* Selectors name only fields whose role is supported by callers or data use. */
u32 GetItemProperty(u16 item_id, u8 property)
{
    const struct ItemDefinition *item = &gItems[item_id];

    switch (property) {
    case ITEM_PROPERTY_NAME_ID: return item->name_id;
    case 1: return item->unknown_at_02;
    case 2: return item->unknown_at_04;
    case ITEM_PROPERTY_EQUIPMENT_CATEGORY: return item->properties_at_08[0];
    case 4: return item->properties_at_08[1];
    case 5: return item->properties_at_08[2];
    case 6: return item->properties_at_08[3];
    case 7: return item->properties_at_08[4];
    case 8: return item->properties_at_08[5];
    case 9: return item->unknown_at_0e;
    ITEM_STAT_WITH_SAVE_BONUS_CASE(ITEM_PROPERTY_PHYSICAL_ATTACK, 0, 51, 1)
    ITEM_STAT_WITH_SAVE_BONUS_CASE(ITEM_PROPERTY_PHYSICAL_DEFENSE, 1, 302, 3)
    ITEM_STAT_WITH_SAVE_BONUS_CASE(ITEM_PROPERTY_MAGIC_POWER, 2, 148, 2)
    ITEM_STAT_WITH_SAVE_BONUS_CASE(ITEM_PROPERTY_MAGIC_RESISTANCE, 3, 286, 4)
    case ITEM_PROPERTY_SPEED_MODIFIER: return item->modifiers[4];
    case 15: return item->modifiers[5];
    case 16: return item->modifiers[6];
    case 17: return item->modifiers[7];
    case ITEM_PROPERTY_ABILITY_SET_INDEX: return item->ability_set;
    default: return 0;
    }
}

#undef ITEM_STAT_WITH_SAVE_BONUS_CASE

/* Keep the original zero-filled alignment after this independently built span. */
asm(".align 2, 0");
