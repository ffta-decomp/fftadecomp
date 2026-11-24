/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u32 ReadUnitField(const void *unit, u8 selector);

u32 MapUnitKindToEffectCode(const void *unit)
{
    switch (ReadUnitField(unit, 4)) {
    case 44:
    case 45:
        return 229;
    case 46:
    case 47:
    case 48:
        return 230;
    case 49:
    case 50:
        return 231;
    case 51:
    case 52:
    case 53:
        return 232;
    case 54:
    case 55:
        return 233;
    case 56:
    case 57:
        return 234;
    case 62:
    case 63:
        return 235;
    case 64:
    case 65:
        return 236;
    case 66:
    case 67:
        return 237;
    default:
        return 0;
    }
}
