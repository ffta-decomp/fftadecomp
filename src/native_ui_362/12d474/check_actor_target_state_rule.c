#include "interfaces.h"
u8 CheckActorTargetStateRule(const u8 *actor, const u8 *target, s32 rule) __asm__("CoreContinuation_0012D474");
u8 CheckActorTargetStateRule(const u8 *actor, const u8 *target, s32 rule)
{
    const u16 *categories;
    s32 count;
    u8 field;
    register const u8 *field_target __asm__("r0");
    u32 value;
    switch (rule) {
    case 15:
        count = 3;
        categories = (const u16 *)0x083a8472;
        break;
    case 27:
        count = 1;
        categories = (const u16 *)0x083a8482;
        break;
    case 16:
        count = 3;
        categories = (const u16 *)0x083a847c;
        break;
    case 37:
        count = 19;
        categories = (const u16 *)0x083a844c;
        break;
    case 7:
        count = 2;
        categories = (const u16 *)0x083a8478;
        break;
    case 9:
        if (!IsPrimaryRosterUnit(target))
            goto accept;
        value = gRosterRuleState.value;
        goto check_value;
    /* Preserve every observed dispatch slot that shares the rejection tail. */
    case 10: case 11: case 12: case 13: case 14:
    case 18: case 19: case 20: case 21: case 22: case 23:
    case 24: case 25: case 26: case 28: case 29: case 30:
    case 31: case 32: case 33: case 34: case 35: case 36:
    default:
    reject:
        return 0;
    case 17:
        field_target = target;
        /* Preserve this branch's actual first-argument definition before selector setup. */
        __asm__("" : "+r" (field_target));
        field = 7;
        goto read_field;
    case 6:
        field_target = target;
        __asm__("" : "+r" (field_target));
        field = 38;
    read_field:
        value = ReadUnitField(field_target, field);
    check_value:
        if (value == 0)
            goto reject;
    accept:
        return 1;
    case 8:
        return HasCompatibleActorTargetChoice(actor, target);
    }
    return HasEquippedItemCategory(target, categories, count);
}
