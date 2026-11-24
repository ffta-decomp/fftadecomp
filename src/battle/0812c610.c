/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern u8 ReadAbilitySlotBValue(const u8 *unit);
__asm__(".global ReadAbilitySlotBValue\n.thumb_set ReadAbilitySlotBValue,0x080cd50d");

int ReadAbilitySlotBRuleAdjustment(const u8 *unit);
int ReadAbilitySlotBRuleAdjustment(const u8 *unit)
{
    u8 value = ReadAbilitySlotBValue(unit);
    if (value == 13)
        return -50;
    if (value == 4)
        return -15;
    return 0;
}
