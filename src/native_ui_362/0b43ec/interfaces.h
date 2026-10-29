typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u32 GetItemProperty(u16,u8);
extern u32 ReadAbilityProperty(u16,u8);
__asm__(".global ReadAbilityProperty\n.thumb_set ReadAbilityProperty,0x080ccd51\n");

asm(".global GetItemProperty\n.thumb_set GetItemProperty,0x080ca7a5");
