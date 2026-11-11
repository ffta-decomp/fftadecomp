typedef unsigned char u8;
typedef unsigned int u32;
u32 UsesExtendedStreamProfile(u8 profile) __asm__("CoreFrontier_0001843C");
u32 UsesExtendedStreamProfile(u8 profile)
{
    u32 result = 0;
    if ((u8)(profile - 3) <= 1 || profile == 10 || profile == 11 ||
        profile == 12 || profile == 13 || profile == 15 || profile == 14)
        result = 1;
    return result;
}
