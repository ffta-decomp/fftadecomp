typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 CalculateBattleActionAmount(void *actor, void *target, u16 action,
                                       u16 item, u16 tag, u8 scale_mode,
                                       u8 formula_mode);

s32 EvaluateEffectFormula(void *actor, void *target, u32 action, u32 item,
                          u32 tag, u32 scale_mode) asm("EffectDirect_001307F4");
s32 EvaluateEffectFormula(void *actor, void *target, u32 action, u32 item,
                          u32 tag, u32 scale_mode)
{
    u16 normalized_action = (u16)action;
    u16 normalized_item = (u16)item;
    u16 normalized_tag = (u16)tag;
    u8 normalized_scale_mode = (u8)scale_mode;
    return CalculateBattleActionAmount(actor, target, normalized_action,
                                       normalized_item, normalized_tag,
                                       normalized_scale_mode, 2);
}
