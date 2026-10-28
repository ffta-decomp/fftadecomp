typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct EffectOperandContext {
    void *actor;
    void *target;
    u8 before_action[4];
    u16 action;
    u16 item;
    u8 before_flags[22];
    u16 flags;
};
#define OFFSET_OF(type, field) ((u32)&(((type *)0)->field))
typedef char actor_offset[(OFFSET_OF(struct EffectOperandContext, actor) == 0) ? 1 : -1];
typedef char target_offset[(OFFSET_OF(struct EffectOperandContext, target) == 4) ? 1 : -1];
typedef char action_offset[(OFFSET_OF(struct EffectOperandContext, action) == 12) ? 1 : -1];
typedef char item_offset[(OFFSET_OF(struct EffectOperandContext, item) == 14) ? 1 : -1];
typedef char flags_offset[(OFFSET_OF(struct EffectOperandContext, flags) == 38) ? 1 : -1];
extern s32 EffectCalculateBase(void *actor, void *target, u32 action, u32 item,
                              u32 zero, u32 mode);
__asm__(".thumb_set EffectCalculateBase, 0x0813079d");
