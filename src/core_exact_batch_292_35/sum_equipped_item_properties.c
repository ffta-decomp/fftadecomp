#ifndef WORKER3_CORE_REGION_0012F5E0_INTERFACES_H
#define WORKER3_CORE_REGION_0012F5E0_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u8 UnitStateE9HasBit0(const void *unit);
extern s32 GetUnitExcludedItemIds(const void *unit, u16 ids[2]);
extern u32 GetItemProperty(u16 item_id, u8 selector);
extern u32 GetUnitDefaultProperty10(const void *unit);
extern u32 ReadUnitField(const void *unit, u8 selector);

/* Source-backed helper bindings; these directives emit no instructions. */
__asm__(".global GetUnitExcludedItemIds\n.thumb_set GetUnitExcludedItemIds, 0x0812f0d9");
__asm__(".global GetUnitDefaultProperty10\n.thumb_set GetUnitDefaultProperty10, 0x08130821");

#endif


/* Sum the unit's item-derived property after excluding its paired item IDs. */
u32 CoreRegion_0012F5E0(const void *unit, u16 initial_item_id, u16 property)
{
    u16 excluded_item_ids[2];
    s32 excluded_count;
    register u32 total __asm__("r6");
    s32 field_index;

    if (UnitStateE9HasBit0(unit) != 0)
        return 0;

    total = 0;
    /* Consume the initialized accumulator before collecting excluded item IDs. */
    asm("" : "+r"(total));
    excluded_count = GetUnitExcludedItemIds(unit, excluded_item_ids);
    if (excluded_count <= 0)
        excluded_count = 0;

    if (property != 10) {
        excluded_count = 0;
    } else {
        u32 initial_value;
        if (initial_item_id != 0)
            initial_value = GetItemProperty(initial_item_id, 10);
        else
            initial_value = GetUnitDefaultProperty10(unit);
        total = initial_value;
    }

    for (field_index = 0; field_index <= 4; field_index++) {
        u16 item_id = (u16)ReadUnitField(unit, (u8)(field_index + 29));
        s32 exclusion_index;

        if (item_id == 0)
            continue;
        exclusion_index = 0;
        while (exclusion_index < excluded_count) {
            if (excluded_item_ids[exclusion_index] == item_id)
                break;
            exclusion_index++;
        }
        if (exclusion_index >= excluded_count)
            total += GetItemProperty(item_id, (u8)property);
    }
    return total;
}
