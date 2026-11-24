typedef unsigned char u8;

struct UnitStateView {
    u8 bytes00[0xe9];
    u8 state_e9;
};

/* The manifest selects one entry point and mask for each isolated build. */
#ifndef UNIT_STATE_E9_FUNCTION
#error UNIT_STATE_E9_FUNCTION must name the recovered function
#endif
#ifndef UNIT_STATE_E9_MASK
#error UNIT_STATE_E9_MASK must select the recovered state bit
#endif

u8 UNIT_STATE_E9_FUNCTION(const struct UnitStateView *unit)
{
#if UNIT_STATE_E9_MASK == 1
    int mask = UNIT_STATE_E9_MASK;
    u8 *state = (u8 *)&unit->state_e9;
#else
    u8 *state = (u8 *)&unit->state_e9;
    int mask = UNIT_STATE_E9_MASK;
#endif

    if (!(*state & mask))
        return 0;
    return 1;
}
