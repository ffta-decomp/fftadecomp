typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectContext {
    void *actor;
    void *target;
    u8 unknown_08[4];
    u16 action, item;
    u8 unknown_10[22];
    u16 flags;
};
typedef char EffectFlagsOffset[((u32)&((struct EffectContext *)0)->flags == 38) ? 1 : -1];
extern u32 CalculateAlternateAmount(void *, void *, u32, u32, u32, u32) __asm__("0x081307c8");
u32 CalculateEffectAlternate(struct EffectContext *context)
{
    void *actor, *target;
    u32 action, item;
    actor = context->actor;
    target = context->target;
    action = context->action;
    item = context->item;
    return CalculateAlternateAmount(actor, target, action, item, 0,
                    (u16)(context->flags & 16) != 0 ? 2 : 0);
}
