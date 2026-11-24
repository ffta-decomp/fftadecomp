typedef unsigned char u8;

extern void SetOpposingStateCounters(u8 *unit, u8 first, u8 second);

static inline u8 ReadCounter(const u8 *unit, unsigned offset)
{
    return unit[offset];
}

/* Adds three to one observed side, then normalizes both counters. */
void AddOpposingStateCounter(u8 *unit, u8 first_side)
{
    u8 first = ReadCounter(unit, 0xda);
    u8 second = ReadCounter(unit, 0xdb);

    if ((first & 0x80) || (second & 0x80))
        return;

    if (first_side) {
        first += 3;
        if (first > 6)
            first = 6;
    } else {
        second += 3;
        if (second > 6)
            second = 6;
    }

    SetOpposingStateCounters(unit, first, second);
}
