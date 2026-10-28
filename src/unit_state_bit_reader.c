typedef unsigned char u8;

/*
 * Each manifest entry supplies one observed byte offset, bit mask, and symbol.
 * Separate compilation preserves the original 24-byte Thumb entry points.
 */
#ifndef UNIT_STATE_FUNCTION
#error UNIT_STATE_FUNCTION must name the recovered function
#endif
#ifndef UNIT_STATE_OFFSET
#error UNIT_STATE_OFFSET must select the observed state byte
#endif
#ifndef UNIT_STATE_MASK
#error UNIT_STATE_MASK must select the observed state bit
#endif

struct UnitStateView {
    u8 bytes00[UNIT_STATE_OFFSET];
    u8 state;
};

u8 UNIT_STATE_FUNCTION(const struct UnitStateView *unit)
{
#ifdef UNIT_STATE_MASK_FIRST
    int mask = UNIT_STATE_MASK;
    u8 *state = (u8 *)&unit->state;
#else
    u8 *state = (u8 *)&unit->state;
    int mask = UNIT_STATE_MASK;
#endif

    if (!(*state & mask))
        return 0;
    return 1;
}
