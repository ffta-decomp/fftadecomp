#include "interfaces.h"

/* Attribute0x3D controls the observed battle-record adjustment; retain the
 * original early-match and zero/all-mismatch shared return continuations. */
u32 ActionDependency_00130654(u32 item)
{
    const struct ItemDefinitionView *definition;
    int attribute_index;
    item = (u16)item;
    if (item != 0) goto scan_attributes;
    goto no_match;
match:
    return 1;
scan_attributes:
    definition = &ItemDefinitionsForAttributeRule[item];
    for (attribute_index = 0; attribute_index <= 2; ++attribute_index) {
        if (definition->attributes[attribute_index] == 61)
            goto match;
    }
no_match:
    return 0;
}
