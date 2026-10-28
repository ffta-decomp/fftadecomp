#ifndef FFTA_BATTLE_EFFECT_RESOLUTION_10_H
#define FFTA_BATTLE_EFFECT_RESOLUTION_10_H
#include "../battle_effect_dispatch_09/interfaces.h"
typedef signed char s8;

/* Reuse the shared calculation context and selected accessor/math bodies. */
#define ResolutionInitialGate EffectResolutionCall_0812F2CC
u32 ResolutionInitialGate(void *actor, void *target, u32 code);
#define ResolutionCode74Gate EffectResolutionCall_0812F124
u32 ResolutionCode74Gate(void *target);
#define ResolutionCompatibilityGate EffectResolutionCall_08133A58
u32 ResolutionCompatibilityGate(void *target, u32 code);
#define ResolutionAbilityProperty BattleRecordProperty_080CCD50
u32 ResolutionAbilityProperty(u32 action, u32 property);
#define ResolutionReaction RetailCall_0812e6a4
u32 ResolutionReaction(void *target);
#define ResolutionPointGate RetailCall_0812f0e4
u32 ResolutionPointGate(void *target, s32 x, s32 y);
#define ResolutionForce100Gate UnitStateEAHasBit1
u32 ResolutionForce100Gate(void *target);
#define ResolutionRule_12DAB8 EffectResolutionCall_0812DAB8
u32 ResolutionRule_12DAB8(void *actor, void *target);
#define ResolutionRule_12D398 EffectResolutionCall_0812D398
u32 ResolutionRule_12D398(void *actor, void *target, u32 value);
#define ResolutionRule_12DAEC EffectResolutionCall_0812DAEC
u32 ResolutionRule_12DAEC(void *actor, void *target, u32 value);
#define ResolutionRule_12EF94 RetailCall_0812ef94
u32 ResolutionRule_12EF94(void *actor, void *target, u32 zero2, u32 zero3, u32 zero4);
#define ResolutionRule_12F068 EffectResolutionCall_0812F068
u32 ResolutionRule_12F068(void *actor, void *target);
#define ResolutionRule_12F054 EffectResolutionCall_0812F054
u32 ResolutionRule_12F054(void *actor, void *target);
#define ResolutionRule_12D388 EffectResolutionCall_0812D388
u32 ResolutionRule_12D388(void *actor, void *target);
#define ResolutionRule_12D5F4 EffectResolutionCall_0812D5F4
u32 ResolutionRule_12D5F4(void *actor, void *target, u32 value, u32 selector);
#define ResolutionRule_12DA0C EffectResolutionCall_0812DA0C
u32 ResolutionRule_12DA0C(void *actor, void *target, u32 value);
#define ResolutionRule_12D99C EffectResolutionCall_0812D99C
u32 ResolutionRule_12D99C(void *target, u32 value);
#define ResolutionRule_12F008 EffectResolutionCall_0812F008
u32 ResolutionRule_12F008(void *actor, void *target, u32 value);
#define ResolutionRule_12D358 EffectResolutionCall_0812D358
u32 ResolutionRule_12D358(void *actor, void *target, u32 value);
#define ResolutionRule_12D2F0 EffectResolutionCall_0812D2F0
u32 ResolutionRule_12D2F0(void *actor, void *target, u32 value);
#define ResolutionRule_12DB5C EffectResolutionCall_0812DB5C
u32 ResolutionRule_12DB5C(void *actor, void *target, u32 value);
#define ResolutionRule_12F1CC EffectResolutionCall_0812F1CC
u32 ResolutionRule_12F1CC(void *target);
#define ResolutionEquipmentOutput RetailCall_0812f0cc
u32 ResolutionEquipmentOutput(void *target, u16 *equipment);
#define ResolutionTargetGateCD8FC EffectResolutionCall_080CD8FC
u32 ResolutionTargetGateCD8FC(void *target);
#define ResolutionCommonRule EffectResolutionCall_08131220
u32 ResolutionCommonRule(volatile EffectRuleContext *context);
#define ResolutionBaseRate EffectResolutionCall_08131160
u32 ResolutionBaseRate(volatile EffectRuleContext *context);
#define ResolutionZeroRule EffectResolutionCall_0813112C
u32 ResolutionZeroRule(volatile EffectRuleContext *context);
#define ResolutionStateE8Bit6 UnitHasPetrify
u32 ResolutionStateE8Bit6(void *unit);
#define ResolutionStateEDBit4 RetailCall_080cdcbc
u32 ResolutionStateEDBit4(void *unit);
#define ResolutionCheck_0C8280 RetailCall_080c8280
u32 ResolutionCheck_0C8280(void *unit);
#define ResolutionClear_0CE418 WriteUnitCounterD8
void ResolutionClear_0CE418(void *unit, u8 value);
#define ResolutionCheck_0CDA94 UnitStateEAHasBit4
u32 ResolutionCheck_0CDA94(void *unit);
#define ResolutionClear_0CE420 WriteUnitCounterD9
void ResolutionClear_0CE420(void *unit, u8 value);
#define ResolutionCheck_0CDAAC RetailCall_080cdaac
u32 ResolutionCheck_0CDAAC(void *unit);
#define ResolutionClear_0CE428 WriteUnitCounterDA
void ResolutionClear_0CE428(void *unit, u8 value);
#define ResolutionCheck_0CDAC4 UnitStateEAHasBit6
u32 ResolutionCheck_0CDAC4(void *unit);
#define ResolutionClear_0CE430 WriteUnitCounterDB
void ResolutionClear_0CE430(void *unit, u8 value);
#define ResolutionCheck_0CDADC UnitStateEAHasBit7
u32 ResolutionCheck_0CDADC(void *unit);
#define ResolutionClear_0CE438 WriteUnitCounterDC
void ResolutionClear_0CE438(void *unit, u8 value);
#define ResolutionCheck_0CDAF4 UnitStateEBHasBit0
u32 ResolutionCheck_0CDAF4(void *unit);
#define ResolutionClear_0CE440 WriteUnitCounterDD
void ResolutionClear_0CE440(void *unit, u8 value);
#define ResolutionCheck_0CDB0C UnitStateEBHasBit1
u32 ResolutionCheck_0CDB0C(void *unit);
#define ResolutionClear_0CE448 WriteUnitCounterDE
void ResolutionClear_0CE448(void *unit, u8 value);
#define ResolutionCheck_0CDB24 UnitStateEBHasBit2
u32 ResolutionCheck_0CDB24(void *unit);
#define ResolutionClear_0CE450 WriteUnitCounterDF
void ResolutionClear_0CE450(void *unit, u8 value);
#define ResolutionCheck_0CDB3C UnitStateEBHasBit3
u32 ResolutionCheck_0CDB3C(void *unit);
#define ResolutionClear_0CE458 WriteUnitCounterE0
void ResolutionClear_0CE458(void *unit, u8 value);
#define ResolutionCheck_0CDB54 UnitStateEBHasBit4
u32 ResolutionCheck_0CDB54(void *unit);
#define ResolutionClear_0CE460 WriteUnitCounterE1
void ResolutionClear_0CE460(void *unit, u8 value);
#define ResolutionCheck_0CDB6C UnitStateEBHasBit5
u32 ResolutionCheck_0CDB6C(void *unit);
#define ResolutionClear_0CE468 WriteUnitCounterE2
void ResolutionClear_0CE468(void *unit, u8 value);
#define ResolutionCheck_0CDB84 UnitStateEBHasBit6
u32 ResolutionCheck_0CDB84(void *unit);
#define ResolutionClear_0CE470 WriteUnitCounterE3
void ResolutionClear_0CE470(void *unit, u8 value);
#define ResolutionCheck_0CDB9C UnitStateEBHasBit7
u32 ResolutionCheck_0CDB9C(void *unit);
#define ResolutionClear_0CE478 WriteUnitCounterE4
void ResolutionClear_0CE478(void *unit, u8 value);
#define ResolutionCheck_0CDBB4 UnitStateECBit0
u32 ResolutionCheck_0CDBB4(void *unit);
#define ResolutionClear_0CE480 WriteUnitCounterE5
void ResolutionClear_0CE480(void *unit, u8 value);
#define ResolutionCheck_0CDBCC EffectRuleCall_080CDBCC
u32 ResolutionCheck_0CDBCC(void *unit);
#define ResolutionCheck_0CDA7C RetailCall_080cda7c
u32 ResolutionCheck_0CDA7C(void *unit);
#define ResolutionCheck_0CDCA4 EffectResolutionCall_080CDCA4
u32 ResolutionCheck_0CDCA4(void *unit);
#define ResolutionClear_0CE488 WriteUnitCounterE6
void ResolutionClear_0CE488(void *unit, u8 value);

#endif
