/* Method-local interface declarations from the frozen build. */
#ifndef FFTA_BATTLE_ACTION_CALCULATION_08_H
#define FFTA_BATTLE_ACTION_CALCULATION_08_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

s32 CalculateBattleActionAmount(void *actor, void *target, u16 action, u16 item, u16 tag, u8 scale_mode, u8 formula_mode);
s32 ResolveBattleActionCalculation(void *actor, void *target, u16 action, u16 item, u16 tag, u16 scale_mode);
#define InitializeBattleCalculation RetailCall_0812f2a4
void InitializeBattleCalculation(u32 action, u32 item, u32 mode);
#define SelectBattleCalculationSlot RetailCall_0812f328
void SelectBattleCalculationSlot(u32 slot);
#define SetBattleCalculationTarget RetailCall_0812f34c
void SetBattleCalculationTarget(void *target);
#define LoadBattleCalculationSlot RetailCall_0812f39c
void LoadBattleCalculationSlot(u32 slot);
#define ReadBattleCalculationKind RetailCall_0812f358
u32 ReadBattleCalculationKind(void);
#define TestBattleCalculationSlot RetailCall_08130fbc
u32 TestBattleCalculationSlot(void);
#define ExecuteBattleCalculationKind RetailCall_08131b20
s32 ExecuteBattleCalculationKind(void);
#define CheckBattleAmountSuppression RetailCall_08130868
u32 CheckBattleAmountSuppression(void *actor, void *target);
#define ComputeBattleBaseOperand BattleCalculationCall_0812FD44
s32 ComputeBattleBaseOperand(void *actor, void *target, u32 action, u32 item, u32 tag, u32 formula_mode, u32 scale_flag);
#define ComputeBattleOpposingOperand BattleCalculationCall_0812FDDC
s32 ComputeBattleOpposingOperand(void *actor, void *target, u32 action, u32 item, u32 tag);
#define CombineBattleOperands BattleCalculationCall_0812FE28
s32 CombineBattleOperands(s32 first, s32 second);
#define ReadBattleAbilityProperty BattleRecordProperty_080CCD50
u32 ReadBattleAbilityProperty(u32 id, u32 property);
#define ReadBattleItemProperty GetItemProperty
u32 ReadBattleItemProperty(u32 id, u32 property);
#define NextBattleCalculationRandom NextRandom15
u32 NextBattleCalculationRandom(void);
#define BattleSignedRemainder RetailCall_08142950
s32 BattleSignedRemainder(s32 numerator, s32 denominator);
#define BattleSignedDivide DivideSignedValues
s32 BattleSignedDivide(s32 numerator, s32 denominator);
#define ReadBattleScalingRule BattleCalculationCall_0812F5E0
u32 ReadBattleScalingRule(void *actor, u32 item, u32 property);
#define SelectBattleResponseIndex BattleCalculationCall_0812F8A4
u32 SelectBattleResponseIndex(void *actor, u32 action, u32 item);
#define ReadBattleTargetProperty ReadUnitField
u32 ReadBattleTargetProperty(void *target, u8 property);
#define TestBattleResponseOverride BattleCalculationCall_0812FA90
u32 TestBattleResponseOverride(void *target, u32 index, u32 mode);
#define ReadBattleResponseOverride BattleCalculationCall_0812FC74
u32 ReadBattleResponseOverride(u32 encoded_response);
#define ApplyBattleResponseRules BattleCalculationCall_0812FAFC
void ApplyBattleResponseRules(void *actor, u8 *responses);
#define ReadBattleActorClass BattleCalculationCall_080CD50C
u32 ReadBattleActorClass(void *actor);
#define TransformBattleResponse BattleCalculationCall_0812F8E8
u32 TransformBattleResponse(s32 response);
#define TestBattleActorResponseGate UnitField27HasBit15
u32 TestBattleActorResponseGate(void *actor);
#define ReadBattleResponseFlag GetIndexedFlagState
u32 ReadBattleResponseFlag(u32 flag);
#define TestBattleResponseKind BattleCalculationCall_080D2CC4
u32 TestBattleResponseKind(u32 kind);
#define TestBattleTargetZeroRule BattleCalculationCall_080CDA4C
u32 TestBattleTargetZeroRule(void *target);
#define TestBattleItemSignRule RetailCall_08130654
u32 TestBattleItemSignRule(u32 item);
#define TestBattleTargetSignRule UseThreeForBattleCounterD8
u32 TestBattleTargetSignRule(void *target);
#define TestBattleItemNegation BattleCalculationCall_08130620
u32 TestBattleItemNegation(u32 item);
#endif

typedef struct { u8 reserved[51]; u8 scale; } BattleFormulaRow;
typedef char FormulaRowSize[sizeof(BattleFormulaRow)==52?1:-1];
extern const BattleFormulaRow gJobDefinitions[];
#define FormulaRows gJobDefinitions

