/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern u8 ReadAbilitySlotBValue(void *unit);
asm(".global ReadAbilitySlotBValue\n.thumb_set ReadAbilitySlotBValue, 0x080cd50d\n");

/* The slot-B value 2 selects fixed-point scaling when the caller permits it. */
int ScaleValueForAbilitySlotB(void *unit, int value, u8 bypass)
{
    if (!bypass && ReadAbilitySlotBValue(unit) == 2)
        return (value * 358) >> 8;
    return value;
}
