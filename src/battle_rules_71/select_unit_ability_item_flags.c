/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetUnitProperty(const u8 *unit, u8 selector);
/* Existing exact ASM dispatches the ability/item halfword rule by mode. */
extern u16 SelectAbilityItemFlags(u16 ability_id, u16 item_id, u8 mode);
__asm__(".global SelectAbilityItemFlags\n.thumb_set SelectAbilityItemFlags, 0x080b7c2d");


u32 SelectUnitAbilityItemFlags(const u8 *unit, u16 ability_id, u16 item_id, u8 mode);
u32 SelectUnitAbilityItemFlags(const u8 *unit, u16 ability_id, u16 item_id, u8 mode)
{
    /* Preserve the unit-property override and this entry's byte-sized mode. */
    if (unit != 0 && (GetUnitProperty(unit, 40) & 4)) {
        if (mode == 0)
            return 448;
        return 450;
    }
    return SelectAbilityItemFlags(ability_id, item_id, mode);
}
