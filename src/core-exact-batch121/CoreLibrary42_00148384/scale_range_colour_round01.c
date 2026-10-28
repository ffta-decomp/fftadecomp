typedef unsigned short u16;
typedef unsigned int u32;
u16 ScaleRangeColour(u16 colour, u16 red_gain, u16 green_gain, u16 blue_gain)
    __asm__("CoreLibrary42_00148384");
u16 ScaleRangeColour(u16 colour, u16 red_gain, u16 green_gain, u16 blue_gain)
{
    u32 red = colour & 31;
    u32 green = (colour & 0x3e0) >> 5;
    u32 blue = (colour & 0x7c00) >> 10;
    red *= red_gain;
    red >>= 8;
    if (red & 0xffe0)
        red = 31;
    green *= green_gain;
    green >>= 8;
    if (green & 0xffe0)
        green = 31;
    blue *= blue_gain;
    blue >>= 8;
    if (blue & 0xffe0)
        blue = 31;
    return red | (green << 5) | (blue << 10);
}
