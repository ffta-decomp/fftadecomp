#ifndef FFTA_BATTLE_EFFECT_DISPATCH_09_H
#define FFTA_BATTLE_EFFECT_DISPATCH_09_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

/* Shared calculation context. Names describe the observed consumers, not a
 * complete gameplay schema. Volatile fields preserve reloads across helpers. */
typedef struct {
    void *actor;
    void *target;
    u32 field08;
    u16 action;
    u16 item;
    u8 reserved10[16];
    s16 amount;
    u8 reserved22[4];
    u16 flags;
    u8 reserved28[8];
    u8 *descriptor;
} EffectRuleContext;
typedef u32 (*EffectCallback)(volatile EffectRuleContext *context);
#define EffectByte(unit, offset) (*(volatile u8 *)((u8 *)(unit) + (offset)))
#define EffectHalf(unit, offset) (*(volatile u16 *)((u8 *)(unit) + (offset)))

#define EffectTargetField19IsZero RetailCall_080c8280
u32 EffectTargetField19IsZero(void *unit);
#define EffectUnitStatusBit15 UnitField27HasBit15
u32 EffectUnitStatusBit15(void *unit);
#define EffectTargetGate1308F4 EvaluateBattleCounterD8Condition
u32 EffectTargetGate1308F4(void *unit);
#define EffectUnsignedResidue IP03_UnsignedRemainder
u32 EffectUnsignedResidue(u32 numerator, u32 denominator);
#define EffectItemProperty GetItemProperty
u32 EffectItemProperty(u32 item, u32 property);
#define EffectTargetGateC8384 EffectRuleCall_080C8384
u32 EffectTargetGateC8384(void *unit);
#define EffectTargetGateCDBCC EffectRuleCall_080CDBCC
u32 EffectTargetGateCDBCC(void *unit);
#define EffectTargetGateCD95C UnitStateE9HasBit0
u32 EffectTargetGateCD95C(void *unit);
#define EffectUnitProperty ReadUnitField
u32 EffectUnitProperty(void *unit, u32 property);
#define EffectTargetGateC8298 RetailCall_080c8298
u32 EffectTargetGateC8298(void *unit);
#define EffectTargetGateCDCEC RetailCall_080cdcec
u32 EffectTargetGateCDCEC(void *unit);
#define EffectTargetGateCDA4C BattleCalculationCall_080CDA4C
u32 EffectTargetGateCDA4C(void *unit);
#define EffectNextRandom NextRandom15
u32 EffectNextRandom(void);
#define EffectSignedRemainder RetailCall_08142950
s32 EffectSignedRemainder(s32 numerator, s32 denominator);
#define EffectSignedDivide DivideSignedValues
s32 EffectSignedDivide(s32 numerator, s32 denominator);
#define EffectUnsignedQuotient UnsignedDivide
u32 EffectUnsignedQuotient(u32 numerator, u32 denominator);
#define EffectBaseCalculation EffectRuleCall_0813189C
s32 EffectBaseCalculation(volatile EffectRuleContext *context);
#define EffectMaximumRule EffectRuleCall_081314FC
u32 EffectMaximumRule(volatile EffectRuleContext *context);
#define EffectPredicateSameProperty EffectRuleCall_08130CC4
u32 EffectPredicateSameProperty(volatile EffectRuleContext *context);
#define EffectPredicateTargetGate EffectRuleCall_08130D54
u32 EffectPredicateTargetGate(volatile EffectRuleContext *context);
#define EffectPredicateNotTypeNine EffectRuleCall_08130D80
u32 EffectPredicateNotTypeNine(volatile EffectRuleContext *context);
#define EffectPredicateInverseGate EffectRuleCall_08130DCC
u32 EffectPredicateInverseGate(volatile EffectRuleContext *context);
#define EffectCalculateOperand EffectRuleCall_0813054C
s32 EffectCalculateOperand(void *actor, void *target, u32 action, u32 item, u32 mode);
#define EffectCalculateBase EffectRuleCall_0813079C
s32 EffectCalculateBase(void *actor, void *target, u32 action, u32 item, u32 zero, u32 mode);
#define EffectCalculateAlternate EffectRuleCall_081307C8
s32 EffectCalculateAlternate(void *actor, void *target, u32 action, u32 item, u32 zero, u32 mode);
#define EffectCalculateThird EffectRuleCall_081307F4
s32 EffectCalculateThird(void *actor, void *target, u32 action, u32 item, u32 zero, u32 mode);
#define EffectCalculateResponse EffectRuleCall_08130150
s32 EffectCalculateResponse(void *actor, void *target, u32 action, u32 mode);
#define EffectTargetSignGate UseThreeForBattleCounterD8
u32 EffectTargetSignGate(void *unit);
#define EffectMultiplier RetailCall_08133988
u32 EffectMultiplier(void);
#define EffectCalculationKind RetailCall_0812f358
u32 EffectCalculationKind(void);
#define EffectSuppressionGate RetailCall_08130868
u32 EffectSuppressionGate(void *actor, void *target);
#define EffectCallThroughR1 CompilerCallViaR1
u32 EffectCallThroughR1(volatile EffectRuleContext *context, EffectCallback callback);

#endif

__asm__(".global BattleCalculationCall_080CDA4C\n.thumb_set BattleCalculationCall_080CDA4C,0x080CDA4D");
