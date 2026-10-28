typedef unsigned char u8;
typedef unsigned short u16;
typedef struct EffectContext {
    void *actor;
    void *target;
    u8 unknown_008[4];
    u16 parameter12;
    u16 parameter14;
    u8 unknown_010[22];
    u16 flags;
} EffectContext;
extern int EvaluateEffectFormula(void *actor, void *target, u16 parameter12,
                                 u16 parameter14, u16 extra, u8 mode);
asm(".global EvaluateEffectFormula\n.thumb_set EvaluateEffectFormula, 0x081307f5");
