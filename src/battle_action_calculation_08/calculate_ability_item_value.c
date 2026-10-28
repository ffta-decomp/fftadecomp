/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 RetailCall_080ccd50(u16, u8);
extern s32 RetailCall_0812f410(const u8 *, u16);
extern s32 RetailCall_0812f48c(const u8 *, s16, u16, u16, u16);
extern s32 RetailCall_0812f528(const u8 *, u8, s16);
extern u32 RetailCall_0812f6e0(const u8 *);
extern s32 RetailCall_0812f690(const u8 *, u16, u16, s16);
asm(".global RetailCall_080ccd50\n.thumb_set RetailCall_080ccd50,0x080ccd51");
asm(".global RetailCall_0812f410\n.thumb_set RetailCall_0812f410,0x0812f411");
asm(".global RetailCall_0812f48c\n.thumb_set RetailCall_0812f48c,0x0812f48d");
asm(".global RetailCall_0812f528\n.thumb_set RetailCall_0812f528,0x0812f529");
asm(".global RetailCall_0812f6e0\n.thumb_set RetailCall_0812f6e0,0x0812f6e1");
asm(".global RetailCall_0812f690\n.thumb_set RetailCall_0812f690,0x0812f691");

/* Ability-dependent value pipeline; category meanings remain unconfirmed. */
s32 CalculateAbilityItemValue(const u8 *unit, const u8 *other_unit,
                       u16 ability_id, u16 item_id, u16 extra_value)
{
    u32 special;
    if (ability_id == 0 || RetailCall_080ccd50(ability_id, 29) != 0)
        special = 0;
    else
        special = 1;
    {
    s16 base_value = RetailCall_0812f410(unit, special);
    s16 scaled_value = RetailCall_0812f48c(unit, base_value, ability_id, item_id, extra_value);
    u16 amount = RetailCall_0812f528(unit, special, scaled_value);
    if (ability_id == 136 && (u8)RetailCall_0812f6e0(other_unit) == 1)
        amount *= 2;
    return (s16)RetailCall_0812f690(unit, ability_id, item_id, (s16)amount);
    }
}
