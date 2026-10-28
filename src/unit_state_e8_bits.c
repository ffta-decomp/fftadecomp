typedef unsigned char u8;

struct UnitStateView {
    u8 bytes00[0xe8];
    u8 state_e8;
};

#if UNIT_STATE_E8_BIT == 1
u8 UnitStateE8HasBit1(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 2;

    if (!(*state & mask))
        return 0;
    return 1;
}
#elif UNIT_STATE_E8_BIT == 2
u8 UnitStateE8HasBit2(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 4;

    if (!(*state & mask))
        return 0;
    return 1;
}
#elif UNIT_STATE_E8_BIT == 3
u8 UnitStateE8HasBit3(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 8;

    if (!(*state & mask))
        return 0;
    return 1;
}
#elif UNIT_STATE_E8_BIT == 4
u8 UnitStateE8HasBit4(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 16;

    if (!(*state & mask))
        return 0;
    return 1;
}
#elif UNIT_STATE_E8_BIT == 5
u8 UnitStateE8HasBit5(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 32;

    if (!(*state & mask))
        return 0;
    return 1;
}
#elif UNIT_STATE_E8_BIT == 6
u8 UnitStateE8HasBit6(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 64;

    if (!(*state & mask))
        return 0;
    return 1;
}
#elif UNIT_STATE_E8_BIT == 7
u8 UnitStateE8HasBit7(const struct UnitStateView *unit)
{
    u8 *state = (u8 *)&unit->state_e8;
    int mask = 128;

    if (!(*state & mask))
        return 0;
    return 1;
}
#else
#error UNIT_STATE_E8_BIT must select one recovered state bit
#endif
