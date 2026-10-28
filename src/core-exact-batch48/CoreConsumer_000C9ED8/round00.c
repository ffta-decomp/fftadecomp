typedef unsigned char u8;
typedef unsigned int u32;
/* Category byte6 selects the bound used by the unit-owned progression initializer. */
u32 GetUnitKindEntryLimit(u8 kind) asm("CoreConsumer_000C9ED8");
u32 GetUnitKindEntryLimit(u8 kind)
{
    switch (kind) {
    case 1:
        return 142;
    case 2:
        return 77;
    case 3:
        return 95;
    case 4:
        return 85;
    case 5:
        return 88;
    case 6:
        return 8;
    case 7:
        return 22;
    case 9:
        return 13;
    case 11:
    case 12:
    case 17:
        return 10;
    case 21:
        return 17;
    case 10:
    case 19:
    case 20:
    case 22:
        return 11;
    case 8:
    case 13:
    case 14:
    case 15:
    case 16:
    case 18:
    case 23:
        return 9;
    default:
        return 0;
    }
}
