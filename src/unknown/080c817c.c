typedef unsigned char u8;

/* Fields +4, +6, and +7 have only observed selector meanings here. */
#if defined(FIELD01_ABOVE_ONE)
u8 UnitField01AboveOne(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[4] > 1)
        match = 1;
    return match;
}
#elif defined(FIELD01_EQUALS)
u8 UnitField01Equals(const u8 *unit, u8 expected)
{
    u8 match = 0;
    if (unit != 0 && unit[4] == expected)
        match = 1;
    return match;
}
#elif defined(FIELD03_EQUALS1)
u8 UnitField03Equals1(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[6] == 1)
        match = 1;
    return match;
}
#elif defined(FIELD03_EQUALS2)
u8 UnitField03Equals2(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[6] == 2)
        match = 1;
    return match;
}
#elif defined(FIELD03_EQUALS3)
u8 UnitField03Equals3(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[6] == 3)
        match = 1;
    return match;
}
#elif defined(FIELD03_EQUALS4)
u8 UnitField03Equals4(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[6] == 4)
        match = 1;
    return match;
}
#elif defined(FIELD03_EQUALS5)
u8 UnitField03Equals5(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[6] == 5)
        match = 1;
    return match;
}
#elif defined(FIELD04_EQUALS24)
u8 UnitField04Equals24(const u8 *unit)
{
    u8 match = 0;
    if (unit != 0 && unit[7] == 24)
        match = 1;
    return match;
}
#elif defined(FIELD03_RANGE6_18)
u8 UnitField03InRange6To18(const u8 *unit)
{
    u8 in_range;
    u8 field;
    if (unit == 0)
        return 0;
    field = unit[6];
    in_range = 0;
    if ((u8)(field - 6) <= 12)
        in_range = 1;
    return in_range;
}
#endif
