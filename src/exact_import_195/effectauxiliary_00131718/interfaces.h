typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct TargetByte10View { u8 before_value[10]; u8 value; };
struct EffectRandomContext {
    u8 before_target[4];
    struct TargetByte10View *target;
    u8 before_flags[30];
    u16 flags;
};
#define OFFSET_OF(type,field) ((u32)&(((type*)0)->field))
typedef char target_offset[(OFFSET_OF(struct EffectRandomContext,target)==4)?1:-1];
typedef char flags_offset[(OFFSET_OF(struct EffectRandomContext,flags)==38)?1:-1];
typedef char target_value_offset[(OFFSET_OF(struct TargetByte10View,value)==10)?1:-1];
extern u32 EffectNextRandom(void);
extern s32 EffectSignedRemainder(s32 numerator, s32 denominator);
__asm__(".thumb_set EffectNextRandom, 0x08002805\n.thumb_set EffectSignedRemainder, 0x08142951");
