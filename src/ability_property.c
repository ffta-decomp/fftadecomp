typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct AbilityDefinition {
    u16 name_id;
    u8 category;
    u8 unknown_at_03;
    u8 mp_cost;
    u8 unknown_at_05;
    u8 unknown_at_06;
    u8 unknown_at_07;
    u8 range;
    u8 area;
    u8 unknown_at_0a;
    u8 power;
    u8 effects[4];
    u32 flags;
    u16 unknown_at_14;
    u8 padding_at_16[6];
};

typedef char AbilityDefinitionSizeMustBe28[(sizeof(struct AbilityDefinition) == 28) ? 1 : -1];

static const struct AbilityDefinition *const gAbilityDefinitions =
    (const struct AbilityDefinition *)0x0855187c;

/* Names for selector-returned fields are cross-checked against retail callers. */
u32 GetAbilityProperty(u16 ability_id, u8 selector)
{
    const struct AbilityDefinition *definition = &gAbilityDefinitions[ability_id];
    u8 flag_index;

    flag_index = selector - 11;
    if (flag_index <= 20)
        return (definition->flags & (1 << flag_index)) != 0;

    switch (selector) {
    case 0: return definition->name_id;
    case 1: return definition->category;
    case 2: return definition->mp_cost;
    case 3: return definition->unknown_at_05;
    case 4: return definition->unknown_at_06;
    case 5: return definition->unknown_at_07;
    case 6: return definition->range;
    case 7: return definition->area;
    case 8: return definition->unknown_at_0a;
    case 9: return (u32)&definition->effects[0];
    case 10: return definition->flags;
    case 32: return definition->unknown_at_14;
    case 33: return definition->power;
    default: return 0;
    }
}
