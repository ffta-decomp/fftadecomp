typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectRateContext {
    u8 before_flags[38];
    u16 flags;
};
#define OFFSET_OF(type, field) ((u32)&(((type *)0)->field))
typedef char flags_offset[(OFFSET_OF(struct EffectRateContext, flags) == 38) ? 1 : -1];
extern u32 ResolutionCommonRule(struct EffectRateContext *context);
__asm__(".thumb_set ResolutionCommonRule, 0x08131221");
