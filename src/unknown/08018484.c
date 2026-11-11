typedef unsigned char u8;
typedef unsigned int u32;
extern u32 IsAlternateStreamProfile_080184D0(u32 profile);
__asm__(".global IsAlternateStreamProfile_080184D0\n.thumb_set IsAlternateStreamProfile_080184D0, 0x080184d1");
static inline u32 IsExtendedStreamProfile(u8 profile)
{
    u32 result = 0;
    if ((u8)(profile - 3) <= 1 || profile == 10 || profile == 11 ||
        profile == 12 || profile == 13 || profile == 15 || profile == 14)
        result = 1;
    return result;
}
u32 UsesAlternateStreamSurface(u8 profile) __asm__("Source52_00018484");
u32 UsesAlternateStreamSurface(u8 profile)
{
    u32 result = 0;
    if (IsExtendedStreamProfile(profile) || (u8)IsAlternateStreamProfile_080184D0(profile))
        result = 1;
    return result;
}
