typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* These names identify proven retail entry addresses, not inferred effects. */
#define DECLARE_RULE(name, address) extern u8 name(const u8 *unit) __asm__(address)
DECLARE_RULE(StateRule01, "0x080cd8fc");
DECLARE_RULE(StateRule02, "0x080cdaf4");
DECLARE_RULE(StateRule03, "0x080cdb0c");
DECLARE_RULE(StateRule04, "0x080cd8cc");
DECLARE_RULE(StateRule05, "0x080cd8e4");
DECLARE_RULE(StateRule06, "0x080cd914");
DECLARE_RULE(StateRule07, "0x080cdb24");
DECLARE_RULE(StateRule08, "0x080cd98c");
DECLARE_RULE(StateRule09, "0x080cdb3c");
DECLARE_RULE(StateRule10, "0x080cdb6c");
DECLARE_RULE(StateRule11, "0x080cdb84");
DECLARE_RULE(StateRule12, "0x080cdb9c");
DECLARE_RULE(StateRule13, "0x080cdbb4");
DECLARE_RULE(StateRuleShared, "0x080cda94");
DECLARE_RULE(ReadCounterD9, "0x080ce3a8");
DECLARE_RULE(FallbackRule, "0x08131030");
DECLARE_RULE(ReadCounterD8, "0x080ce3a0");
DECLARE_RULE(StateRule17, "0x080cd9d4");
DECLARE_RULE(StateRule18, "0x080cd9ec");
DECLARE_RULE(StateRule19, "0x080cda04");
DECLARE_RULE(StateRule20, "0x080cdbcc");
DECLARE_RULE(StateRule21, "0x080cda4c");
DECLARE_RULE(StateRule22, "0x080cdb54");
DECLARE_RULE(StateRule23, "0x080c8280");
DECLARE_RULE(StateRule24, "0x080cdca4");

/* A 1..24 predicate selector. The caller stores the returned low byte. */
u32 IsolatedCore57_0009DA0C(const u8 *unit, u32 requested_rule)
{
    u32 rule = (u16)requested_rule;

    if (rule == 0)
        rule = 1;
    if (rule > 24)
        rule = 1;

    switch (rule) {
    case 1: if (StateRule01(unit)) return 1; break;
    case 2: if (StateRule02(unit)) return 2; break;
    case 3: if (StateRule03(unit)) return 3; break;
    case 4: if (StateRule04(unit)) return 4; break;
    case 5: if (StateRule05(unit)) return 5; break;
    case 6: if (StateRule06(unit)) return 6; break;
    case 7: if (StateRule07(unit)) return 7; break;
    case 8: if (StateRule08(unit)) return 8; break;
    case 9: if (StateRule09(unit)) return 9; break;
    case 10: if (StateRule10(unit)) return 10; break;
    case 11: if (StateRule11(unit)) return 11; break;
    case 12: if (StateRule12(unit)) return 12; break;
    case 13: if (StateRule13(unit)) return 13; break;
    case 16:
        if (StateRuleShared(unit) && ReadCounterD9(unit) == 1)
            return 16;
        if (FallbackRule(unit) && ReadCounterD8(unit) == 1)
            return 16;
        break;
    case 15:
        if (StateRuleShared(unit) && ReadCounterD9(unit) == 2)
            return 15;
        if (FallbackRule(unit) && ReadCounterD8(unit) == 2)
            return 15;
        break;
    case 14:
        if (StateRuleShared(unit) && ReadCounterD9(unit) == 3)
            return 14;
        if (FallbackRule(unit) && ReadCounterD8(unit) == 3)
            return 14;
        break;
    case 17: if (StateRule17(unit)) return 17; break;
    case 18: if (StateRule18(unit)) return 18; break;
    case 19: if (StateRule19(unit)) return 19; break;
    case 20: if (StateRule20(unit)) return 20; break;
    case 21: if (StateRule21(unit)) return 21; break;
    case 22: if (StateRule22(unit)) return 22; break;
    case 23:
        if (StateRule23(unit) && !FallbackRule(unit))
            return 23;
        break;
    case 24: if (StateRule24(unit)) return 24; break;
    }
    return 0;
}
