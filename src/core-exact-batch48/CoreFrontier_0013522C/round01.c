#include "interfaces.h"
/* Live rule-list first-match scan; ids[1] describes its starting address, not capacity. */
u8 FindFirstMatchingDefinitionRule(void *actor, void *target, u16 selector,
    u8 mode, u16 adjustment, void *payload) asm("CoreFrontier_0013522C");
u8 FindFirstMatchingDefinitionRule(void *actor, void *target, u16 selector,
    u8 mode, u16 adjustment, void *payload)
{
    int ordinal;
    for (ordinal = 0; ordinal < gRuleRoster.count; ++ordinal) {
        if (EvaluateDefinitionRule(actor, target, selector, mode, 0, (s16)adjustment,
                payload, &gRuleDefinitions[gRuleDefinitions[gRuleRoster.ids[ordinal]].parent]))
            return (u8)(ordinal + 1);
    }
    return 0;
}
