/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u8 UnitField01Equals(const u8 *unit, u8 expected);


u8 CountOccupiedRosterUnitsExceptField01Values2And8(void);
u8 CountOccupiedRosterUnitsExceptField01Values2And8(void)
{
    const u8 *unit = (const u8 *)0x02000080;
    u32 count = 0;
    s32 remaining;

    for (remaining = 23; remaining >= 0; --remaining, unit += 264) {
        if (unit[4] != 0
            && !UnitField01Equals(unit, 2)
            && !UnitField01Equals(unit, 8))
            ++count;
    }
    return count;
}
