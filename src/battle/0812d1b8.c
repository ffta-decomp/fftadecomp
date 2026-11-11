/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern u8 ReadAbilitySlotBValue(const u8 *unit);
__asm__(".global ReadAbilitySlotBValue\n.thumb_set ReadAbilitySlotBValue, 0x080cd50d");

int ReadAbilitySlotBBattleAdjustment(const u8 *unit);
int ReadAbilitySlotBBattleAdjustment(const u8 *unit)
{
    u8 value = ReadAbilitySlotBValue(unit);
    if (value == 13)
        return -20;
    if (value == 4)
        return -10;
    return 0;
}
