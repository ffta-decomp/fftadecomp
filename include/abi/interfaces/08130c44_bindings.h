typedef unsigned char u8;
typedef unsigned int u32;
struct EffectUnit;
struct EffectPredicateContext { struct EffectUnit *actor; struct EffectUnit *target; };
u32 QueryTargetUnitGate(struct EffectUnit *) __asm__("RetailCall_080c8280");
u32 ReadUnitComparisonProperty(struct EffectUnit *) __asm__("RetailCall_080c8240");
asm(".global RetailCall_080c8280\n.thumb_set RetailCall_080c8280,0x080c8281\n.global RetailCall_080c8240\n.thumb_set RetailCall_080c8240,0x080c8241\n");
