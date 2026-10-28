/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 InitializeBattleRuleValue(void *unit, u16 rule, s32 *value);
extern u32 CheckBattleRuleStatus(void *unit, u32 rule);
extern u32 ReadUnitField(const void *unit, u8 selector);
extern u32 CheckEquippedItemRule(void *unit, u16 item, u32 rule);
extern u8 IsRuleSelectedForAbilitySlotBValue11(const void *unit, u32 rule);
extern u8 IsUnitEligibleForRuleValue(void *unit);
extern s32 ReadAbilitySlotBBattleAdjustment(const void *unit);
extern s32 ClassifyRelativePosition(s8 position_a, s8 position_b, s8 position_c, s8 position_d, s8 direction);
extern const s8 gRelativePositionAdjustments[];
__asm__(".global InitializeBattleRuleValue\n.thumb_set InitializeBattleRuleValue,0x0812c97d");
__asm__(".global CheckBattleRuleStatus\n.thumb_set CheckBattleRuleStatus,0x08133a59");
__asm__(".global CheckEquippedItemRule\n.thumb_set CheckEquippedItemRule,0x0812d07d");
__asm__(".global IsRuleSelectedForAbilitySlotBValue11\n.thumb_set IsRuleSelectedForAbilitySlotBValue11,0x0812d0bd");
__asm__(".global IsUnitEligibleForRuleValue\n.thumb_set IsUnitEligibleForRuleValue,0x0812c56d");
__asm__(".global ReadAbilitySlotBBattleAdjustment\n.thumb_set ReadAbilitySlotBBattleAdjustment,0x0812d1b9");
__asm__(".global ClassifyRelativePosition\n.thumb_set ClassifyRelativePosition,0x0812c701");
__asm__(".global gRelativePositionAdjustments\n.set gRelativePositionAdjustments,0x083a8448");

s32 ComputeBattleRuleComplement(void *source_unit, void *target_unit,
    u8 position_a, u8 position_b, u8 position_c, u8 position_d,
    u8 direction, u32 rule);
s32 ComputeBattleRuleComplement(void *source_unit, void *target_unit,
    u8 position_a, u8 position_b, u8 position_c, u8 position_d,
    u8 direction, u32 rule)
{
    s32 rule_value;
    s32 equipment_index;
    if ((u8)InitializeBattleRuleValue(target_unit, (u16)rule, &rule_value) == 0) {
        if ((u8)CheckBattleRuleStatus(target_unit, rule) == 0)
            return 0;
        for (equipment_index = 0; equipment_index < 5; ++equipment_index) {
            u32 item = ReadUnitField(target_unit, equipment_index + 29);
            if (item != 0) {
                if ((u8)CheckEquippedItemRule(target_unit, (u16)item, rule) == 0)
                    return 0;
            }
        }
        if ((u8)IsRuleSelectedForAbilitySlotBValue11(target_unit, rule) != 0)
            return 0;
        if ((u8)IsUnitEligibleForRuleValue(target_unit) == 0)
            return 100;
        rule_value += ReadAbilitySlotBBattleAdjustment(source_unit);
        rule_value += gRelativePositionAdjustments[ClassifyRelativePosition(
            (s8)position_a, (s8)position_b, (s8)position_c,
            (s8)position_d, (s8)direction)];
        if (rule_value < 0)
            rule_value = 0;
        if (rule_value > 99)
            rule_value = 100;
    }
    return 100 - rule_value;
}
