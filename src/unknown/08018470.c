typedef unsigned char u8;
typedef unsigned int u32;
u32 IsStreamProfileNine(u8 profile) __asm__("sub_08018470");
u32 IsStreamProfileNine(u8 profile)
{
    u32 result = 0;
    if (profile == 9)
        result = 1;
    return result;
}
