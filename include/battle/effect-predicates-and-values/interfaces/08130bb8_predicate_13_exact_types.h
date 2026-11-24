typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {u8 prefix[9];u8 selector;} EffectUnit;
typedef struct {void *previous;EffectUnit *unit;} EffectContext;
u32 UnitField19IsZero(EffectUnit *) __asm__("UnitField19IsZero");
u32 IsReactionAllowed(EffectUnit *) __asm__("EvaluateBattleCounterD8Condition");
u32 UnsignedRemainder(u32,u32) __asm__("IP03_UnsignedRemainder");
