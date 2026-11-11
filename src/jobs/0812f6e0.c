/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u32 ReadUnitField(const void *unit, u8 selector);

u32 ClassifyUnitField03Range(const void *unit);
u32 ClassifyUnitField03Range(const void *unit)
{
    switch (ReadUnitField(unit, 3)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return 0;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        return 1;
    default:
        return 2;
    }
}
