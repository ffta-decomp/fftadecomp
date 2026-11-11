typedef unsigned char u8;
typedef unsigned int u32;

extern u32 EffectApplicationCall_08131BB8(const void *unit);
__asm__(".global EffectApplicationCall_08131BB8\n"
        ".thumb_set EffectApplicationCall_08131BB8, 0x08131bb9");

u32 BattleDependency_00133BC4(const void *unit)
{
    return (u8)EffectApplicationCall_08131BB8(unit);
}
