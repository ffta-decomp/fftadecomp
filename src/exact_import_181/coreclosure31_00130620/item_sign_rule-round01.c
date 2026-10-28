typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Physical fields consumed here, not a complete item schema. */
struct ItemEffectDefinition {
    u8 unknown_00[26];
    u8 effect_codes[3];
    u8 unknown_1d[3];
};
typedef char ItemDefinitionSize[(sizeof(struct ItemEffectDefinition) == 32) ? 1 : -1];
typedef char ItemEffectsOffset[((u32)&((struct ItemEffectDefinition *)0)->effect_codes == 26) ? 1 : -1];

/* Symbol-only fixed ROM object binding; emits no instructions. */
extern const struct ItemEffectDefinition ItemEffectDefinitions[];
__asm__(".global ItemEffectDefinitions\n.set ItemEffectDefinitions,0x0851d180");

u32 ItemReversesActionAmount(u32 item_id) __asm__("CoreClosure31_00130620");
u32 ItemReversesActionAmount(u32 item_id)
{
    const struct ItemEffectDefinition *definition;
    int effect_index;

    item_id = (u16)item_id;
    if (item_id != 0)
        goto scan_effects;
    goto no_match;
match:
    return 1;
scan_effects:
    definition = &ItemEffectDefinitions[item_id];
    for (effect_index = 0; effect_index <= 2; ++effect_index) {
        /* The caller negates its amount on code 0x3f; its caption is unknown. */
        if (definition->effect_codes[effect_index] == 0x3f)
            goto match;
    }
no_match:
    return 0;
}
