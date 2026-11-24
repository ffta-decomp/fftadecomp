typedef unsigned char u8;

enum {
    UNIT_COUNTER_FIRST = 0xda,
    UNIT_COUNTER_SECOND = 0xdb,
    UNIT_STATE_BYTE_EA = 0xea,
    UNIT_STATE_FIRST_MASK = 0x20,
    UNIT_STATE_SECOND_MASK = 0x40
};

static inline u8 IsStateBitSet(const u8 *flags, u8 mask)
{
    if (*flags & mask)
        return 1;
    return 0;
}

static inline void ClearStateBit(u8 *flags, u8 mask)
{
    *flags &= ~mask;
}

static inline void SetStateBit(u8 *flags, u8 mask)
{
    *flags = (*flags & ~mask) | mask;
}

/* Keeps the two observed counters mutually exclusive and synchronizes their bits. */
void SetOpposingStateCounters(u8 *unit, u8 first, u8 second)
{
    if (first >= second) {
        first -= second;
        second = 0;
    } else {
        second -= first;
        first = 0;
    }

    unit[UNIT_COUNTER_FIRST] = first;
    if (!first)
        ClearStateBit(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_FIRST_MASK);
    else
        SetStateBit(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_FIRST_MASK);

    unit[UNIT_COUNTER_SECOND] = second;
    if (!second)
        ClearStateBit(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_SECOND_MASK);
    else
        SetStateBit(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_SECOND_MASK);
}

/* Advances the active observed counter by one tick, unless it has bit 7 set. */
void TickOpposingStateCounters(u8 *unit)
{
    if (IsStateBitSet(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_FIRST_MASK)) {
        u8 counter = unit[UNIT_COUNTER_FIRST];
        if (counter & 0x80)
            return;
        if (counter)
            --counter;
        if (!counter)
            ClearStateBit(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_FIRST_MASK);
        unit[UNIT_COUNTER_FIRST] = counter;
    } else if (IsStateBitSet(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_SECOND_MASK)) {
        u8 counter = unit[UNIT_COUNTER_SECOND];
        if (counter & 0x80)
            return;
        if (counter)
            --counter;
        if (!counter)
            ClearStateBit(unit + UNIT_STATE_BYTE_EA, UNIT_STATE_SECOND_MASK);
        unit[UNIT_COUNTER_SECOND] = counter;
    }
}
