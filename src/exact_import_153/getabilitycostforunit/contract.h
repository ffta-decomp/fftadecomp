typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern u32 GetAbilityProperty(u16 ability_id, u8 selector);
extern u32 GetUnitCostModifier(const u8 *unit);
__asm__(".thumb_set GetAbilityProperty, 0x080ccd51\n"
        ".thumb_set GetUnitCostModifier, 0x080cd50d\n");
