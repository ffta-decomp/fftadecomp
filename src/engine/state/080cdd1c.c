typedef unsigned char u8;

/* The manifest supplies one state byte, bit mask, and entry-point name. */
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

void UNIT_STATE_FUNCTION(struct UnitStateView *unit, u8 set)
{
    u8 *state = &unit->state;
    int clear_mask = ~UNIT_STATE_MASK;
    int set_mask = UNIT_STATE_MASK;

    *state = *state & clear_mask;
    if (set) {
        /* Both branches are intentional compiler-shaping equivalents. */
        if (state || clear_mask)
            *state = (*state & clear_mask) | set_mask;
        else
            *state = (*state & clear_mask) | set_mask;
    }
}
