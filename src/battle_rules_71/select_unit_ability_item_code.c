/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetUnitProperty(const u8 *unit, u8 selector);
/* Existing exact ASM decides a byte code from ability/item properties. */
extern u8 SelectAbilityItemCode(u16 ability_id, u16 item_id, u32 mode);
__asm__(".global SelectAbilityItemCode\n.thumb_set SelectAbilityItemCode, 0x080b7c95");


u32 SelectUnitAbilityItemCode(const u8 *unit, u16 ability_id, u16 item_id, u32 mode);
u32 SelectUnitAbilityItemCode(const u8 *unit, u16 ability_id, u16 item_id, u32 mode)
{
    /* Property40 bit2 selects the unit-specific override; code meanings remain tentative. */
    if (unit != 0 && (GetUnitProperty(unit, 40) & 4)) {
        if (mode == 0)
            return 4;
        return 1;
    }
    return SelectAbilityItemCode(ability_id, item_id, mode);
}
