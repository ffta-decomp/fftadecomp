typedef unsigned char u8;
struct EffectDescriptor { u8 unknown00_to_03[4]; u8 category; u8 unknown05_to_0b[7]; };
typedef char DescriptorSize[(sizeof(struct EffectDescriptor)==12)?1:-1];
extern const struct EffectDescriptor gEffectDescriptors[];
asm(".global gEffectDescriptors\n.set gEffectDescriptors,0x083a87b0");
unsigned int ReadEffectCategory(u8 selector) asm("CoreDependency29_00133970");
unsigned int ReadEffectCategory(u8 selector)
{
    const struct EffectDescriptor *descriptors;
    const u8 *category;
    unsigned int byte_offset;
    descriptors = gEffectDescriptors;
    byte_offset = (unsigned int)selector * 12;
    category = (const u8 *)descriptors;
    category += 4;
    return category[byte_offset];
}
