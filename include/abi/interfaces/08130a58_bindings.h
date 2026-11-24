typedef unsigned char u8;
typedef unsigned int u32;
struct EffectPairContext {
    void *actor;
    void *target;
};
#define OFFSET_OF(type, field) ((u32)&(((type *)0)->field))
typedef char actor_offset[(OFFSET_OF(struct EffectPairContext, actor) == 0) ? 1 : -1];
typedef char target_offset[(OFFSET_OF(struct EffectPairContext, target) == 4) ? 1 : -1];
extern u32 EffectTargetField19IsZero(void *unit);
extern u32 EffectUnitStatusBit15(void *unit);
__asm__(".thumb_set EffectTargetField19IsZero, 0x080c8281\n.thumb_set EffectUnitStatusBit15, 0x080c8241");
