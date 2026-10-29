#include "interfaces.h"

void CollectAvailableFlag10AbilityRows(struct AbilityMenuContext *context, struct AbilityScanState *scan) __asm__("Source52_00026F9C");
void CollectAvailableFlag10AbilityRows(struct AbilityMenuContext *context, struct AbilityScanState *scan)
{
    struct AbilityMenuLayout *layout = &context->layout;
    s32 index;
    register s32 count asm("r10");
    scan->cost_width = 0;
    index = scan->first;
    /* Preserve the actual zero-count working definition after the first index load. */
    count = 0;
    asm ("" : "+r" (count));
    for (; index <= scan->last; ++index) {
        const struct AbilityListEntry *entry = scan->entries + index;
        register const struct AbilityDefinition *definition asm("r5");
        u8 name_width;
        if (entry->kind != 1 && entry->kind != 4)
            continue;
        if (!IsAbilityAvailable(gActiveAbilitySelection->unit, index))
            continue;
        if (!GetAbilityProperty(entry->ability_id, 21))
            continue;
        {
            u32 definition_byte_offset = (u32)entry->ability_id * 28;
            /* Define the actual preserved pointer only at the original
               final ADD; its inputs retain their preceding C arithmetic. */
            asm ("add %0, %1, %2"
                : "=&l" (definition)
                : "l" (definition_byte_offset), "l" (gAbilityDefinitions)
                : "cc");
        }
        context->indices[count] = index;
        if (UnitStateEBHasBit3(gActiveAbilitySelection->unit)
            && !GetAbilityProperty(entry->ability_id, 20)) {
            if (definition->mp_cost != 0) {
                u32 cost = definition->mp_cost;
                if (scan->cost_width <= 2)
                    scan->cost_width = 3;
                if (cost > 99)
                    scan->cost_width = 4;
            }
            goto disable_row;
        } else {
            if (definition->mp_cost != 0) {
                u32 cost = definition->mp_cost;
                if (scan->cost_width <= 2)
                    scan->cost_width = 3;
                if (cost > 99)
                    scan->cost_width = 4;
                if (*(const u16 *)(gActiveAbilitySelection->unit + 28) < cost)
                    goto disable_row;
            }
            goto row_ready;
        }
    disable_row:
        context->enabled[count] = 0;
    row_ready:
        ++count;
        name_width = ReadEncodedTextTileWidth(gAbilityNames[definition->name_id]);
        if (name_width > scan->name_width)
            scan->name_width = name_width;
    }
    if (scan->cost_width != 0)
        layout->cost_marker = 9;
    scan->count = count;
}

/* Symbol-only existing helper binding; no helper body or extra instruction. */
asm(".global UnitStateEBHasBit3\n.thumb_set UnitStateEBHasBit3,0x080cdb3d");
