typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u32 GetAbilityProperty(u16 ability_id, u8 selector);
extern u8 ReadAbilitySlotBValue(const u8 *unit);
extern u32 GetItemProperty(u16 item_id, u8 selector);
__asm__(".global ReadAbilitySlotBValue\n.thumb_set ReadAbilitySlotBValue, 0x080cd50d");
__asm__(".global GetAbilityProperty\n.thumb_set GetAbilityProperty, 0x080ccd51");

asm(".global GetItemProperty\n.thumb_set GetItemProperty,0x080ca7a5");
