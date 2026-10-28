typedef unsigned char u8;
typedef unsigned int u32;
u32 IsAlternateStreamProfile(u8 profile) __asm__("CoreFrontier_000184D0");
u32 IsAlternateStreamProfile(u8 profile)
{
    u32 result = 0;
    if ((u8)(profile - 1) <= 1 || profile == 16 || profile == 17 ||
        profile == 18 || profile == 19 || profile == 20 || profile == 21 ||
        profile == 22 || profile == 23 || profile == 24 || profile == 25 || profile == 26)
        result = 1;
    return result;
}
