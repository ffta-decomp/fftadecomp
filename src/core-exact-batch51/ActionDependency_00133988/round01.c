typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
struct EffectActionRecord { u8 unknown00; u8 effect_selector; };
struct EffectContext { u8 unknown00_to_2f[48]; const struct EffectActionRecord *action; };
struct EffectDescriptor { u8 unknown00_to_07[8]; s8 classification; u8 unknown09_to_0b[3]; };
typedef char DescriptorSize[(sizeof(struct EffectDescriptor)==12)?1:-1];
typedef char DescriptorClassificationOffset[((u32)&(((struct EffectDescriptor*)0)->classification)==8)?1:-1];
typedef char ContextActionOffset[((u32)&(((struct EffectContext*)0)->action)==48)?1:-1];
extern const struct EffectContext gEffectContext;
extern const struct EffectDescriptor gEffectDescriptors[];
asm(".global gEffectContext\n.set gEffectContext,0x0200f3f0\n.global gEffectDescriptors\n.set gEffectDescriptors,0x083a87b0");
int ReadCurrentEffectClassification(void) asm("ActionDependency_00133988");
int ReadCurrentEffectClassification(void)
{
    const struct EffectContext *context;
    const struct EffectDescriptor *descriptors;
    context = &gEffectContext;
    descriptors = gEffectDescriptors;
    return descriptors[context->action->effect_selector].classification;
}
