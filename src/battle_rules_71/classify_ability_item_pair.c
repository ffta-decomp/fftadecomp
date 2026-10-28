/* Method-local interface declarations from the frozen build. */
#ifndef WORKER3_CORE_REGION30_000B7C94_INTERFACES_H
#define WORKER3_CORE_REGION30_000B7C94_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 CheckAbilityItemOverride(u16 ability_id, u16 item_id);
extern u32 GetItemProperty(u16 item_id, u8 selector);
extern u32 GetAbilityProperty(u16 ability_id, u8 selector);

/* Stable source ASM helper; the alias emits no machine instructions. */
__asm__(".global CheckAbilityItemOverride\n.thumb_set CheckAbilityItemOverride, 0x080b448d");
__asm__(".global GetAbilityProperty\n.thumb_set GetAbilityProperty, 0x080ccd51");

#endif


/* ClassifyAbilityItemPair: return a mapped or raw ability/item code.
 * The original code meanings are not established by this method alone.
 */
u8 ClassifyAbilityItemPair(u16 ability_id, u16 item_id, u32 return_raw_code)
{
    u32 code;

    if (return_raw_code == 0) {
        u8 override_code = (u8)CheckAbilityItemOverride(ability_id, item_id);
        if (override_code != 0)
            return override_code;

        if (ability_id == 0) {
            if (item_id == 0) {
                code = 1;
            } else {
                u32 item_category = GetItemProperty(item_id, 3);
                if ((u32)(item_category - 13) <= 1 || item_category == 19)
                    code = 1;
                else
                    code = GetItemProperty(item_id, 5);
            }
        } else {
            u16 property_four = (u16)GetAbilityProperty(ability_id, 4);
            if ((property_four & 128) != 0) {
                code = 1;
            } else {
                u32 property_seven = GetAbilityProperty(ability_id, 7);
                if ((property_seven & 128) != 0)
                    code = 16;
                else
                    code = property_seven & 63;
            }
        }

        switch ((u8)code) {
        case 4:
        case 5:
            return 1;
        case 12:
        case 13:
            return 2;
        case 16:
            return 16;
        default:
            return 0;
        }
    }

    if (ability_id == 0) {
        if (item_id == 0) {
            code = 1;
        } else {
            u32 item_category = GetItemProperty(item_id, 3);
            if ((u32)(item_category - 13) <= 1 || item_category == 19)
                code = 1;
            else
                code = GetItemProperty(item_id, 5);
        }
    } else {
        u16 property_four = (u16)GetAbilityProperty(ability_id, 4);
        if ((property_four & 128) != 0) {
            code = 1;
        } else {
            u32 property_seven = GetAbilityProperty(ability_id, 7);
            if ((property_seven & 128) != 0)
                code = 16;
            else
                code = property_seven & 63;
        }
    }
    return (u8)code;
}
