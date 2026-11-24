typedef unsigned char u8;
typedef unsigned int u32;
struct TargetUnit;
struct EffectPredicateContext { void *actor; struct TargetUnit *target; };
u32 QueryTargetUnitGate(struct TargetUnit *) __asm__("RetailCall_080c8280");
asm(".global RetailCall_080c8280\n.thumb_set RetailCall_080c8280,0x080c8281\n");
