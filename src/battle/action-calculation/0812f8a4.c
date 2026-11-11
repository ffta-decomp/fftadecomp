/* Method-local interface declarations from the frozen build. */
typedef unsigned short u16;
extern unsigned GetAbilityProperty(unsigned ability, unsigned property);
extern unsigned GetItemProperty(unsigned item, unsigned property);
/* Existing helper target; no implementation emitted. */
asm(".global GetAbilityProperty\n.thumb_set GetAbilityProperty, 0x080ccd51\n");

/* Ability property 1 overrides item property 4; property 3 permits fallback. */
unsigned ResolveAbilityItemProperty4(unsigned unused, u16 ability, u16 item)
{
    if (ability != 0) {
        unsigned property = (u16)GetAbilityProperty(ability, 1);
        if (property != 0)
            return property;
        if (GetAbilityProperty(ability, 3) == 0)
            return 0;
    }
    if (item != 0)
        return (u16)GetItemProperty(item, 4);
    else
        return 0;
}
