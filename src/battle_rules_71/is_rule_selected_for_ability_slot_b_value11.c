/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed int s32;
extern u8 ReadAbilitySlotBValue(const u8 *unit);
__asm__(".global ReadAbilitySlotBValue\n.thumb_set ReadAbilitySlotBValue, 0x080cd50d");

u8 IsRuleSelectedForAbilitySlotBValue11(const u8 *unit, s32 rule);
u8 IsRuleSelectedForAbilitySlotBValue11(const u8 *unit, s32 rule)
{
    if (ReadAbilitySlotBValue(unit) != 11)
        return 0;
    switch (rule) {
    case 12:
    case 35:
    case 41:
    case 45:
    case 46:
    case 56:
    case 61:
        return 1;
    /* These original slots share the rejection tail. */
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 42:
    case 43:
    case 44:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 57:
    case 58:
    case 59:
    case 60:
    default:
        return 0;
    }
}
