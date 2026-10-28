typedef unsigned char u8;
typedef unsigned int u32;
struct EffectUnit;
struct EffectPredicateContext { struct EffectUnit *actor; struct EffectUnit *target; };
u32 QueryTargetEligibilityGate(struct EffectUnit *) __asm__("RetailCall_080c8298");
asm(".global RetailCall_080c8298\n.thumb_set RetailCall_080c8298,0x080c8299\n");
