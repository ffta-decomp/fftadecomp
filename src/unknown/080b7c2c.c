typedef unsigned char u8;
typedef unsigned short u16;
extern unsigned int ReadPrimaryActionFlags(u16, u16) __asm__("0x080b42e4");
extern unsigned int ReadAlternateActionFlags(u16, u16) __asm__("0x080b43ec");
u16 ChooseActionFlags(u16 ability, u16 item, u8 alternate_lane)
{
    unsigned int flags;
    if (alternate_lane)
        flags = ReadAlternateActionFlags(ability, item);
    else
        flags = ReadPrimaryActionFlags(ability, item);
    return flags;
}