/* These shifts intentionally retain 32-bit wrap before the arithmetic shift. */
#define TripleHalf(value) ((s32)(((u32)(value) * 3) << 7) >> 8)

s32 CalculateBattleActionAmount(void *actor, void *target, u16 action, u16 item,
                               u16 tag, u8 scale_mode, u8 formula_mode)
{
    s32 first;
    s32 second;
    s32 amount;
    s32 variation;
    s32 weighted_amount;
    u32 response_index;
    u32 response;
    u32 override;
    s32 index;
    u8 *selected_response;
    s16 saved_variation;
    u8 responses[9];

    first = ComputeBattleBaseOperand(actor, target, action, item, tag,
                                     formula_mode, scale_mode == 2);
    if (first > 999)
        first = 999;
    second = ComputeBattleOpposingOperand(actor, target, action, item, tag);
    if (second > 999)
        second = 999;
    amount = CombineBattleOperands((s16)first, (s16)second);
    if (amount <= 0)
        amount = 1;

    switch (formula_mode) {
    case 1: {
        s32 physical_factor;
        if (item == 0) {
            u32 definition_offset = 52 * ((u8 *)actor)[5];
            const BattleFormulaRow *definition = (const BattleFormulaRow *)((const u8 *)FormulaRows + definition_offset);
            physical_factor = definition->scale;
        }
        else
            physical_factor = ReadBattleItemProperty(item, 10);
        physical_factor = (s32)(((u32)physical_factor * 3) << 7);
        physical_factor >>= 8;
        weighted_amount = (s32)((u32)amount * (u32)physical_factor);
        break;
    }
    case 2: {
        s32 randomized_factor;
        if (item == 0) {
            u32 definition_offset = 52 * ((u8 *)actor)[5];
            const BattleFormulaRow *definition = (const BattleFormulaRow *)((const u8 *)FormulaRows + definition_offset);
            randomized_factor = definition->scale;
        }
        else
            randomized_factor = ReadBattleItemProperty(item, 10);
        if (scale_mode != 2) {
            s32 random_base = 256;
            variation = BattleSignedRemainder((s16)NextBattleCalculationRandom(), random_base + 1);
            variation += random_base;
            randomized_factor = (s32)((u32)randomized_factor * (u32)variation);
            randomized_factor >>= 8;
        }
        weighted_amount = (s32)((u32)amount * (u32)randomized_factor);
        break;
    }
    default:
        if (action != 0 && ReadBattleAbilityProperty(action, 3) == 0)
            weighted_amount = (s32)((u32)ReadBattleAbilityProperty(action, 33) * (u32)amount);
        else
            weighted_amount = (s32)((u32)ReadBattleScalingRule(actor, item, 10) * (u32)amount);
        break;
    }
    amount = BattleSignedDivide(weighted_amount, 100);
    if (amount <= 0)
        amount = 1;

    response_index = (u16)SelectBattleResponseIndex(actor, action, item);
    for (index = 0; index <= 8; ++index)
        responses[index] = ReadBattleTargetProperty(target, index + 10);
    override = (u16)TestBattleResponseOverride(target, (u8)response_index, 0);
    selected_response = responses + response_index;
    if (override)
        *selected_response = ReadBattleResponseOverride(override);
    ApplyBattleResponseRules(actor, responses);
    if (response_index != 0) {
        if ((u8)ReadBattleActorClass(actor) == 5)
            *selected_response = TransformBattleResponse((s8)*selected_response);
        if (!(u8)TestBattleActorResponseGate(actor) &&
            !(u8)ReadBattleResponseFlag(13) &&
            (u8)TestBattleResponseKind((u8)response_index))
            *selected_response = TransformBattleResponse((s8)*selected_response);
    }
    switch (*selected_response) {
    case 0: amount = TripleHalf(amount); break;
    case 2: amount = 0; break;
    case 3: amount = (s32)(0u - (u32)amount); break;
    case 4: amount >>= 1; break;
    }
    if (scale_mode == 1)
        amount = TripleHalf(amount);
    if ((u8)TestBattleTargetZeroRule(target))
        amount = 0;
    if (scale_mode != 2) {
        saved_variation = BattleSignedDivide(amount, 10);
        variation = (s16)(BattleSignedRemainder((s16)NextBattleCalculationRandom(),
                                               (s16)saved_variation * 2 + 1) - (s16)saved_variation);
        amount = (s32)((u32)amount + (u32)variation);
    }
    if (tag == 10)
        amount = TripleHalf(amount);
    if (action == 0 || ReadBattleAbilityProperty(action, 3) != 0) {
        if ((u8)TestBattleItemSignRule(item) && (u8)TestBattleTargetSignRule(target))
            amount = (s32)(0u - (u32)amount);
        if ((u8)TestBattleItemNegation(item))
            amount = (s32)(0u - (u32)amount);
    }
    if (amount < -999)
        amount = -999;
    if (amount > 999)
        amount = 999;
    return amount;
}
