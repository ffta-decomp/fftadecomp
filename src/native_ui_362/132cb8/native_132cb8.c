#include "_captured_6cf5b3a2c41e749e_interfaces.h"

/* Field ownership is inferred from the observed callback and effect consumers. */
struct EquipmentEffect {
    u8 *source_unit;
    u8 reserved_04[4];
    u8 *affected_unit;
    u8 reserved_0c[12];
    u16 selected_item;
};

u32 EffectDirect_00132CB8(struct EquipmentEffect *effect, u16 property)
{
    register u32 category asm("r9")=property;
    u8 matching_slots[8];
    u32 match_count = 0;
    s32 slot = 0;
    register u32 selector_word asm("r8") = 232U << 21;
    register u32 item asm("r4");
    u8 selected_slot;
    u16 selected_item;

    asm("" : "+r"(category));
    asm("" : "+r"(selector_word));
    do {
        item = ReadUnitField(effect->affected_unit, selector_word >> 24);
        asm("" : "+r"(item));
        if (item != 0 && GetItemProperty((u16)item, 3) == category) {
            matching_slots[match_count] = (u8)slot;
            ++match_count;
        }
        selector_word += 128U << 17;
        ++slot;
    } while (slot <= 4);

    if (match_count == 0)
        return 0;

    selected_slot = matching_slots[SignedModulo((s16)NextRandom15(), match_count)];
    selected_item = (u16)ReadUnitField(effect->affected_unit,
                                        (u8)(29 + selected_slot));
    effect->selected_item = selected_item;
    {
        register u8 *unit_argument asm("r0") = effect->affected_unit;
        register u32 slot_argument asm("r2");
        asm("" : "+r"(unit_argument));
        slot_argument = selected_slot;
        asm("" : "+r"(slot_argument));
        ReplaceEquipmentSlotForScan(unit_argument, 0, slot_argument);
    }
    ScanEquipmentMask81(effect->affected_unit, 1);
    if ((u8)EffectDirect_00131BB8(effect->affected_unit) != 0)
        RemoveInventoryItem(selected_item, 1);
    if ((u8)EffectDirect_00131BB8(effect->source_unit) != 0)
        AddInventoryItem(selected_item, 1);
    UpdateUnitDerivedBytes(effect->affected_unit);
    return 1;
}

/* Existing original helper entry bindings only; no helper bodies. */
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x80c7ea5");
__asm__(".global GetItemProperty\n.thumb_set GetItemProperty, 0x80ca7a5");
__asm__(".global NextRandom15\n.thumb_set NextRandom15, 0x8002805");
__asm__(".global SignedModulo\n.thumb_set SignedModulo, 0x8142951");
__asm__(".global ReplaceEquipmentSlotForScan\n.thumb_set ReplaceEquipmentSlotForScan, 0x80caf79");
__asm__(".global AddInventoryItem\n.thumb_set AddInventoryItem, 0x80ca901");
