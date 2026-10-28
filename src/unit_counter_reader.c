typedef unsigned char u8;

/* The manifest supplies one counter offset and its independent entry point. */
#ifndef UNIT_COUNTER_FUNCTION
#error UNIT_COUNTER_FUNCTION must name the recovered function
#endif
#ifndef UNIT_COUNTER_OFFSET
#error UNIT_COUNTER_OFFSET must select the observed counter byte
#endif

struct UnitCounterView {
    u8 bytes00[UNIT_COUNTER_OFFSET];
    u8 value;
};

u8 UNIT_COUNTER_FUNCTION(const struct UnitCounterView *unit)
{
    return unit->value;
}
