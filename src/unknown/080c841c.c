typedef unsigned char u8;
extern u8 ReadJobMappingValue(u8 index);

/* The retail switch table accepts ten mapped job values. */
u8 UnitMatchesJobMappingSet(const u8 *unit)
{
    switch (ReadJobMappingValue(unit[7])) {
    case 1: case 4: case 6: case 7: case 10: case 12:
    case 16: case 21: case 24: case 30: return 1;
    default: return 0;
    }
}
