typedef unsigned int u32;
typedef unsigned char u8;
extern u32 QueryTargetProperty(void *target);
asm(".global QueryTargetProperty\n.thumb_set QueryTargetProperty, 0x0812c961");
u32 EffectDirect_0012F1CC(void *target)
{
    return (u8)QueryTargetProperty(target);
}
